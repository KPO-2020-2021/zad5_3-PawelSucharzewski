#pragma once

#include "Wielokat.h"
#include "Przeszkoda.h"

const std::string KOLOR_PRZESZKODY = "#595959";
const int SCIANY = 4;

class Ostroslup : public Przeszkoda {
private:
    std::array<Wielokat<TROJKAT>, SCIANY> sciany;
    Wielokat<ILOSC_KATOW> podstawa;
public:
    Ostroslup(double dlugosc, double wysokosc, double szerokosc, std::string _kolor = KOLOR_PRZESZKODY);

    void rysowanie() override;

    void translacja(Wektor<WEKTOR3D> wektorTranslacji) override;

    void obrotGlowny(double kat, char os) override;

    void obrotWlasny(double kat, char os) override;

    void ustawKolor(std::string _kolor) override;

    void usunObiekt() override;

    Wektor<WEKTOR3D> wezSrodekSymetrii() override;

    void ustawRamke();
};