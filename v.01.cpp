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

bool ar_skaicius(string reiksme);

int skaiciaus_ivedimas(string prasymas, int min=INT_MIN, int max=INT_MAX);

int main (){
    srand(time(0));
    vector<Studentas> Grupe;

    int pasirinkimas;
    cout << "Kaip norite gauti studentu duomenis?\n";
    cout << "1 - Ivesti patiems arba sugeneruoti\n";
    cout << "2 - Nuskaityti is failo\n";
    pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1,2);
    
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
        cout << "Jusu pasirinkimas: "; 
        rez_pasirinkimas = skaiciaus_ivedimas("Jusu pasirinkimas: ", 1, 3);   
        
    } else if (pasirinkimas == 2) {
        rez_pasirinkimas = 3;
        string fpav;
        cout << "Koks jusu failo pavadinimas? (iveskite tikslu failo pavadinima arba idekite jo lokacija) "; cin >> fpav;
        failo_nuskaitymas(fpav, Grupe);
    } else {
        cout << "Neteisingas pasirinkimas!\n";
        return 0;
    }

    sort(Grupe.begin(), Grupe.end(), [](Studentas a, Studentas b) {
    return a.vard < b.vard; 
    });
    
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
        int gen_kiek = skaiciaus_ivedimas("Kiek namu darbu pazymiu norite sugeneruoti? ", 1);
        for (int i = 0; i < gen_kiek; i++) {
            int paz = rand() % 10 + 1; 
            Laik.paz.push_back(paz);
        }

        cout << "Sugeneruoti namu darbu pazymiai: ";
        for (int i = 0; i < Laik.paz.size(); i++) {
            cout << Laik.paz[i] << " ";
        }
        cout << endl;

        Laik.egzas = rand() % 10 +1; 
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

bool ar_skaicius(string reiksme) {
    if (reiksme.empty()) return false;
    for (char r : reiksme) {
        if (!isdigit(r)) return false;
    }
    return true;
}

int skaiciaus_ivedimas(string prasymas, int min=INT_MIN, int max=INT_MAX) {
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

