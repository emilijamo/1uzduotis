# 1 užduotis
*Ši programa yra skirta suskaičiuoti galutinius studentų rezultatus iš namų darbų bei egzamino pažymių.*
Namų darbų bei egzamino pažymius galima įvesti pačiam naudotojui, galima pasirinkti galimybę balus sugeneruoti automatiškai (namų darbų balų skaičius taip pat įvedamas naudotojo) arba galima nuskaityti duomenis iš failo.

*Programa leidžia generuoti atsitiktinius studentų pažymius.*
Programa turi funkcionalumą, leidžiantį pasirinkti generuoti atsitiktinius studentų pažymius į failą, taip pat kuriant ir "šabloninius" vardus bei pavardes, t.y. Vardas1 Pavarde1, Vardas2 Pavarde2,...

**Programos rezultatas** 

Įvedant duomenis pažiam naudotojui, rezultatas yra lentelė, kurioje matoma studentų vardai, pavardės ir galutiniai rezultatai.  Taip pat naudotojui suteikiamas pasirinkimas, kaip skaičiuotą rezultatą jis nori matyti galutinėje išvestyje - naudojant medianą, vidurkį ar abiem variantais skaičiuotus rezultatus.
Duomenis nuskaitant iš failo, naudotojas gali pasirinkti, nori matyti rezultatų lentelę terminale ar nori lentelę įrašyti į naują failą. Rezultatas nuskaitant nuo failo yra lentelė, kurioje pateikiami studentų vardai, pavardės ir galutiniai rezultatai, skaičiuoti tiek su mediana, tiek su vidurkiu. Pasirinkus lentelę įrašyti į failą, naudotojas gali studentus išvesti į du failus, išskirstant juos pagal jų galutinį pažymį. Į "vargšiukų" grupę yra skiriami studentai, kurių galutinis pažymys yra mažesnis už 5, o į "kietiakų" grupę skiriami studentai, kurių pažymys yra lygus arba didesnis už 5 (Verta atkreipti dėmesį, kad skirstant į grupes naudojami abiem būdais skaičiuoti galutiniai balai ir studentas į tam tikrą kategoriją skiriamas pagal jų vidurkį).

# Kiekvienos versijos aprašymas

*V.01*

- Galimas studentų įvedimas žinant ir nežinant pradinio pažymių skaičiaus
- Apskaičiuojamas studentų galutinis balas pagal pažymių vidurkį bei medianą
- Studentų duomenis į programą galima įkelti ir nuskaitant iš failo
- Išvedami rezultatai lentelėje sūrušiuoti


*V.02 (patobulinta V.01)*

- Studentai gali būti sūrušiuoti į kategorijas ir rezultatai išvedami į faila
- Atliktas kodo refactoringas 
- Pridėtas funkcionalumas - spartos analizė, matuojantis programos funkcionalumų užtrunkamą laiką
  

*V.03 (patobulinta V.02)*

- Vartotojui leidžiama pasirinkti konteinerį, su kuriuo nori dirbti
- Atitinkami metodai pritaikyti std::list vektoriui
- Atlikta spartos analizė abiems konteineriams


 *V.10 (patobulinta V.03)* 
 
- Studentų dalijimui pridėtos 2 naujos strategijos ir atlikta jų laiko analizė


# Greičio tyrimai

*Testavimo sistemos parametrai*

***CPU***: Intel(R) Core(TM) i5-6300U CPU @ 2.40GHz

***RAM***: 8.0 GB

***HDD***: SAMSUNG MZNLN256HMHQ-000, tipas - SSD

*Tyrimai atliekami naudojant konteinerį std::vector*

*Failų generavimo greitis*

Buvo matuojamas failų kūrimo greitis, kuriant failą su ***1000, 10000,100000,1000000,10000000*** studentų ir kiekvienu atveju, pažymėta, kad jie turi po *5* namų darbų pažymius, kad būtų galima lyginti rezultatus tarpusavyje. Matavimas buvo atliktas ***3*** kartus, tokiomis pačiomis sąlygomis ir išvestas vidurkis, pateikiamas 3 skaičių po kablelio tikslumu (milisekundėmis):

