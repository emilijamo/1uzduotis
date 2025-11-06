#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
#include "skaiciavimo_f.h"
#include "pagalbines_f.h"
#include "duom_ivedimo_isvedimo_f.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::to_string;
using std::list;


Studentas ivesk(){
    Studentas Laik;
   
    cout<<"Iveskite varda: "; cin>>Laik.vard;
    cout<<"Iveskite pavarde: "; cin>>Laik.pav;

    int paz_gen_pasirinkimas;
    cout << "Kaip norite i sistema suvesti rezultatus?\n";
    cout << "1 - patys\n";
    cout << "2 - rezultatai generuojami atsitiktinai\n";
    paz_gen_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);
    
      if (paz_gen_pasirinkimas == 1) {

        string n;
        while (true) {
            cout << "Kiek pazymiu turi studentas (jei nera aisku, iveskite 'neaisku'): "; cin >> n;
            if (n == "neaisku") {
                break;
            } else if (ar_skaicius(n)) {
                int kiek = stoi(n);
                if (kiek >= 0) {
                    for (int i = 0; i < kiek; i++) {
                        cout << "Vedamas " << i+1 << " pazymys is " << kiek << endl;
                        int paz = skaiciaus_ivedimas("Iveskite pazymi: ", 1, 10);
                        Laik.paz.push_back(paz);
                    }
                    break;
                } else {
                    cout << "Studentas negali tureti neigiamo pazymiu skaiciaus.\n";
                }
            } else {
                cout << "Neteisinga ivestis. Prasome ivesti skaiciu arba 'neaisku'.\n";
            }
        }

        if (n == "neaisku") {
            while (true) {
                cout << "Iveskite pazymi, norint baigti pazymiu ivedima, parasykite 'baigti': ";
                string m;
                cin >> m;
                if (m == "baigti") break;
                if (ar_skaicius(m)) {
                    int paz = stoi(m);
                    if (paz >= 1 && paz <= 10) {
                        Laik.paz.push_back(paz);
                    } else {
                        cout << "Pazymys turi buti intervale nuo 1 iki 10.\n";
                    }
                } else {
                    cout << "Neteisinga ivestis, prasome ivesti sveika teigiama skaiciu arba 'baigti'.\n";
                }
            }
        }

        Laik.egzas = skaiciaus_ivedimas("Iveskite egzamino pazymi: ", 1, 10);

    }

    else if (paz_gen_pasirinkimas == 2) {
        RandInt rng(1, 10); 
        
        int gen_kiek = skaiciaus_ivedimas("Kiek namu darbu pazymiu norite sugeneruoti? ", 1);
        for (int i = 0; i < gen_kiek; i++) {
            int paz = rng(); 
            Laik.paz.push_back(paz);
        }

        cout << "Sugeneruoti namu darbu pazymiai: ";
        for (int i = 0; i < Laik.paz.size(); i++) {
            cout << Laik.paz[i] << " ";
        }
        cout << endl;

        Laik.egzas = rng(); 
        cout << "Sugeneruotas egzamino pazymys: " << Laik.egzas << endl;
    }

    
    Laik.rez_vidurkis = Laik.egzas*0.6 + vidurkis(Laik.paz)*0.4;
    Laik.rez_mediana = Laik.egzas*0.6 + mediana(Laik.paz)*0.4;
    
    return Laik;

    }

template <typename Konteineris>
void failo_nuskaitymas(string fpav, Konteineris& Grupe) {
    ifstream is;
    is.open(fpav);
    
    if (!is) {
        cout << "Nepavyko atidaryti failo: " << fpav << endl;
        return;
    }

    string pirmas;
    getline(is, pirmas);

    string eilute;
    while (getline(is, eilute)) {
        stringstream ss(eilute);
        Studentas Laik;

         ss >> Laik.vard >> Laik.pav;

        vector<int> nd_paz;
        int paz;
        while (ss >> paz) {
            nd_paz.push_back(paz);
        }

        Laik.egzas = nd_paz.back();
        nd_paz.pop_back();

        Laik.paz = nd_paz;       

        Laik.rez_vidurkis = Laik.egzas*0.6 + vidurkis(Laik.paz)*0.4;
        Laik.rez_mediana = Laik.egzas*0.6 + mediana(Laik.paz)*0.4;

        Grupe.push_back(Laik);
    }

    is.close();

    if (Grupe.empty()) {
        cout << "Failas perskaitytas, bet studentu nerasta." << endl;
    }
}

