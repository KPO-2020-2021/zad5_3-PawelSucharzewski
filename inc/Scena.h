#pragma once

#include "Dron.h"
#include "Ostroslup.h"
#include "Zbocze.h"
#include "Przeszkoda.h"
#include "Ramka.h"
#include "Plaskowyz.h"

const int ILOSC_LINII = 3;

struct Komenda{
    char znak;
    double wartosc;
};

class Scena {
private:
    std::vector<Dron> drony;
    std::vector<Komenda> komendy;
    std::vector<Przeszkoda *> elementyTerenu;
    std::vector<Ramka *> przeszkody;
    std::array<Wielokat<LINIA>, ILOSC_LINII> trasa;
    int numerDrona;

    void animacja();
    void narysujTrase();
    bool translacjaWykonana();
    void usunTrase();
public:
    Scena();

    void wybierzDrona();
    void wystartuj();
    void obrot();
    void przesun();
    void ladowanie();
    void rysuj();
    void dodajPrzeszkode();
    void usunPrzeszkode();

};