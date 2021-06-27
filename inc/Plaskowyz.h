#pragma once

#include "Przeszkoda.h"
#include "Prostopadloscian.h"

class Plaskowyz : public Przeszkoda {
private:
    Prostopadloscian prostopadloscian;
public:
    Plaskowyz(double dlugosc, double wysokosc, double szerkosc);

    void rysowanie() override;

    void translacja(Wektor<WEKTOR3D> wektorTranslacji) override;

    void obrotGlowny(double kat, char os) override;

    void obrotWlasny(double kat, char os) override;

    void ustawKolor(std::string _kolor) override;

    void usunObiekt() override;

    Wektor<WEKTOR3D> wezSrodekSymetrii() override;

    void ustawRamke();
};