template <typename Konteineris>
void rezultatu_isvedimas(string failo_vardas, Konteineris& Grupe, int rez_pasirinkimas) {
    ofstream os(failo_vardas);
    if (!os) {
        cout << "Nepavyko sukurti failo: " << failo_vardas << endl;
        return;
    }

    os << "--------------------------------------------------\n";
    os << left << setw(15) << "Vardas"
       << left << setw(15) << "Pavarde";

    if (rez_pasirinkimas == 1)
        os << right << setw(10) << "Galutinis (Vid.)\n";
    else if (rez_pasirinkimas == 2)
        os << right << setw(10) << "Galutinis (Med.)\n";
    else if (rez_pasirinkimas == 3)
        os << right << setw(10) << "Galutinis (Vid.) "
           << right << setw(10) << "Galutinis (Med.)\n";
    os << "--------------------------------------------------\n";

    for (auto &temp : Grupe) {
        os << left << setw(15) << temp.vard
           << left << setw(15) << temp.pav;

        if (rez_pasirinkimas == 1)
            os << right << setw(10) << fixed << setprecision(2) << temp.rez_vidurkis << endl;
        else if (rez_pasirinkimas == 2)
            os << right << setw(10) << fixed << setprecision(2) << temp.rez_mediana << endl;
        else if (rez_pasirinkimas == 3)
            os << right << setw(10) << fixed << setprecision(2) << temp.rez_vidurkis
               << right << setw(10) << fixed << setprecision(2) << temp.rez_mediana << endl;
    }

    os.close();
    cout << "Rezultatai issaugoti faile: " << failo_vardas << endl;
}

void generuoti_faila(string failo_pav, int kiek_stud, int kiek_nd) {
    ofstream os(failo_pav);
    if (!os) {
        cout << "Nepavyko sukurti failo: " << failo_pav << endl;
        return;
    }

    os << left << setw(15) << "Vardas"
       << left << setw(15) << "Pavarde";
    for (int i = 1; i <= kiek_nd; i++) {
        os << left << setw(8) << ("ND" + to_string(i));
    }
    os << left << setw(10) << "Egz." << endl;

    RandInt rng(1, 10);

    for (int i = 1; i <= kiek_stud; i++) {
        string vard = "Vardas" + to_string(i);
        string pav = "Pavarde" + to_string(i);

        os << left << setw(15) << vard
           << left << setw(15) << pav;

        for (int j = 0; j < kiek_nd; j++) {
            os << left << setw(8) << rng();
        }

        os << left << setw(10) << rng() << endl;
    }

    os.close();
    cout << "Sugeneruotas failas: " << failo_pav << " su " << kiek_stud << " studentais.\n";

};

template <typename Konteineris>
void isvesti_studentus (Konteineris& Grupe,Konteineris& vargsiukai,Konteineris& kietiakai, int rez_pasirinkimas) {
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

template void failo_nuskaitymas<vector<Studentas>>(string fpav, vector<Studentas>& Grupe);
template void failo_nuskaitymas<list<Studentas>>(string fpav, list<Studentas>& Grupe);
template void rezultatu_isvedimas<vector<Studentas>>(string failo_vardas, vector<Studentas>& Grupe, int rez_pasirinkimas);
template void rezultatu_isvedimas<list<Studentas>>(string failo_vardas, list<Studentas>& Grupe, int rez_pasirinkimas);
template void isvesti_studentus(vector<Studentas>&, vector<Studentas>&, vector<Studentas>&, int);
template void isvesti_studentus(list<Studentas>&, list<Studentas>&, list<Studentas>&, int);


