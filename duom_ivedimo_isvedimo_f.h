#pragma once

#include "studentas.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

void generuoti_faila(string failo_pav, int studsk, int ndsk);
void failo_nuskaitymas(string fpav, vector<Studentas>& Grupe);
void rezultatu_isvedimas(string failo_vardas, vector<Studentas>& Grupe, int rez_pasirinkimas);

Studentas ivesk();