| Studentų kiekis | Vidutinis generavimo laikas (s) |
| --------------- | ------------------------------- |
| 1 000           | 0.027                           |
| 10 000          | 0.093                           |
| 100 000         | 1.030                           |
| 1 000 000       | 8.483                           |
| 10 000 000      | 91.611                          |


*Programos veikimo spartos analizė su skirtingais konteineriais*

Ši analizė atlikta naudojant pirmojo generavimo metu gautą failą su atitinkamu studentų skaičiumi, t.y. ***1000, 10000,100000,1000000,10000000***. Matuojami buvo 5 programos veiksnumai: nuskaitymas iš failo, duomenų rūšiavimas pagal galutinį pažymį(šiuo atveju kreipiamas dėmesys ir į mediana skaičiuota pažymi, ir į vidurkiu), studentų išskirstymas pagal pažymius į vargšiukus ir kietiakus (skirstymo pagrindas apibrėžtas programos aprašyme), tuomet tų grupių išvedimas į du atskirus failus bei bendras programos veikimo laikas, t.y. visų kitų laikų suma. Analizė buvo atlikta ***3*** kartus, tokiomis pačiomis sąlygomis ir išvestas vidurkis, pateikiamas 3 skaičių po kablelio tikslumu (milisekundėmis): 

**Testavimas su konteineriu std::vector**

*1000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 0.007      |
| Rūšiavimas           | 0.010      |
| Išskirstymas         | 0.001      |
| „Vargšiukų“ įrašymas | 0.008      |
| „Kietiakų“ įrašymas  | 0.008      |
| **Bendras laikas**   | **0.034**  |


*10000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 0.048      |
| Rūšiavimas           | 0.083      |
| Išskirstymas         | 0.007      |
| „Vargšiukų“ įrašymas | 0.032      |
| „Kietiakų“ įrašymas  | 0.045      |
| **Bendras laikas**   | **0.216**  |



*100000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 0.458      |
| Rūšiavimas           | 1.140      |
| Išskirstymas         | 0.076      |
| „Vargšiukų“ įrašymas | 0.305      |
| „Kietiakų“ įrašymas  | 0.445      |
| **Bendras laikas**   | **2.424**  |



*1000000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 4.775      |
| Rūšiavimas           | 13.834     |
| Išskirstymas         | 0.792      |
| „Vargšiukų“ įrašymas | 2.952      |
| „Kietiakų“ įrašymas  | 4.758      |
| **Bendras laikas**   | **27.111** |



*10000000 eilučių testavimas*

| Veiksmas             | Laikas (s)  |
| -------------------- | ----------- |
| Nuskaitymas          | 46.233      |
| Rūšiavimas           | 161.059     |
| Išskirstymas         | 9.637       |
| „Vargšiukų“ įrašymas | 30.190      |
| „Kietiakų“ įrašymas  | 43.593      |
| **Bendras laikas**   | **290.712** |



**Testavimas su konteineriu std::list**

Ši analizė atlikta naudojant pirmojo generavimo metu gautą failą su atitinkamu studentų skaičiumi, t.y. ***1000, 10000,100000,1000000,10000000*** - tokie patys failai, kokie naudoti konteinrio std::vector analizėje. Matuojami buvo 5 programos veiksnumai: nuskaitymas iš failo, duomenų rūšiavimas pagal galutinį pažymį(šiuo atveju kreipiamas dėmesys ir į mediana skaičiuota pažymi, ir į vidurkiu), studentų išskirstymas pagal pažymius į vargšiukus ir kietiakus (skirstymo pagrindas apibrėžtas programos aprašyme), tuomet tų grupių išvedimas į du atskirus failus bei bendras programos veikimo laikas, t.y. visų kitų laikų suma. Tiek failų kūrimas, tiek ir surūšiuotų rezultatų išvedimas į failus nepriklauso nuo naudojamo konteinerio, bet, kad būtų galima palyginti bendrą veikimo laiką su skirtingais konteineriais, tai yra matuojami ir šie laikai. Analizė buvo atlikta ***3*** kartus, tokiomis pačiomis sąlygomis ir išvestas vidurkis, pateikiamas 3 skaičių po kablelio tikslumu (milisekundėmis): 

