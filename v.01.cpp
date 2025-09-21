#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

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

struct Studentas {
    string vard;
    string pav;
    vector<int> paz;
    int egzas;
    float rez;
    };    

Studentas ivesk();  

int main (){
    vector<Studentas> Grupe;
    int studsk;
    cout << "Kiek studentu norite ivesti? "; cin >> studsk;
    for(int j=0;j<studsk;j++){
        cout<<"Iveskite " <<j+1<<" studenta:\n";
        Grupe.push_back(ivesk());
    }
    cout << "--------------------------------------------------\n";
    cout << left << setw(15) << "Vardas"
         << left << setw(15) << "Pavarde"
         << right << setw(10) << "Galutinis (Vid.)\n";
    cout << "--------------------------------------------------\n";
    for (auto temp :Grupe)
        cout << left << setw(15) << temp.vard
             << left << setw(15) << temp.pav
             << right << setw(10) << fixed << setprecision(2) <<temp.rez << endl;
}

Studentas ivesk(){
    Studentas Laik;
    int sum=0, n,m ;
   
    cout<<"Iveskite varda: "; cin>>Laik.vard;
        cout<<"Iveskite pavarde: "; cin>>Laik.pav;
        cout<<"Kiek pazymiu turi studentas: "; cin>>n;
        for (int i=0;i<n;i++) {
            cout<<"Iveskite " <<i+1 << " paz. is " << n<<" : "; cin>>m;
            Laik.paz.push_back(m);
            sum+=m;
    }
    cout<<"Iveskite egzamina: "; cin>>Laik.egzas;
    Laik.rez=Laik.egzas*0.6+double(sum)/double(Laik.paz.size())*0.4;
    return Laik;

    }
