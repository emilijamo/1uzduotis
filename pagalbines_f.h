#pragma once 

#include <string>
#include <random>

using std::string;

bool ar_skaicius(string reiksme);
int skaiciaus_ivedimas(string prasymas, int min=INT_MIN, int max=INT_MAX);

class RandInt {
public:
    RandInt(int low, int high);
    int operator()();
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;
};