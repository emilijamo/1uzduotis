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


*Atminties analizė*

1 strategija

| Duomenų kiekis | Bendras studentai (B) | Vargsiukai (B) | Kietiakai (B) | Viso (B)      |
| -------------- | --------------------- | -------------- | ------------- | ------------- |
| 1,000          | 104,000               | 53,248         | 106,496       | 263,744       |
| 10,000         | 1,040,000             | 851,968        | 851,968       | 2,743,936     |
| 100,000        | 10,400,000            | 6,815,744      | 6,815,744     | 24,031,488    |
| 1,000,000      | 104,000,000           | 54,525,952     | 109,051,904   | 267,577,856   |
| 10,000,000     | 1,040,000,000         | 436,207,616    | 872,415,232   | 2,348,622,848 |


2 strategija

| Duomenų kiekis | Vargsiukai (B) | Kietiakai (rezervuota) (B) | Kietiakai (sumažinta) (B) | Viso prieš (B) | Viso po (B)   |
| -------------- | -------------- | -------------------------- | ------------------------- | -------------- | ------------- |
| 1,000          | 53,248         | 104,000                    | 59,488                    | 157,248        | 112,736       |
| 10,000         | 851,968        | 1,040,000                  | 612,560                   | 1,891,968      | 1,464,528     |
| 100,000        | 6,815,744      | 10,400,000                 | 6,095,648                 | 17,215,744     | 12,911,392    |
| 1,000,000      | 54,525,952     | 104,000,000                | 60,963,760                | 158,525,952    | 115,489,712   |
| 10,000,000     | 436,207,616    | 1,040,000,000              | 610,308,192               | 1,476,207,616  | 1,046,515,808 |


3 strategija

| Duomenų kiekis | Bendras studentai (B) | Vargsiukai (B) | Kietiakai (B) | Viso (B)      |
| -------------- | --------------------- | -------------- | ------------- | ------------- |
| 1,000          | 104,000               | 44,928         | 59,072        | 208,000       |
| 10,000         | 1,040,000             | 427,648        | 612,352       | 2,080,000     |
| 100,000        | 10,400,000            | 4,301,336      | 6,098,664     | 20,800,000    |
| 1,000,000      | 104,000,000           | 43,017,832     | 60,982,168    | 208,000,000   |
| 10,000,000     | 1,040,000,000         | 429,491,088    | 610,508,912   | 2,080,000,000 |


*Testavimas su konteineriu std::list*

| Duomenų kiekis | 1 str  | 2 str | 3 str |
| -------------- | ------ | ----- | ----- |
| 1,000          | 0.002  | 0.000 | 0.001 |
| 10,000         | 0.017  | 0.004 | 0.010 |
| 100,000        | 0.227  | 0.042 | 0.063 |
| 1,000,000      | 1.867  | 0.035 | 0.731 |
| 10,000,000     | 18.544 | 4.345 | 9.828 |


*Atminties analizė*

1 strategija

| Duomenų kiekis | Bendras studentai (B) | Vargsiukai (B) | Kietiakai (B) | Viso (B)      |
| -------------- | --------------------- | -------------- | ------------- | ------------- |
| 1,000          | 120,000               | 51,840         | 68,160        | 240,000       |
| 10,000         | 1,200,000             | 493,440        | 706,560       | 2,400,000     |
| 100,000        | 12,000,000            | 4,963,080      | 7,036,920     | 24,000,000    |
| 1,000,000      | 120,000,000           | 49,635,960     | 70,364,040    | 240,000,000   |
| 10,000,000     | 1,200,000,000         | 495,566,640    | 704,433,360   | 2,400,000,000 |


2 strategija

| Duomenų kiekis | Vargsiukai (B) | Kietiakai (atitinkamai studentų sąrašas) (B) | Viso (B)      |
| -------------- | -------------- | -------------------------------------------- | ------------- |
| 1,000          | 51,840         | 68,160                                       | 120,000       |
| 10,000         | 493,440        | 706,560                                      | 1,200,000     |
| 100,000        | 4,963,080      | 7,036,920                                    | 12,000,000    |
| 1,000,000      | 49,635,960     | 70,364,040                                   | 120,000,000   |
| 10,000,000     | 495,566,640    | 704,433,360                                  | 1,200,000,000 |


3 strategija

