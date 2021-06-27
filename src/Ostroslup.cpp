#include <Ostroslup.h>
#include <bits/stdc++.h>

void Ostroslup::rysowanie() {
    podstawa.rysowanie();
    for (int i = 0; i < sciany.size(); ++i) {
        sciany[i].rysowanie();
    }

}

void Ostroslup::translacja(Wektor <WEKTOR3D> wektorTranslacji) {
    srodek_symetrii = srodek_symetrii + wektorTranslacji;
    podstawa.translacja(wektorTranslacji);
    for (int i = 0; i < sciany.size(); ++i) {
        sciany[i].translacja(wektorTranslacji);
    }
    ramka = Ramka({0,0,0,0,0,0});
    ustawRamke();
}

void Ostroslup::obrotGlowny(double kat, char os) {
    MacierzObrotu<3> obrot(kat, os);
    srodek_symetrii = obrot * srodek_symetrii;
    podstawa.obrotGlowny(kat, os);
    for (int i = 0; i < sciany.size(); ++i) {
        sciany[i].obrotGlowny(kat, os);
    }
}

void Ostroslup::obrotWlasny(double kat, char os) {
    Wektor<3> tmp = srodek_symetrii * -1;
    translacja(tmp);
    obrotGlowny(kat, os);
    tmp = tmp * -1;
    translacja(tmp);
    srodek_symetrii = tmp;
}

void Ostroslup::ustawKolor(std::string _kolor) {
    kolor = _kolor;
    podstawa.ustawKolor(kolor);
    for (int i = 0; i < sciany.size(); ++i) {
        sciany[i].ustawKolor(kolor);
    }
}

void Ostroslup::usunObiekt() {
    for (int i = 0; i < sciany.size(); ++i) {
        sciany[i].usunObiekt();
    }
}

Wektor <WEKTOR3D> Ostroslup::wezSrodekSymetrii() {
    return srodek_symetrii;
}

Ostroslup::Ostroslup(double dlugosc, double wysokosc, double szerokosc, std::string _kolor) {
    ustawKolor(_kolor);
    Wektor<WEKTOR3D> v({dlugosc, 0, 0});
    Wektor<WEKTOR3D> w({0, 0, szerokosc});
    Wektor<WEKTOR3D> r({dlugosc/2, wysokosc, szerokosc/2});

    podstawa = Wielokat<ILOSC_KATOW>(v, w, Wektor<WEKTOR3D>());
    sciany[0] = Wielokat<TROJKAT>({podstawa[0], podstawa[1], r}, kolor);
    sciany[1] = Wielokat<TROJKAT>({podstawa[1], podstawa[2], r}, kolor);
    sciany[2] = Wielokat<TROJKAT>({podstawa[2], podstawa[3], r}, kolor);
    sciany[3] = Wielokat<TROJKAT>({podstawa[3], podstawa[0], r}, kolor);

    translacja(Wektor({-dlugosc/2, 0,-szerokosc/2}));
    srodek_symetrii = Wektor({0, 0,  0});
    ramka = Ramka({0,0,0,0,0,0});
    ustawRamke();
}

void Ostroslup::ustawRamke() {
    double minX = INT_MAX;
    double maxX = INT_MIN;
    double minY = 0; // state
    double maxY = sciany[0][2][1];
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