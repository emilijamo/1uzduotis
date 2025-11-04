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
        pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1,4);
        
    
        double generavimo_laikas = 0.0;
        double nuskaitymo_laikas = 0.0;
        double rusiavimo_laikas = 0.0;
        double dalijimo_laikas = 0.0;
        double vargsiuku_irasymo_laikas = 0.0;
        double kietiaku_irasymo_laikas = 0.0;
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
        
            cout << "Ar norite rezultatus issaugoti i txt faila?: \n";
            cout << "1 - taip\n";
            cout << "2 - ne\n";
            int issaugoti = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);
            if (issaugoti == 1) {
                cout << "Ar norite studentus suskirstyti i vargsiukus (iki 5) ir kietiakus (nuo 5)?:\n";
                cout << "1 - taip\n";
               cout << "2 - ne\n";
               int kategorizavimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);
    
                if (kategorizavimas == 1) {
                    vector<Studentas> vargsiukai, kietiakai;
                    
                    for (auto temp : Grupe) {
                        float galutinis = (temp.rez_vidurkis + temp.rez_mediana)/2.0;
                        if (galutinis < 5.0)
                            vargsiukai.push_back(temp);
                        else
                            kietiakai.push_back(temp);
                    }
                 string vargsiuku_failas, kietiaku_failas;
                cout << "Iveskite vargsiuku failo pavadinima: ";
                cin >> vargsiuku_failas;
                cout << "Iveskite kietiaku failo pavadinima: ";
                cin >> kietiaku_failas;
        
                if (!vargsiukai.empty())
                    rezultatu_isvedimas(vargsiuku_failas, vargsiukai, rez_pasirinkimas);
                if (!kietiakai.empty())
                    rezultatu_isvedimas(kietiaku_failas, kietiakai, rez_pasirinkimas);
        
                cout << "Studentai suskirstyti i failus: "
                     << vargsiuku_failas << " (vargsiukai) ir "
                     << kietiaku_failas << " (kietiakai).\n";
                } else if (kategorizavimas ==2) {
                    string failo_pav;
                    cout << "Iveskite failo pavadinima, i kuri issaugoti rezultatus: ";
                    cin >> failo_pav;
                    rezultatu_isvedimas(failo_pav, Grupe, rez_pasirinkimas);
                }
        } else {    
            cout << "--------------------------------------------------\n";
            cout << left << setw(15) << "Vardas"
                 << left << setw(15) << "Pavarde";
                
            if (rez_pasirinkimas == 1)
                cout << right << setw(10) << "Galutinis (Vid.)\n";
            else if (rez_pasirinkimas == 2)
                cout << right << setw(10) << "Galutinis (Med.)\n";
            else if (rez_pasirinkimas == 3)
                cout << right << setw(10) << "Galutinis (Vid.) " 
                     << right << setw(10) << "Galutinis (Med.)\n";
            cout << "--------------------------------------------------\n";
            
            for (auto temp :Grupe){
                cout << left << setw(15) << temp.vard
                     << left << setw(15) << temp.pav;
                    
                if (rez_pasirinkimas == 1)
                    cout << right << setw(10) << fixed << setprecision(2) << temp.rez_vidurkis << endl;
                else if (rez_pasirinkimas == 2)
                    cout << right << setw(10) << fixed << setprecision(2) << temp.rez_mediana << endl;
                else if (rez_pasirinkimas == 3)
                    cout << right << setw(10) << fixed << setprecision(2) << temp.rez_vidurkis
                         << right << setw(10) << fixed << setprecision(2) << temp.rez_mediana << endl;
            }
        }
    } else {
        list<Studentas> Grupe;
    
        int pasirinkimas;
        cout << "Kaip norite gauti studentu duomenis?\n";
        cout << "1 - Ivesti patiems arba sugeneruoti\n";
        cout << "2 - Nuskaityti is failo\n";
        cout << "3 - Atsitikinai sugeneruoti ir issaugoti i faila\n";
        cout << "Jei norite atlikti spartos analize, iveskite 4\n";
        pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1,4);
        
    
        double generavimo_laikas = 0.0;
        double nuskaitymo_laikas = 0.0;
        double rusiavimo_laikas = 0.0;
        double dalijimo_laikas = 0.0;
        double vargsiuku_irasymo_laikas = 0.0;
        double kietiaku_irasymo_laikas = 0.0;
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
    
    cout << "Kaip norite surikiuoti studentus?\n";
    cout << "1 - Pagal varda\n";
    cout << "2 - Pagal galutini bala\n";
    int rus_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);

    cout << "Studento adresas atmintyje: " << &Grupe.back() << endl;
    
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
        
            cout << "Ar norite rezultatus issaugoti i txt faila?: \n";
            cout << "1 - taip\n";
            cout << "2 - ne\n";
            int issaugoti = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);
            if (issaugoti == 1) {
                cout << "Ar norite studentus suskirstyti i vargsiukus (iki 5) ir kietiakus (nuo 5)?:\n";
                cout << "1 - taip\n";
               cout << "2 - ne\n";
               int kategorizavimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);
    
                if (kategorizavimas == 1) {
                    list<Studentas> vargsiukai, kietiakai;
                    
                    for (auto temp : Grupe) {
                        float galutinis = (temp.rez_vidurkis + temp.rez_mediana)/2.0;
                        if (galutinis < 5.0)
                            vargsiukai.push_back(temp);
                        else
                            kietiakai.push_back(temp);
                    }
                 string vargsiuku_failas, kietiaku_failas;
                cout << "Iveskite vargsiuku failo pavadinima: ";
                cin >> vargsiuku_failas;
                cout << "Iveskite kietiaku failo pavadinima: ";
                cin >> kietiaku_failas;
        
                if (!vargsiukai.empty())
                    rezultatu_isvedimas(vargsiuku_failas, vargsiukai, rez_pasirinkimas);
                if (!kietiakai.empty())
                    rezultatu_isvedimas(kietiaku_failas, kietiakai, rez_pasirinkimas);
        
                cout << "Studentai suskirstyti i failus: "
                     << vargsiuku_failas << " (vargsiukai) ir "
                     << kietiaku_failas << " (kietiakai).\n";
                } else if (kategorizavimas ==2) {
                    string failo_pav;
                    cout << "Iveskite failo pavadinima, i kuri issaugoti rezultatus: ";
                    cin >> failo_pav;
                    rezultatu_isvedimas(failo_pav, Grupe, rez_pasirinkimas);
                }
        } else {    
            cout << "--------------------------------------------------\n";
            cout << left << setw(15) << "Vardas"
                 << left << setw(15) << "Pavarde";
                
            if (rez_pasirinkimas == 1)
                cout << right << setw(10) << "Galutinis (Vid.)\n";
            else if (rez_pasirinkimas == 2)
                cout << right << setw(10) << "Galutinis (Med.)\n";
            else if (rez_pasirinkimas == 3)
                cout << right << setw(10) << "Galutinis (Vid.) " 
                     << right << setw(10) << "Galutinis (Med.)\n";
            cout << "--------------------------------------------------\n";
            
            for (auto temp :Grupe){
                cout << left << setw(15) << temp.vard
                     << left << setw(15) << temp.pav;
                    
                if (rez_pasirinkimas == 1)
                    cout << right << setw(10) << fixed << setprecision(2) << temp.rez_vidurkis << endl;
                else if (rez_pasirinkimas == 2)
                    cout << right << setw(10) << fixed << setprecision(2) << temp.rez_mediana << endl;
                else if (rez_pasirinkimas == 3)
                    cout << right << setw(10) << fixed << setprecision(2) << temp.rez_vidurkis
                         << right << setw(10) << fixed << setprecision(2) << temp.rez_mediana << endl;
            }
        }
    }
    }
    
    }