| Duomenų kiekis | Bendras studentai (B) | Vargsiukai (B) | Kietiakai (B) | Viso (B)      |
| -------------- | --------------------- | -------------- | ------------- | ------------- |
| 1,000          | 0                     | 51,840         | 68,160        | 120,000       |
| 10,000         | 0                     | 493,440        | 706,560       | 1,200,000     |
| 100,000        | 0                     | 4,963,080      | 7,036,920     | 12,000,000    |
| 1,000,000      | 0                     | 49,635,960     | 70,364,040    | 120,000,000   |
| 10,000,000     | 0                     | 495,566,640    | 704,433,360   | 1,200,000,000 |

# Įdiegimo instrukcija

1. Kompiuteryje turėkite įdiegtus cmake interpretatorių bei C++ kompiliatorių. Jei neturite, galite juos įsidiegti čia: https://cmake.org/download/
  https://cmake.org/download/
  https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022

3. Iš šios github repozitorijos, atsisiųskite CMakeFiles.txt, duom_ivedimo_isvedimo_f.h, pagalbines_f.h skaiciavimo_f.h,studentas.h, duom_ivedimo_isvedimo_f.cpp, main.cpp, pagalbines_f.cpp, skaiciavimo_f.cpp failus

4. Susikurkite darbinį aplankalą, kuriame norėsite vykdyti programą. Į šį aplanką įdėkite visus parsisiųstusfailus iš github. Šiame aplankale sukurkite dar du aplankalus: src ir Include (būtinai tokiais pavadinimais). Į src aplanką perkelkite visus .cpp failus (duom_ivedimo_isvedimo_f.cpp, main.cpp, pagalbines_f.cpp, skaiciavimo_f.cpp), o į Include visus .h failus (duom_ivedimo_isvedimo_f.h, pagalbines_f.h skaiciavimo_f.h,studentas.h).

5. Tuomet terminalą nueikite iki savo darbinio aplankalo ir tuomet paleiskite šias komandas:
   1) cmake CMakeLists.txt
   2) cmake --build .
   3) cd .\Debug\
   4) .\v1.exe

Norint įdiegimą atlikti greičiau - pakartokite 1-3 žingsnius ir atsisiųskite repozitorijoje esantį run.bat failą. Jį taip pat įsikelkite į darbinį aplanką ir tiesiog paleiskite. Pirmą kartą atlikus įdiegimą programa pasileidžia automatiškai, bet jei norite ją paleisti dar kartą, per terminalą nueikite iki aplanko, kuriame yra .exe failas ir paleiskite jį įvedant terminale .\v1.exe

# Naudojimosi instrukcija

Pasileidus programą, naudotojui leidžiama pasirinkti konteinerį, su kuriuo jis norės vykdyti programą.

Įvedus atitinkamo konteinerio skaičių, naudotojui duodami pasirinkimai, ką gali daryti su programa:

<img width="309" height="125" alt="visi_funkcionalumai" src="https://github.com/user-attachments/assets/0df920ec-e542-4f5f-b8f7-48842272f670" />


*Tolimesnis programos veikimas, pasirinkus* ***1***:

Naudotojas įveda, kiek studentų norį įvesti į programą.

Tuomet atitinkamai įveda studento vardą, pavardę.

Studento pažymius galima įvesti 2 būdais - patiems arba sugeneruojant atsitiktinai:

Pasirinkus įvedimą patiems, naudotojas žinant, kiek pažymių turi studentas, gali įvesti tą skaičių į programą ir tuomet ji leis įvesti tik atitinkamą skaičių pažymių. Naudotojas, nežinant kiek studentas turi pažymių, gali įvesti 'neaisku' ir tuomet vesti pažymius iki kol jie baigias ir įvedimą užbaigti įvedus 'baigti'. Abejais atvejais įvedus visus pažymius, paprašoma įvesti egzamino pažymį.
Pasirinkus atsitiktinį generavimą, naudotojo paklausiama, kiek pažymių nori generuoti. Tuomet atitinkamai išmetamas tas skaičius pažymių ir taip pat sugeneruotas studento pažymys.

Baigus pažymių įvedimą, naudotojas gali pasirinkti, kokiu būdu skaičiuoti galutinį pažymį - medianą, vidurkį ar abu.

Tuomet pasirenkama, kaip rūšiuoti studentus rezultate - pagal vardą ar galutinį pažymį. Po šio įvedimo išmetamos nuorodos į studento vietą atmintyje.

