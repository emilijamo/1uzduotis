#pragma once 

#include <string>
#include <random>
#include <vector>
#include <list>
#include "studentas.h"

using std::string;
using std::vector;
using std::list;

bool ar_skaicius(string reiksme);
int skaiciaus_ivedimas(string prasymas, int min=INT_MIN, int max=INT_MAX);

size_t atminties_naudojimas_vector(const vector<Studentas>& Grupe);
size_t atminties_naudojimas_list(const list<Studentas>& Grupe);

class RandInt {
public:
    RandInt(int low, int high);
    int operator()();
private:
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;

};

