# 1 užduotis
*Ši programa yra skirta suskaičiuoti galutinius studentų rezultatus iš namų darbų bei egzamino pažymių.*
Namų darbų bei egzamino pažymius galima įvesti pačiam naudotojui, galima pasirinkti galimybę balus sugeneruoti automatiškai (namų darbų balų skaičius taip pat įvedamas naudotojo) arba galima nuskaityti duomenis iš failo.

*Programa leidžia generuoti atsitiktinius studentų pažymius.*
Programa turi funkcionalumą, leidžiantį pasirinkti generuoti atsitiktinius studentų pažymius į failą, taip pat kuriant ir "šabloninius" vardus bei pavardes, t.y. Vardas1 Pavarde1, Vardas2 Pavarde2,...

**Programos rezultatas** 
Įvedant duomenis pažiam naudotojui, rezultatas yra lentelė, kurioje matoma studentų vardai, pavardės ir galutiniai rezultatai.  Taip pat naudotojui suteikiamas pasirinkimas, kaip skaičiuotą rezultatą jis nori matyti galutinėje išvestyje - naudojant medianą, vidurkį ar abiem variantais skaičiuotus rezultatus.
Duomenis nuskaitant iš failo, naudotojas gali pasirinkti, nori matyti rezultatų lentelę terminale ar nori lentelę įrašyti į naują failą. Rezultatas nuskaitant nuo failo yra lentelė, kurioje pateikiami studentų vardai, pavardės ir galutiniai rezultatai, skaičiuoti tiek su mediana, tiek su vidurkiu. Pasirinkus lentelę įrašyti į failą, naudotojas gali studentus išvesti į du failus, išskirstant juos pagal jų galutinį pažymį. Į "vargšiukų" grupę yra skiriami studentai, kurių galutinis pažymys yra mažesnis už 5, o į "kietiakų" grupę skiriami studentai, kurių pažymys yra lygus arba didesnis už 5 (Verta atkreipti dėmesį, kad skirstant į grupes naudojami abiem būdais skaičiuoti galutiniai balai ir studentas į tam tikrą kategoriją skiriamas pagal jų vidurkį).

**Greičio tyrimai**

*Testavimo sistemos parametrai*

***CPU***: Intel(R) Core(TM) i5-6300U CPU @ 2.40GHz

***RAM***: 8.0 GB

***HDD***: SAMSUNG MZNLN256HMHQ-000, tipas - SSD

*Tyrimai atliekami naudojant konteinerį std::vector*

*Failų generavimo greitis*

Buvo matuojamas failų kūrimo greitis, kuriant failą su ***1000, 10000,100000,1000000,10000000*** studentų ir kiekvienu atveju, pažymėta, kad jie turi po *5* namų darbų pažymius, kad būtų galima lyginti rezultatus tarpusavyje. Matavimas buvo atliktas ***3*** kartus, tokiomis pačiomis sąlygomis ir išvestas vidurkis, pateikiamas 3 skaičių po kablelio tikslumu (milisekundėmis):

1000 studentų generavimas vidutiniškai užtruko - 0.027s

10000 studentų generavimas vidutiniškai užtruko - 0.093s

100000 studentų generavimas vidutiniškai užtruko - 1.03s

1000000 studentų generavimas vidutiniškai užtruko - 8.483s

10000000 studentų generavimas vidutiniškai užtruko - 91.611s

*Programos veikimo spartos analizė*

Ši analizė atlikta naudojant pirmojo generavimo metu gautą failą su atitinkamu studentų skaičiumi, t.y. ***1000, 10000,100000,1000000,10000000***. Matuojami buvo 5 programos veiksnumai: nuskaitymas iš failo, duomenų rūšiavimas pagal galutinį pažymį(šiuo atveju kreipiamas dėmesys ir į mediana skaičiuota pažymi, ir į vidurkiu), studentų išskirstymas pagal pažymius į vargšiukus ir kietiakus (skirstymo pagrindas apibrėžtas programos aprašyme), tuomet tų grupių išvedimas į du atskirus failus bei bendras programos veikimo laikas, t.y. visų kitų laikų suma. Analizė buvo atlikta ***3*** kartus, tokiomis pačiomis sąlygomis ir išvestas vidurkis, pateikiamas 3 skaičių po kablelio tikslumu (milisekundėmis): 

*1000 eilučių testavimas*

Nuskaitymas - 0.007s

Rūšiavimas - 0.01s

Išskirstymas - 0.001s

"Vargšiukų" įrašymas - 0.008s

"Kietiakų" įrašymas - 0.008s


Bendras laikas: 0.034s

*10000 eilučių testavimas*

Nuskaitymas - 0.048s

Rūšiavimas - 0.083s

Išskirstymas - 0.007s

"Vargšiukų" įrašymas - 0.032s 

"Kietiakų" įrašymas - 0.045s


Bendras laikas: 0.216s


*100000 eilučių testavimas*

Nuskaitymas - 0.458s

Rūšiavimas - 1.140s

Išskirstymas - 0.076s

"Vargšiukų" įrašymas - 0.305s

"Kietiakų" įrašymas - 0.445s


Bendras laikas: 2.424s


*1000000 eilučių testavimas*

Nuskaitymas - 4.775s

Rūšiavimas - 13.834s

Išskirstymas - 0.792s

"Vargšiukų" įrašymas - 2.952s 

"Kietiakų" įrašymas - 4.758s


Bendras laikas: 27.111s


*10000000 eilučių testavimas*

Nuskaitymas - 46.233s

Rūšiavimas - 161.059s

Išskirstymas - 9.637s

"Vargšiukų" įrašymas - 30.190s 

"Kietiakų" įrašymas - 43.593s


Bendras laikas: 290.712s



