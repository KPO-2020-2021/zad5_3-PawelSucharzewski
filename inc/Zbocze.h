#pragma once

#include "Wielokat.h"
#include "Przeszkoda.h"

const int SCIANY_BOCZNE = 2;

class Zbocze : public Przeszkoda {
private:
    Wielokat<ILOSC_KATOW> podstawa;
    std::array<Wielokat<ILOSC_KATOW>, SCIANY_BOCZNE> kwadratowe;
    std::array<Wielokat<TROJKAT>, SCIANY_BOCZNE> trojkatne;
public:
    Zbocze() = default;
    Zbocze(double dlugosc, double wyokosc, double szerokosc);

    void rysowanie() override;

    void translacja(Wektor<WEKTOR3D> wektorTranslacji) override;

    void obrotGlowny(double kat, char os) override;

    void obrotWlasny(double kat, char os) override;

    void ustawKolor(std::string _kolor) override;

    void usunObiekt() override;

    Wektor<WEKTOR3D> wezSrodekSymetrii() override;

    void ustawRamke();
};