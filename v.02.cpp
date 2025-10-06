#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> 
#include <cstdlib>   
#include <ctime> 
#include <fstream>
#include <sstream>
#include <climits>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::sort;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::ofstream;
using std::to_string;

struct Studentas {
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    float rez_vidurkis;
    float rez_mediana;
    };    

Studentas ivesk();  
float vidurkis(vector<int> pazymiai);
float mediana(vector<int> pazymiai);
void failo_nuskaitymas(string fpav, vector<Studentas>& Grupe);
void rezultatu_isvedimas(string failo_vardas, vector<Studentas>& Grupe, int rez_pasirinkimas);
bool ar_skaicius(string reiksme);
int skaiciaus_ivedimas(string prasymas, int min=INT_MIN, int max=INT_MAX);
void generuoti_faila(string failo_pav, int studsk, int ndsk);

class RandInt {
public:
    RandInt(int low, int high) : mt{rd()}, dist{low, high} { }
    int operator()() { return dist(mt); }
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};

int main (){
    vector<Studentas> Grupe;

    int pasirinkimas;
    cout << "Kaip norite gauti studentu duomenis?\n";
    cout << "1 - Ivesti patiems arba sugeneruoti\n";
    cout << "2 - Nuskaityti is failo\n";
    cout << "3 - Atsitikinai sugeneruoti ir issaugoti i faila\n";
    pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1,3);
    
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

        generuoti_faila(gen_failo_pav, studsk, ndsk);

        int skaityti = skaiciaus_ivedimas("Ar norite iskart ji nuskaityti? (1 - taip, 2 - ne): ", 1, 2);

        if (skaityti == 1) {
            failo_nuskaitymas(gen_failo_pav, Grupe);
            rez_pasirinkimas = 3;
        } else {
            cout << "Programa baigta. Galite paleisti is naujo ir nuskaityti faila rankiniu budu.\n";
            return 0;
        }
    }  

cout << "Kaip norite surikiuoti studentus?\n";
cout << "1 - Pagal varda\n";
cout << "2 - Pagal galutini bala\n";
int rus_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 2);

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
}

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

float vidurkis(vector<int> pazymiai) {
    if (pazymiai.empty()) 
    return 0.0;

    float suma = 0;
    for (int i = 0; i < pazymiai.size(); i++) {
        suma += pazymiai[i];
    }

    return suma / pazymiai.size();
}


float mediana(vector<int> pazymiai) {
        if (pazymiai.empty()) 
        return 0.0;
    sort(pazymiai.begin(), pazymiai.end());
    int n = pazymiai.size();

    if (n % 2 == 0)
        return (pazymiai[n/2 - 1] + pazymiai[n/2]) / 2.0;

    else
        return pazymiai[n/2];
}

void failo_nuskaitymas(string fpav, vector<Studentas>& Grupe) {
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

void rezultatu_isvedimas(string failo_vardas, vector<Studentas>& Grupe, int rez_pasirinkimas) {
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

bool ar_skaicius(string reiksme) {
    if (reiksme.empty()) return false;
    for (char r : reiksme) {
        if (!isdigit(r)) return false;
    }
    return true;
}

int skaiciaus_ivedimas(string prasymas, int min, int max) {
    string ivestis;
    int value;
    while (true) {
        cout << prasymas; cin >> ivestis;

        if (ar_skaicius(ivestis)) {
            value = stoi(ivestis);
            if (value >= min && value <= max) {
                return value;
            }
        }
        cout << "Neteisinga ivestis. Bandykite dar karta.\n";
    }
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
        os << left << setw(8) << "ND" << to_string(i);
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