Naudotojas gali pasirinkti, ar nori resultato išvedimo į txt failą, ar ne. Pasirinkus ne, į terminalą išvedama lentelė, kurioje atitinkamai pagal pasirinkimą surūšiuojami studentai ir matomas skaičiuotas galutinis pažymys pagal pasirinktą būdą. Pasirinkus išvedimą į failą, naudotojas gali pasirinkti, ar nori rūšiuoti studentus į vargšiukus ir kietiakus. Jei nori studentai suskirstomi ir atitinkamai išvedami į du failus, kurių pavadinimą įveda naudotojas. Pasirinkus nerūšiuoti studentų, jie išvedami į vieną failą, kurio pavadinimą įveda naudotojas. Faile randama tokia pati lentelė, kuri gaunama ir pasirinkus išvedimą ne į failą.


*Tolimesnis programos veikimas, pasirinkus* ***2***:

Naudotojo paprašoma įvesti failo pavadinimą arba tikslią jo lokaciją kompiuteryje.

Tuomet pasirenkama, kaip rūšiuoti studentus rezultate - pagal vardą ar galutinį pažymį. Po šio įvedimo išmetamos nuorodos į studento vietą atmintyje.

Naudotojas gali pasirinkti, ar nori resultato išvedimo į txt failą, ar ne. Pasirinkus ne, į terminalą išvedama lentelė, kurioje atitinkamai pagal pasirinkimą surūšiuojami studentai ir matomas skaičiuotas galutinis pažymys pagal pasirinktą būdą. Pasirinkus išvedimą į failą, naudotojas gali pasirinkti, ar nori rūšiuoti studentus į vargšiukus ir kietiakus. Jei nori studentai suskirstomi ir atitinkamai išvedami į du failus, kurių pavadinimą įveda naudotojas. Pasirinkus nerūšiuoti studentų, jie išvedami į vieną failą, kurio pavadinimą įveda naudotojas. Faile randama tokia pati lentelė, kuri gaunama ir pasirinkus išvedimą ne į failą.


*Tolimesnis programos veikimas, pasirinkus* ***3***:

Naudotojas įveda failo pavadinimą, į kurį norės išsaugoti sugeneruotus duomenis (pavadinimą būtina įvesti su .txt gale). 

Naudotojas įveda, kiek studentų norės sugeneruotame faile.

Naudotojas įveda, kiek namų darbų pažymių turės kiekvienas studentas.

Naudotojui suteikiamas pasirinkimas nuskaityti sugeneruotą failą iš karto. Jei pasirenkama nuskaityti, tai vykdomas 2 funkcionalumas nuo 2 žingsnio. Jei Nenuskaitoma, programa baigiama. Failas randamas darbiniame aplinke.


*Tolimesnis programos veikimas, pasirinkus* ***4***:

Naudotojo paprašoma įvesti failo pavadinimą, su kuriuo vykdys spartos analizę. Jei failas perskaitomas, naudotojas gauna eilutę: "Failas perskaitytas. Jame yra {atitinkamas skaičius} irasu."

Naudotojo paklausiama, kaip nori rūšiuoti studentus. 

Automatiškai yra suskirstoma į vargšiukus bei kietiakus. 

Kaip rezultatas yra išmetami duomenys apie tam tikrus programos funkcionalumo veikimo laikus:

"Bendri testavimo rezultatai, kai faile yra {atitinkamas skaičius} duomenu :

{atitinkamas laikas} - studentu duomenu nuskaitymas is tekstinio failo.

{atitinkamas laikas} - studentu rusiavimo pagal galutini rezultata laikas.

{atitinkamas laikas} - studentu dalijimo i vargsiukus ir kietiakus laikas.

{atitinkamas laikas} - studentu vargsiuku irasymo i faila laikas.

{atitinkamas laikas} - studentu kietiaku irasymo i faila laikas."


*Tolimesnis programos veikimas, pasirinkus* ***5***:

Naudotojo paprašoma įvesti failo pavadinimą, su kuriuo vykdys strategijų analizę. Jei failas perskaitomas, naudotojas gauna eilutę: "Testavimas bus atliktas su failu, kuriame yra {atitinkamas skaičius} eiluciu."

Kaip rezultatas yra išmetami duomenys apie realizuotų strategijų veikimo laikus ir užimamą vietą atmintyje.

*Proogramos rezultato lentelės pavyzdys*

<img width="324" height="116" alt="rezultatas_vid_pvz" src="https://github.com/user-attachments/assets/cecf23b4-04ec-4b99-b2c5-e001fd492ed7" />




