#include "Plaskowyz.h"
#include <bits/stdc++.h>

Plaskowyz::Plaskowyz(double dlugosc, double wysokosc, double szerkosc) {
    prostopadloscian = Prostopadloscian(dlugosc, wysokosc, szerkosc);
    ramka = Ramka({0,0,0,0,0,0});
    ustawRamke();
}

void Plaskowyz::rysowanie() {
    prostopadloscian.rysowanie();
}

void Plaskowyz::translacja(Wektor<WEKTOR3D> wektorTranslacji) {
    prostopadloscian.translacja(wektorTranslacji);
    ustawRamke();
}

void Plaskowyz::obrotGlowny(double kat, char os) {
    prostopadloscian.obrotGlowny(kat, os);
}

void Plaskowyz::obrotWlasny(double kat, char os) {
    prostopadloscian.obrotWlasny(kat, os);
}

void Plaskowyz::ustawKolor(std::string _kolor) {
    prostopadloscian.ustawKolor(_kolor);
}

void Plaskowyz::usunObiekt() {
    prostopadloscian.translacja(Wektor({100000, 100000, 100000}));
}

Wektor<WEKTOR3D> Plaskowyz::wezSrodekSymetrii() {
    return prostopadloscian.wezSrodekSymetrii();
}

void Plaskowyz::ustawRamke() {
    double minX = INT_MAX;
    double maxX = INT_MIN;
    double minY = 0;
    double maxY = prostopadloscian[1][0][1];
    double minZ = INT_MAX;
    double maxZ = INT_MIN;

    for (int i = 0; i < 4; ++i) {
        if(prostopadloscian[0][i][0] < minX) minX = prostopadloscian[0][i][0];
        if(prostopadloscian[0][i][0] > maxX) maxX = prostopadloscian[0][i][0];
        if(prostopadloscian[0][i][2] < minZ) minZ = prostopadloscian[0][i][2];
        if(prostopadloscian[0][i][2] > maxZ) maxZ = prostopadloscian[0][i][2];
    }

    ramka.ustawWspolrzedne({minX, maxX, minY, maxY, minZ, maxZ});

}
