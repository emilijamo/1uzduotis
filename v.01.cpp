#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> 
#include <cstdlib>   
#include <ctime> 

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

int main (){
    srand(time(0));
    vector<Studentas> Grupe;
    int studsk;
    cout << "Kiek studentu norite ivesti? "; cin >> studsk;
    
    for(int j=0;j<studsk;j++){
        cout<<"Iveskite " <<j+1<<" studenta:\n";
        Grupe.push_back(ivesk());
    }
    
    int rez_pasirinkimas;
    cout << "Kaip skaiciuoti galutini bala?\n";
    cout << "1 - pagal vidurki\n";
    cout << "2 - pagal mediana\n";
    cout << "3 - abu\n";
    cout << "Jusu pasirinkimas: "; cin >> rez_pasirinkimas;
    
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
    string n,m;
    int k;
   
    cout<<"Iveskite varda: "; cin>>Laik.vard;
    cout<<"Iveskite pavarde: "; cin>>Laik.pav;

    int paz_gen_pasirinkimas;
    cout << "Kaip norite i sistema suvesti rezultatus?\n";
    cout << "1 - patys\n";
    cout << "2 - rezultatai generuojami atsitiktinai\n";
    cout << "Jusu pasirinkimas: "; cin >> paz_gen_pasirinkimas;
    
   if (paz_gen_pasirinkimas == 1) {
        cout << "Kiek pazymiu turi studentas (jei nera aisku, iveskite 'neaisku'): "; cin >> n;
        if (n == "neaisku") {
            while (true) {
                cout << "Iveskite pazymi, norint baigti pazymiu ivedima, parasykite 'baigti': ";
                cin >> m;
                if (m == "baigti") break;
                int paz = stoi(m);
                if (paz < 1 || paz > 10) {
                    cout << "Pazymys turi buti intervale nuo 1 iki 10. Pabandykite dar karta.\n";
                    continue;
                }
                Laik.paz.push_back(paz);
            }
        } else {
            int kiek = stoi(n);
            if (kiek < 0) {
                cout << "Studentas negali tureti neigiamo pazymiu skaiciaus, pabandykite dar karta\n";
                return ivesk();
            }
            for (int i = 0; i < kiek; i++) {
                cout << "Iveskite " << i + 1 << " paz. is " << kiek << ": "; cin >> k;
                if (k < 1 || k > 10) {
                    cout << "Pazymys turi buti intervale nuo 1 iki 10.\n";
                    i--;
                } else {
                    Laik.paz.push_back(k);
                }
            }
        }
        cout << "Iveskite egzamina: "; cin >> Laik.egzas;
    }

    else if (paz_gen_pasirinkimas == 2) {
        int gen_kiek;
        cout << "Kiek namu darbu pazymiu norite sugeneruoti? "; cin >> gen_kiek;
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



