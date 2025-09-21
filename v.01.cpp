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
    for(int j=0;j<3;j++){
        cout<<"Iveskite " <<j+1<<" studenta:\n";
        Grupe.push_back(ivesk());
    }
    for (auto temp :Grupe)
    cout<<temp.vard<<" | "<<temp.pav<<" | "<<temp.rez<<endl;
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