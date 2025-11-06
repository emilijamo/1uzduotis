#include "studentas.h"
#include "skaiciavimo_f.h"
#include "duom_ivedimo_isvedimo_f.h"
#include "pagalbines_f.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <list>


using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::sort;
using std::endl;
using std::list;
using namespace std::chrono;

int main (){
    int konteineris;
    cout << "Koki konteineri norite naudoti programoje?\n";
    cout << "1 - std::vector\n";
    cout << "2 - std::list\n";
    konteineris = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);
    bool konteineris_vektorius = (konteineris==1);

    if (konteineris_vektorius) {
        vector<Studentas> Grupe;
    
        int pasirinkimas;
        cout << "Kaip norite gauti studentu duomenis?\n";
        cout << "1 - Ivesti patiems arba sugeneruoti\n";
        cout << "2 - Nuskaityti is failo\n";
        cout << "3 - Atsitikinai sugeneruoti ir issaugoti i faila\n";
        cout << "Jei norite atlikti spartos analize, iveskite 4\n";
        cout << "Jei norite atlikti strategiju analize, iveskite 5\n";
        pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1,5);
        
    
        double generavimo_laikas = 0.0;
        double nuskaitymo_laikas = 0.0;
        double rusiavimo_laikas = 0.0;
        double dalijimo_laikas = 0.0;
        double vargsiuku_irasymo_laikas = 0.0;
        double kietiaku_irasymo_laikas = 0.0;
        double strategija1_laikas = 0.0;
        double strategija2_laikas = 0.0;
        double strategija3_laikas = 0.0;

        bool matuoti_laika = (pasirinkimas == 4);
        
        int rez_pasirinkimas;
        if (pasirinkimas == 1) {
            int studsk = skaiciaus_ivedimas("Kiek studentu norite ivesti? ", 1);
            for(int j=0;j<studsk;j++){
                cout<<"Iveskite " <<j+1<<" studenta:\n";
                Grupe.push_back(ivesk());
            }
            cout << "Kaip skaiciuoti galutini bala?\n";
            cout << "1 - pagal vidurki\n";
            cout << "2 - pagal mediana\n";
            cout << "3 - abu\n";
            rez_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 3);   
            
        } else if (pasirinkimas == 2) {
            rez_pasirinkimas = 3;
            string fpav;
    
            while (true) {
                cout << "Koks jusu failo pavadinimas? (iveskite tikslu failo pavadinima arba idekite jo lokacija) ";
                cin >> fpav;
                
                failo_nuskaitymas(fpav, Grupe);
    
                if (!Grupe.empty()) {
                    break;
                } else {
                    cout << "Nepavyko atidaryti failo arba failas tuscias. Bandykite dar karta.\n";
                }
            }
    
      } else if (pasirinkimas == 3) {
            string gen_failo_pav;
            int studsk, ndsk;
    
            cout << "Iveskite failo pavadinima, kuriame bus issaugoti sugeneruoti duomenys: ";
            cin >> gen_failo_pav;
    
            studsk = skaiciaus_ivedimas("Kiek studentu norite sugeneruoti? ", 1);
            ndsk = skaiciaus_ivedimas("Kiek namu darbu pazymiu turi kiekvienas studentas? ", 1);
            
            auto start_gen = high_resolution_clock::now();
            generuoti_faila(gen_failo_pav, studsk, ndsk);
            auto end_gen = high_resolution_clock::now();
            
            duration<double> diff_gen = end_gen - start_gen;
            generavimo_laikas = diff_gen.count();
            cout << studsk << " irasu failo generavimo laikas: " << generavimo_laikas << endl;
            
            int skaityti = skaiciaus_ivedimas("Ar norite iskart ji nuskaityti? (1 - taip, 2 - ne): ", 1, 2);
    
            if (skaityti == 1) {
                failo_nuskaitymas(gen_failo_pav, Grupe);
                rez_pasirinkimas = 3;
            } else {
                cout << "Programa baigta. Galite paleisti is naujo ir nuskaityti faila rankiniu budu.\n";
                return 0;
            }
        }  
        else if (pasirinkimas == 4) {
            rez_pasirinkimas = 3;
            string fpav;
            cout << "Iveskite failo pavadinima, kuri naudosite testavimui: ";
            cin >> fpav;
    
            auto start_read = high_resolution_clock::now();
            failo_nuskaitymas(fpav, Grupe);
            auto end_read = high_resolution_clock::now();
            nuskaitymo_laikas = duration<double>(end_read - start_read).count();
    
            if (Grupe.empty()) {
                cout << "Failas tuscias arba nepavyko atidaryti. Testavimas nutraukiamas.\n";
                return 0;
            }
            cout << "Failas perskaitytas. Jame yra " << Grupe.size() << " irasu."<<endl;
        }
        else if (pasirinkimas == 5) {   
            cout << "STRATEGIJOS ANALIZE NAUDOJANT STD::VECTOR\n";
            string fpav;
            cout << "Iveskite failo pavadinima, kuri naudosite testavimui: ";
            cin >> fpav;

            failo_nuskaitymas(fpav, Grupe);
            if (Grupe.empty()) {
                cout << "Failas tuscias arba nepavyko atidaryti. Strategijos analizė nutraukta.\n";
                return 0;
            }            
            cout << "Testavimas bus atliktas su failu, kuriame yra " <<Grupe.size() <<" eiluciu.\n";
            
            cout << fixed << setprecision(3);

            cout << "\n--1 strategija--\n";


            
            auto start_1 = high_resolution_clock::now();
            vector<Studentas> Grupe1 = Grupe;
            vector<Studentas> vargsiukai1, kietiakai1;

            for (auto temp : Grupe1) {
                float galutinis = (temp.rez_vidurkis + temp.rez_mediana)/2.0;
                if (galutinis < 5.0)
                    vargsiukai1.push_back(temp);
                else
                    kietiakai1.push_back(temp);
            }  
            auto end_1 = high_resolution_clock::now();
            strategija1_laikas = duration<double>(end_1 - start_1).count();

            cout << "1 skirstymo strategijos veikimo laikas: " << strategija1_laikas <<"s" << endl;
            
            size_t atmintis_studentai1 = atminties_naudojimas_vector(Grupe1);
            size_t atmintis_vargsiukai1 = atminties_naudojimas_vector(vargsiukai1);
            size_t atmintis_kietiakai1 = atminties_naudojimas_vector(kietiakai1);

            cout << "\nAtminties analize\n";
            cout << "Bendras studentai: " << atmintis_studentai1 << " B\n";
            cout << "Vargsiukai: " << atmintis_vargsiukai1 << " B\n";
            cout << "Kietiakai: " << atmintis_kietiakai1 << " B\n";
            cout << "Viso: "
                 << (atmintis_studentai1 + atmintis_vargsiukai1 + atmintis_kietiakai1)
                 << " B\n";            
            
            cout << "\n--2 strategija--\n";
            auto start_2 = high_resolution_clock::now();
            vector<Studentas> Grupe2 = Grupe;
            vector<Studentas> vargsiukai2;

            sort(Grupe2.begin(), Grupe2.end(), [](const Studentas &a, const Studentas &b){
                return a.rez_vidurkis > b.rez_vidurkis;
            });

            while (true) {
                Studentas s = Grupe2.back();
                if (s.rez_vidurkis < 5.0) {
                    vargsiukai2.push_back(s);
                    Grupe2.pop_back();
                } else break;
            }
            
            auto end_2 = high_resolution_clock::now();
            strategija2_laikas = duration<double>(end_2 - start_2).count();

            cout << "2 skirstymo strategijos veikimo laikas: " << strategija2_laikas << "s" << endl;
            size_t atmintis_kietiakai2 = atminties_naudojimas_vector(Grupe2);
            size_t atmintis_vargsiukai2 = atminties_naudojimas_vector(vargsiukai2);

            cout << "\nAtminties analize\n";
            cout << "Vargsiukai: " << atmintis_vargsiukai2 << " B\n";
            cout << "Kietiakai (atitinkamai studentu vektorius su rezervuota atmintimi): " << atmintis_kietiakai2 << " B\n";
            Grupe2.shrink_to_fit();
            size_t atmintis_kietiakai22 = atminties_naudojimas_vector(Grupe2);
            cout << "Kietiakai (atitinkamai studentu vektorius atlikus vektoriaus sumazinima): " << atmintis_kietiakai22 << " B\n";
            cout << "Viso (pries vektoriaus sumazinima): "
                 << (atmintis_vargsiukai2 + atmintis_kietiakai2)
                 << " B\n";

            cout << "Viso (po vektoriaus sumazinimo): "
                 << (atmintis_vargsiukai2 + atmintis_kietiakai22)
                 << " B\n";

            cout << "\n--3 strategija--\n";

            vector<Studentas> Grupe3 = Grupe;
            vector<Studentas> vargsiukai3;
            vector<Studentas> kietiakai3;

            auto start_3 = high_resolution_clock::now();

            auto it = std::partition(Grupe3.begin(), Grupe3.end(), [](const Studentas& s){
                float galutinis = (s.rez_vidurkis + s.rez_mediana)/2.0;
                return galutinis < 5.0;
            });

            vargsiukai3.insert(vargsiukai3.end(), Grupe3.begin(), it);
            kietiakai3.insert(kietiakai3.end(), it, Grupe3.end());
            auto end_3 = high_resolution_clock::now();

            strategija3_laikas = duration<double>(end_3 - start_3).count();

            cout << "3 skirstymo strategijos veikimo laikas: " << strategija3_laikas <<"s" << endl;

            size_t atmintis_studentai3 = atminties_naudojimas_vector(Grupe3);
            size_t atmintis_vargsiukai3 = atminties_naudojimas_vector(vargsiukai3);
            size_t atmintis_kietiakai3 = atminties_naudojimas_vector(kietiakai3);

            cout << "\nAtminties analize\n";
            cout << "Bendras studentai: " << atmintis_studentai3 << " B\n";
            cout << "Vargsiukai: " << atmintis_vargsiukai3 << " B\n";
            cout << "Kietiakai: " << atmintis_kietiakai3 << " B\n";
            cout << "Viso: "
                 << (atmintis_studentai3 + atmintis_vargsiukai3 + atmintis_kietiakai3)
                 << " B\n";

            return 0;
        }
    
    cout << "Kaip norite surikiuoti studentus?\n";
    cout << "1 - Pagal varda\n";
    cout << "2 - Pagal galutini bala\n";
    int rus_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);

        for (auto& studentas : Grupe) {
            cout << "Studento adresas atmintyje: " << &studentas << endl;
        }
    
    auto start_sort = high_resolution_clock::now();    
    if (rus_pasirinkimas == 1) {
        sort(Grupe.begin(), Grupe.end(), [](Studentas a, Studentas b) {
            string s1 = a.vard, s2 = b.vard;
    
            int i = 0;
            while (i < s1.size() && !isdigit(s1[i])) i++;
            int j = 0;
            while (j < s2.size() && !isdigit(s2[j])) j++;
    
            string prefix_s1 = s1.substr(0, i);
            string prefix_s2 = s2.substr(0, j);
    
            if (prefix_s1 != prefix_s2)
                return prefix_s1 < prefix_s2;
    
            int num_s1 = stoi(s1.substr(i));
            int num_s2 = stoi(s2.substr(j));
    
            return num_s1 < num_s2;
        });
    } else { 
        sort(Grupe.begin(), Grupe.end(), [rez_pasirinkimas](Studentas a,Studentas b) {
            float gal_rez_a, gal_rez_b;
    
            if (rez_pasirinkimas == 1) {
                gal_rez_a = a.rez_vidurkis;
                gal_rez_b = b.rez_vidurkis;
            } else if (rez_pasirinkimas == 2) {
                gal_rez_a = a.rez_mediana;
                gal_rez_b = b.rez_mediana;
            } else { 
                gal_rez_a = (a.rez_vidurkis + a.rez_mediana) / 2.0;
                gal_rez_b = (b.rez_vidurkis + b.rez_mediana) / 2.0;
            }
    
            return gal_rez_a > gal_rez_b; 
        });
    }
        auto end_sort = high_resolution_clock::now();
        rusiavimo_laikas = duration<double>(end_sort - start_sort).count();
    
        if (matuoti_laika) {
            cout << "\nAutomatiskai skirstoma i vargsiukus ir kietiakus.\n";
    
            auto start_split = high_resolution_clock::now();
            vector<Studentas> vargsiukai, kietiakai;
            for (auto temp : Grupe) {
                float galutinis = (temp.rez_vidurkis + temp.rez_mediana)/2.0;
                if (galutinis < 5.0)
                    vargsiukai.push_back(temp);
                else
                    kietiakai.push_back(temp);
            }
            auto end_split = high_resolution_clock::now();
            dalijimo_laikas = duration<double>(end_split - start_split).count();
    
    
            auto start_write_vargsiukai = high_resolution_clock::now();
            if (!vargsiukai.empty())
                rezultatu_isvedimas("vargsiukai.txt", vargsiukai, rez_pasirinkimas);
            auto end_write_vargsiukai = high_resolution_clock::now();
            vargsiuku_irasymo_laikas = duration<double>(end_write_vargsiukai - start_write_vargsiukai).count();
    
            auto start_write_kietiakai = high_resolution_clock::now();
            if (!kietiakai.empty())
                rezultatu_isvedimas("kietiakai.txt", kietiakai, rez_pasirinkimas);
            auto end_write_kietiakai = high_resolution_clock::now();
            kietiaku_irasymo_laikas = duration<double>(end_write_kietiakai - start_write_kietiakai).count();
    
    
            double bendras_laikas = nuskaitymo_laikas + rusiavimo_laikas + dalijimo_laikas +
                                   vargsiuku_irasymo_laikas + kietiaku_irasymo_laikas;
    
            cout << fixed << setprecision(3);
            cout << "\nBendri testavimo rezultatai, kai faile yra " << Grupe.size() <<" duomenu : \n";
            cout << endl << nuskaitymo_laikas << " - studentu duomenu nuskaitymas is tekstinio failo.\n";
            cout << endl << rusiavimo_laikas << " - studentu rusiavimo pagal galutini rezultata laikas.\n";
            cout << endl << dalijimo_laikas << " - studentu dalijimo i vargsiukus ir kietiakus laikas.\n";
            cout << endl << vargsiuku_irasymo_laikas <<" - studentu vargsiuku irasymo i faila laikas.\n";
            cout << endl << kietiaku_irasymo_laikas <<" - studentu kietiaku irasymo i faila laikas.\n";
            cout << endl << "Bendras testavimo laikas: " << bendras_laikas << endl; 
    
            cout << "\nTestavimas baigtas, jei norite testuoti kitu scenarijumi, paleiskite programa vel.";
    
            return 0;
        }
        vector<Studentas> vargsiukai, kietiakai;
        isvesti_studentus(Grupe, vargsiukai, kietiakai, rez_pasirinkimas);
        
    } else {
        list<Studentas> Grupe;
    
        int pasirinkimas;
        cout << "Kaip norite gauti studentu duomenis?\n";
        cout << "1 - Ivesti patiems arba sugeneruoti\n";
        cout << "2 - Nuskaityti is failo\n";
        cout << "3 - Atsitikinai sugeneruoti ir issaugoti i faila\n";
        cout << "Jei norite atlikti spartos analize, iveskite 4\n";
        cout << "Jei norite atlikti strategijos analize, iveskite 5\n";
        pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1,5);
        
    
        double generavimo_laikas = 0.0;
        double nuskaitymo_laikas = 0.0;
        double rusiavimo_laikas = 0.0;
        double dalijimo_laikas = 0.0;
        double vargsiuku_irasymo_laikas = 0.0;
        double kietiaku_irasymo_laikas = 0.0;
        double strategija1_laikas = 0.0;
        double strategija2_laikas = 0.0;
        double strategija3_laikas = 0.0;

        bool matuoti_laika = (pasirinkimas == 4);
        
        int rez_pasirinkimas;
        if (pasirinkimas == 1) {
            int studsk = skaiciaus_ivedimas("Kiek studentu norite ivesti? ", 1);
            for(int j=0;j<studsk;j++){
                cout<<"Iveskite " <<j+1<<" studenta:\n";
                Grupe.push_back(ivesk());
            }
            cout << "Kaip skaiciuoti galutini bala?\n";
            cout << "1 - pagal vidurki\n";
            cout << "2 - pagal mediana\n";
            cout << "3 - abu\n";
            rez_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 3);   
            
        } else if (pasirinkimas == 2) {
            rez_pasirinkimas = 3;
            string fpav;
    
            while (true) {
                cout << "Koks jusu failo pavadinimas? (iveskite tikslu failo pavadinima arba idekite jo lokacija) ";
                cin >> fpav;
                
                failo_nuskaitymas(fpav, Grupe);
    
                if (!Grupe.empty()) {
                    break;
                } else {
                    cout << "Nepavyko atidaryti failo arba failas tuscias. Bandykite dar karta.\n";
                }
            }
    
      } else if (pasirinkimas == 3) {
            
            string gen_failo_pav;
            int studsk, ndsk;
    
            cout << "Iveskite failo pavadinima, kuriame bus issaugoti sugeneruoti duomenys: ";
            cin >> gen_failo_pav;
    
            studsk = skaiciaus_ivedimas("Kiek studentu norite sugeneruoti? ", 1);
            ndsk = skaiciaus_ivedimas("Kiek namu darbu pazymiu turi kiekvienas studentas? ", 1);
            
            auto start_gen = high_resolution_clock::now();
            generuoti_faila(gen_failo_pav, studsk, ndsk);
            auto end_gen = high_resolution_clock::now();
            
            duration<double> diff_gen = end_gen - start_gen;
            generavimo_laikas = diff_gen.count();
            cout << studsk << " irasu failo generavimo laikas: " << generavimo_laikas << endl;
            
            int skaityti = skaiciaus_ivedimas("Ar norite iskart ji nuskaityti? (1 - taip, 2 - ne): ", 1, 2);
    
            if (skaityti == 1) {
                failo_nuskaitymas(gen_failo_pav, Grupe);
                rez_pasirinkimas = 3;
            } else {
                cout << "Programa baigta. Galite paleisti is naujo ir nuskaityti faila rankiniu budu.\n";
                return 0;
            }
        }  
        else if (pasirinkimas == 4) {
            rez_pasirinkimas = 3;
            string fpav;
            cout << "Iveskite failo pavadinima, kuri naudosite testavimui: ";
            cin >> fpav;
    
            auto start_read = high_resolution_clock::now();
            failo_nuskaitymas(fpav, Grupe);
            auto end_read = high_resolution_clock::now();
            nuskaitymo_laikas = duration<double>(end_read - start_read).count();
    
            if (Grupe.empty()) {
                cout << "Failas tuscias arba nepavyko atidaryti. Testavimas nutraukiamas.\n";
                return 0;
            }
            cout << "Failas perskaitytas. Jame yra " << Grupe.size() << " irasu."<<endl;
        }

            else if (pasirinkimas == 5) {   
            cout << "STRATEGIJOS ANALIZE NAUDOJANT STD::LIST\n";
            string fpav;
            cout << "Iveskite failo pavadinima, kuri naudosite testavimui: ";
            cin >> fpav;

            failo_nuskaitymas(fpav, Grupe);
            if (Grupe.empty()) {
                cout << "Failas tuscias arba nepavyko atidaryti. Strategijos analizė nutraukta.\n";
                return 0;
            }           
            cout << "Testavimas bus atliktas su failu, kuriame yra " <<Grupe.size() <<" eiluciu.\n";
            cout << fixed << setprecision(3);
                
            cout << "\n--1 strategija--\n";
                
            auto start_1 = high_resolution_clock::now();
            list<Studentas> Grupe1 = Grupe;
            list<Studentas> vargsiukai1, kietiakai1;

            for (auto temp : Grupe1) {
                float galutinis = (temp.rez_vidurkis + temp.rez_mediana)/2.0;
                if (galutinis < 5.0)
                    vargsiukai1.push_back(temp);
                else
                    kietiakai1.push_back(temp);
            }         
            auto end_1 = high_resolution_clock::now();
            strategija1_laikas = duration<double>(end_1 - start_1).count();

            cout << "1 skirstymo strategijos veikimo laikas: " << strategija1_laikas <<"s"<< endl;
                
            size_t atmintis_studentai1 = atminties_naudojimas_list(Grupe1);
            size_t atmintis_vargsiukai1 = atminties_naudojimas_list(vargsiukai1);
            size_t atmintis_kietiakai1 = atminties_naudojimas_list(kietiakai1);

            cout << "\nAtminties analize\n";
            cout << "Bendras studentai: " << atmintis_studentai1 << " B\n";
            cout << "Vargsiukai: " << atmintis_vargsiukai1 << " B\n";
            cout << "Kietiakai: " << atmintis_kietiakai1 << " B\n";
            cout << "Viso: "
                 << (atmintis_studentai1 + atmintis_vargsiukai1 + atmintis_kietiakai1)
                 << " B\n";      

            cout << "\n--2 strategija--\n";
            list<Studentas> Grupe2 = Grupe;
            list<Studentas> vargsiukai2;

            auto start_2 = high_resolution_clock::now();
            for (auto it = Grupe2.begin(); it != Grupe2.end(); ) {
            float galutinis = (it->rez_vidurkis + it->rez_mediana) / 2.0;
            if (galutinis < 5.0) {
                vargsiukai2.push_back(*it);   
                it = Grupe2.erase(it);          
            } else {
                ++it;  
              }
            }
            auto end_2 = high_resolution_clock::now();
            strategija2_laikas = duration<double>(end_2 - start_2).count();

            cout << "2 skirstymo strategijos veikimo laikas: " << strategija2_laikas << "s" << endl;
            size_t atmintis_kietiakai2 = atminties_naudojimas_list(Grupe2);
            size_t atmintis_vargsiukai2 = atminties_naudojimas_list(vargsiukai2);

            cout << "\nAtminties analize\n";
            cout << "Vargsiukai: " << atmintis_vargsiukai2 << " B\n";
            cout << "Kietiakai (atitinkamai studentu sarasas): " << atmintis_kietiakai2 << " B\n";
            cout << "Viso: "
                 << (atmintis_vargsiukai2 + atmintis_kietiakai2)
                 << " B\n";

            cout << "\n--3 strategija--\n";

            list<Studentas> Grupe3 = Grupe;
            list<Studentas> vargsiukai3;
            list<Studentas> kietiakai3;

            auto start_3 = high_resolution_clock::now();

            auto it = std::stable_partition(Grupe3.begin(), Grupe3.end(), [](const Studentas& s) {
                float galutinis = (s.rez_vidurkis + s.rez_mediana) / 2.0;
                return galutinis < 5.0;
            });

            vargsiukai3.splice(vargsiukai3.end(), Grupe3, Grupe3.begin(), it);
            kietiakai3.splice(kietiakai3.end(), Grupe3, it, Grupe3.end());
            auto end_3 = high_resolution_clock::now();

            strategija3_laikas = duration<double>(end_3 - start_3).count();

            cout << "3 skirstymo strategijos veikimo laikas: " << strategija3_laikas <<"s" << endl;

            size_t atmintis_studentai3 = atminties_naudojimas_list(Grupe3);
            size_t atmintis_vargsiukai3 = atminties_naudojimas_list(vargsiukai3);
            size_t atmintis_kietiakai3 = atminties_naudojimas_list(kietiakai3);

            cout << "\nAtminties analize\n";
            cout << "Bendras studentai: " << atmintis_studentai3 << " B\n";
            cout << "Vargsiukai: " << atmintis_vargsiukai3 << " B\n";
            cout << "Kietiakai: " << atmintis_kietiakai3 << " B\n";
            cout << "Viso: "
                 << (atmintis_studentai3 + atmintis_vargsiukai3 + atmintis_kietiakai3)
                 << " B\n";
                
            return 0;
        }
    
    cout << "Kaip norite surikiuoti studentus?\n";
    cout << "1 - Pagal varda\n";
    cout << "2 - Pagal galutini bala\n";
    int rus_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);

    for (auto& studentas : Grupe) {
        cout << "Studento adresas atmintyje: " << &studentas << endl;
    }
    
    auto start_sort = high_resolution_clock::now();    
    if (rus_pasirinkimas == 1) {
        Grupe.sort( [](Studentas a, Studentas b) {
            string s1 = a.vard, s2 = b.vard;
    
            int i = 0;
            while (i < s1.size() && !isdigit(s1[i])) i++;
            int j = 0;
            while (j < s2.size() && !isdigit(s2[j])) j++;
    
            string prefix_s1 = s1.substr(0, i);
            string prefix_s2 = s2.substr(0, j);
    
            if (prefix_s1 != prefix_s2)
                return prefix_s1 < prefix_s2;
    
            int num_s1 = stoi(s1.substr(i));
            int num_s2 = stoi(s2.substr(j));
    
            return num_s1 < num_s2;
        });
    } else { 
        Grupe.sort([rez_pasirinkimas](Studentas a,Studentas b) {
            float gal_rez_a, gal_rez_b;
    
            if (rez_pasirinkimas == 1) {
                gal_rez_a = a.rez_vidurkis;
                gal_rez_b = b.rez_vidurkis;
            } else if (rez_pasirinkimas == 2) {
                gal_rez_a = a.rez_mediana;
                gal_rez_b = b.rez_mediana;
            } else { 
                gal_rez_a = (a.rez_vidurkis + a.rez_mediana) / 2.0;
                gal_rez_b = (b.rez_vidurkis + b.rez_mediana) / 2.0;
            }
    
            return gal_rez_a > gal_rez_b; 
        });
    }
        auto end_sort = high_resolution_clock::now();
        rusiavimo_laikas = duration<double>(end_sort - start_sort).count();
    
        if (matuoti_laika) {
            cout << "\nAutomatiskai skirstoma i vargsiukus ir kietiakus.\n";
    
            auto start_split = high_resolution_clock::now();
            list<Studentas> vargsiukai, kietiakai;
            for (auto temp : Grupe) {
                float galutinis = (temp.rez_vidurkis + temp.rez_mediana)/2.0;
                if (galutinis < 5.0)
                    vargsiukai.push_back(temp);
                else
                    kietiakai.push_back(temp);
            }
            auto end_split = high_resolution_clock::now();
            dalijimo_laikas = duration<double>(end_split - start_split).count();
    
    
            auto start_write_vargsiukai = high_resolution_clock::now();
            if (!vargsiukai.empty())
                rezultatu_isvedimas("vargsiukai.txt", vargsiukai, rez_pasirinkimas);
            auto end_write_vargsiukai = high_resolution_clock::now();
            vargsiuku_irasymo_laikas = duration<double>(end_write_vargsiukai - start_write_vargsiukai).count();
    
            auto start_write_kietiakai = high_resolution_clock::now();
            if (!kietiakai.empty())
                rezultatu_isvedimas("kietiakai.txt", kietiakai, rez_pasirinkimas);
            auto end_write_kietiakai = high_resolution_clock::now();
            kietiaku_irasymo_laikas = duration<double>(end_write_kietiakai - start_write_kietiakai).count();
    
    
            double bendras_laikas = nuskaitymo_laikas + rusiavimo_laikas + dalijimo_laikas +
                                   vargsiuku_irasymo_laikas + kietiaku_irasymo_laikas;
    
            cout << fixed << setprecision(3);
            cout << "\nBendri testavimo rezultatai, kai faile yra " << Grupe.size() <<" duomenu : \n";
            cout << endl << nuskaitymo_laikas << " - studentu duomenu nuskaitymas is tekstinio failo.\n";
            cout << endl << rusiavimo_laikas << " - studentu rusiavimo pagal galutini rezultata laikas.\n";
            cout << endl << dalijimo_laikas << " - studentu dalijimo i vargsiukus ir kietiakus laikas.\n";
            cout << endl << vargsiuku_irasymo_laikas <<" - studentu vargsiuku irasymo i faila laikas.\n";
            cout << endl << kietiaku_irasymo_laikas <<" - studentu kietiaku irasymo i faila laikas.\n";
            cout << endl << "Bendras testavimo laikas: " << bendras_laikas << endl; 
    
            cout << "\nTestavimas baigtas, jei norite testuoti kitu scenarijumi, paleiskite programa vel.";
    
            return 0;
        }
        list<Studentas> vargsiukai, kietiakai;
        isvesti_studentus(Grupe, vargsiukai,kietiakai,rez_pasirinkimas);
    }
    return 0;
}
