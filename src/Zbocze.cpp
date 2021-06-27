#include "Zbocze.h"
#include <bits/stdc++.h>

Zbocze::Zbocze(double dlugosc, double wysokosc, double szerokosc) {
    ramka = Ramka({0,0,0,0,0,0});
    Wektor v ({dlugosc, 0, 0});
    Wektor r ({0, 0, szerokosc});
    kolor = KOLOR;

    podstawa = Wielokat(v, r, Wektor());
    podstawa.translacja(Wektor({- dlugosc / 2, 0, - szerokosc / 2}));

    trojkatne[0] = Wielokat<TROJKAT>({podstawa[0], podstawa[1], Wektor({0, wysokosc, 0}) + podstawa[1]}, KOLOR);
    trojkatne[1] = Wielokat<TROJKAT>({podstawa[2], podstawa[3], Wektor({0, wysokosc, 0}) + podstawa[2]}, KOLOR);

    kwadratowe[0] = Wielokat<ILOSC_KATOW>({podstawa[0], Wektor({0, wysokosc, 0}) + podstawa[1],
                                           Wektor({0, wysokosc, 0}) + podstawa[2], podstawa[3]}, KOLOR);

    kwadratowe[1] = Wielokat<ILOSC_KATOW>({podstawa[1], Wektor({0, wysokosc, 0}) + podstawa[1],
                                           Wektor({0, wysokosc, 0}) + podstawa[2], podstawa[2]}, KOLOR);
    ustawRamke();
}

void Zbocze::rysowanie() {
    podstawa.rysowanie();

    for (int i = 0; i < SCIANY_BOCZNE; ++i) {
        trojkatne[i].rysowanie();
        kwadratowe[i].rysowanie();
    }
}

void Zbocze::translacja(Wektor<WEKTOR3D> wektorTranslacji) {
    srodek_symetrii = srodek_symetrii + wektorTranslacji;
    podstawa.translacja(wektorTranslacji);

    for (int i = 0; i < SCIANY_BOCZNE; ++i) {
        trojkatne[i].translacja(wektorTranslacji);
        kwadratowe[i].translacja(wektorTranslacji);
    }
    ustawRamke();
}

void Zbocze::obrotGlowny(double kat, char os) {
    MacierzObrotu<3> obrot(kat, os);
    srodek_symetrii = obrot * srodek_symetrii;

    podstawa.obrotGlowny(kat, os);

    for (int i = 0; i < SCIANY_BOCZNE; ++i) {
        trojkatne[i].obrotGlowny(kat, os);
        kwadratowe[i].obrotGlowny(kat, os);
    }
}

void Zbocze::obrotWlasny(double kat, char os) {
    Wektor tmp = srodek_symetrii * -1;
    translacja(tmp);
    obrotGlowny(kat, os);
    tmp = tmp * -1;
    translacja(tmp);
    srodek_symetrii = tmp;
}

void Zbocze::ustawKolor(std::string _kolor) {
    kolor = _kolor;
    podstawa.ustawKolor(kolor);

    for (int i = 0; i < SCIANY_BOCZNE; ++i) {
        trojkatne[i].ustawKolor(kolor);
        kwadratowe[i].ustawKolor(kolor);
    }
}

void Zbocze::usunObiekt() {
    podstawa.translacja(Wektor({100000, 1000000, 0}));

    for (int i = 0; i < SCIANY_BOCZNE; ++i) {
        trojkatne[i].translacja(Wektor({100000, 1000000, 0}));
        kwadratowe[i].translacja(Wektor({100000, 1000000, 0}));
    }
}

Wektor<WEKTOR3D> Zbocze::wezSrodekSymetrii() {
    return srodek_symetrii;
}

void Zbocze::ustawRamke() {
    double minX = INT_MAX;
    double maxX = INT_MIN;
    double minY = 0; // state
    double maxY = kwadratowe[0][1][1]; // state
    double minZ = INT_MAX;
    double maxZ = INT_MIN;

    for (int i = 0; i < ILOSC_KATOW; ++i) {
        if(podstawa[i][0] < minX) minX = podstawa[i][0];
        if(podstawa[i][0] > maxX) maxX = podstawa[i][0];
        if(podstawa[i][2] < minZ) minZ = podstawa[i][2];
        if(podstawa[i][2] > maxZ) maxZ = podstawa[i][2];
    }
    ramka.ustawWspolrzedne({minX, maxX, minY, maxY, minZ, maxZ});
}
