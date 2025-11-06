#pragma once

#include "studentas.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

void generuoti_faila(string failo_pav, int studsk, int ndsk);

template <typename Konteineris>
void failo_nuskaitymas(string fpav, Konteineris& Grupe);

template <typename Konteineris>
void rezultatu_isvedimas(string failo_vardas, Konteineris& Grupe, int rez_pasirinkimas);

template <typename Konteineris>
void isvesti_studentus (Konteineris& Grupe,Konteineris& vargsiukai, Konteineris& kietiakai, int rez_pasirinkimas);

Studentas ivesk();

