#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> 

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
    int n,m ;
   
    cout<<"Iveskite varda: "; cin>>Laik.vard;
        cout<<"Iveskite pavarde: "; cin>>Laik.pav;
        cout<<"Kiek pazymiu turi studentas: "; cin>>n;
        for (int i=0;i<n;i++) {
            cout<<"Iveskite " <<i+1 << " paz. is " << n<<" : "; cin>>m;
            Laik.paz.push_back(m);
    }
    
    cout<<"Iveskite egzamina: "; cin>>Laik.egzas;
    
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
    sort(pazymiai.begin(), pazymiai.end());
    int n = pazymiai.size();

    if (n % 2 == 0)
        return (pazymiai[n/2 - 1] + pazymiai[n/2]) / 2.0;

    else
        return pazymiai[n/2];
}
