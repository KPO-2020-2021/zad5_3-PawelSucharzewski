#pragma once

#include <vector>
#include "Wektor.h"

class Ramka {
private:
    std::vector<double> wspolrzedne;
public:
    Ramka();

    Ramka(const std::vector<double> &wspolrzedne);

    Ramka(Wektor<WEKTOR3D> srodekSymetrii, double promien);

    Ramka(Wektor<WEKTOR3D> min, Wektor<WEKTOR3D> max);

    void ustawWspolrzedne(std::vector<double> arg);

    int wezRozmiar() { return wspolrzedne.size(); }

    const double &operator[](int index) const { return wspolrzedne[index]; }

    double &operator[](int index) { return wspolrzedne[index]; }

};

bool czyKolizjaKulaProstopadloscian(Ramka kula, Ramka pros);
bool czyKolizjaKulaKula(Ramka kula1, Ramka kula2);