*1000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 0.012      |
| Rūšiavimas           | 0.008      |
| Išskirstymas         | 0.001      |
| „Vargšiukų“ įrašymas | 0.007      |
| „Kietiakų“ įrašymas  | 0.008      |
| **Bendras laikas**   | **0.035**  |



*10000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 0.080      |
| Rūšiavimas           | 0.134      |
| Išskirstymas         | 0.015      |
| „Vargšiukų“ įrašymas | 0.064      |
| „Kietiakų“ įrašymas  | 0.065      |
| **Bendras laikas**   | **0.358**  |



*100000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 0.619      |
| Rūšiavimas           | 1.284      |
| Išskirstymas         | 0.142      |
| „Vargšiukų“ įrašymas | 0.456      |
| „Kietiakų“ įrašymas  | 0.513      |
| **Bendras laikas**   | **3.014**  |



*1000000 eilučių testavimas*

| Veiksmas             | Laikas (s) |
| -------------------- | ---------- |
| Nuskaitymas          | 5.871      |
| Rūšiavimas           | 14.653     |
| Išskirstymas         | 1.041      |
| „Vargšiukų“ įrašymas | 4.247      |
| „Kietiakų“ įrašymas  | 6.393      |
| **Bendras laikas**   | **32.205** |



*10000000 eilučių testavimas*

| Veiksmas             | Laikas (s)  |
| -------------------- | ----------- |
| Nuskaitymas          | 61.269      |
| Rūšiavimas           | 192.896     |
| Išskirstymas         | 27.693      |
| „Vargšiukų“ įrašymas | 40.411      |
| „Kietiakų“ įrašymas  | 70.382      |
| **Bendras laikas**   | **392.652** |


**Skirtingų studentų dalijimo strategijų analizė**

Ši analizė atlikta naudojant pirmojo generavimo metu gautą failą su atitinkamu studentų skaičiumi, t.y. ***1000, 10000,100000,1000000,10000000*** - tokie patys failai, kokie naudoti ir konteinerių palyginimo analizėje. Buvo matuojamas laikas, kurį kiekviena strategija užtrunka rūšiuojant studentus į "Vargšiukų" bei "Kietiakų" grupes. Analizė buvo atlikta ***3*** kartus, tokiomis pačiomis sąlygomis ir išvestas vidurkis, pateikiamas 3 skaičių po kablelio tikslumu (milisekundėmis):

*Testavimas su konteineriu std::vector*

| Duomenų kiekis | 1 str  | 2 str  | 3 str |
| -------------- | ------ | ------ | ----- |
| 1,000          | 0.002  | 0.002  | 0.001 |
| 10,000         | 0.023  | 0.046  | 0.005 |
| 100,000        | 0.114  | 0.342  | 0.050 |
| 1,000,000      | 1.196  | 4.093  | 0.495 |
| 10,000,000     | 14.789 | 63.229 | 7.798 |


*Testavimas su konteineriu std::list*

| Duomenų kiekis | 1 str  | 2 str | 3 str |
| -------------- | ------ | ----- | ----- |
| 1,000          | 0.002  | 0.000 | 0.001 |
| 10,000         | 0.017  | 0.004 | 0.010 |
| 100,000        | 0.227  | 0.042 | 0.063 |
| 1,000,000      | 1.867  | 0.035 | 0.731 |
| 10,000,000     | 18.544 | 4.345 | 9.828 |

