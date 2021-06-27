#include "Ramka.h"

Ramka::Ramka() {
    wspolrzedne.push_back(0);
    wspolrzedne.push_back(0);
    wspolrzedne.push_back(0);
    wspolrzedne.push_back(0);
}

Ramka::Ramka(Wektor<WEKTOR3D> srodekSymetrii, double promien) {
    wspolrzedne.push_back(srodekSymetrii[0]);
    wspolrzedne.push_back(srodekSymetrii[1]);
    wspolrzedne.push_back(srodekSymetrii[2]);
    wspolrzedne.push_back(promien);
}

Ramka::Ramka(Wektor<WEKTOR3D> min, Wektor<WEKTOR3D> max) {
    wspolrzedne.push_back(min[0]);
    wspolrzedne.push_back(max[0]);
    wspolrzedne.push_back(min[1]);
    wspolrzedne.push_back(max[1]);
    wspolrzedne.push_back(min[2]);
    wspolrzedne.push_back(max[2]);
}

void Ramka::ustawWspolrzedne(std::vector<double> arg) {
    for (int i = 0; i < arg.size(); ++i) {
        wspolrzedne[i] = arg[i];
    }
}

Ramka::Ramka(const std::vector<double> &wspolrzedne) : wspolrzedne(wspolrzedne) {}

bool czyKolizjaKulaProstopadloscian(Ramka kula, Ramka pros) {
    double x = std::max(pros[0], std::min(kula[0], pros[1]));
    double y = std::max(pros[2], std::min(kula[1], pros[3]));
    double z = std::max(pros[4], std::min(kula[2], pros[5]));

    double dystans = sqrt((x - kula[0]) * (x - kula[0]) +
                          (y - kula[1]) * (y - kula[1]) +
                          (z - kula[2]) * (z - kula[2]));
    return dystans < kula[3];
}

bool czyKolizjaKulaKula(Ramka kula1, Ramka kula2) {
    double dystans = sqrt((kula1[0] -kula2[0]) * (kula1[0] -kula2[0]) +
                          (kula1[1] -kula2[1]) * (kula1[1] -kula2[1]) +
                          (kula1[2] -kula2[2]) * (kula1[2] -kula2[2]));
    return dystans < (kula1[3] + kula2[3]);
}
