#include <chrono>
#include <thread>
#include "Scena.h"

bool petlaGry = true;
bool wyswietlonoOstrzezenie = false;

bool porownanieDoPrecyzji(double a, double b, double epsilon = 0.9);

Scena::Scena() {
    numerDrona = 0;
    drony.push_back(Dron());
    drony.push_back(Dron(1, Wektor<WEKTOR3D>({-150, 0, 0})));
    drony.push_back(Dron(1, Wektor<WEKTOR3D>({150, 0, 0})));
    drony[0].ustawKolor("#808000");
    drony[1].ustawKolor("#C71585");
    drony[2].ustawKolor("#B8860B");
    przeszkody.push_back(drony[0].wezRamke());
    przeszkody.push_back(drony[1].wezRamke());
    przeszkody.push_back(drony[2].wezRamke());
}

void Scena::rysuj() {
    petlaGry = true;
    using clock = std::chrono::steady_clock;
    auto next_frame = clock::now();
    narysujTrase();

    while(petlaGry) {
        next_frame += std::chrono::milliseconds(1000 / 60); // 60FPS
        if (komendy.empty()) { petlaGry = false; }
        else {
            animacja();
        }
        for (int i = 0; i < drony.size(); ++i) {
            drony[i].rysowanie();
        }

        for (int j = 0; j < elementyTerenu.size(); ++j) {
            elementyTerenu[j]->rysowanie();
        }

        for (int i = 0; i < trasa.size(); ++i) {
            trasa[i].rysowanie();
        }
        wykres.rysujWykres();
        std::this_thread::sleep_until(next_frame);
    }
}

void Scena::animacja() {
    switch (komendy[0].znak) {
        case 'W':
            drony[numerDrona].wzniesSie(komendy[0].wartosc);
            if (drony[numerDrona].wezSrodekSymetrii()[1] >= komendy[0].wartosc) {
                komendy.erase(komendy.begin());
            }
            break;
        case 'O':
            drony[numerDrona].obrocSie(komendy[0].wartosc);
            if (drony[numerDrona].wezPredkoscObrotu() == 0 &&
            porownanieDoPrecyzji(drony[numerDrona].wezOrientacje()[1], komendy[0].wartosc)){
                komendy.erase(komendy.begin());
                Wektor tmp = drony[numerDrona].wezOrientacje();
                tmp = drony[numerDrona].wezOrientacjaCalkowita() + tmp;
                drony[numerDrona].ustawOrientacjeCalkowita(tmp);
                drony[numerDrona].ustawOrientacje(Wektor<WEKTOR3D>());
            }
            break;
        case 'P':
            drony[numerDrona].lec();
            if (translacjaWykonana()) {
                drony[numerDrona].ustawTranslacjeCalkowita(Wektor());
                komendy.erase(komendy.begin());
            }
            break;
        case 'L':
            for (int i = 0; i < przeszkody.size(); ++i) {
                if (i == numerDrona) continue;
                if (przeszkody[i]->wezRozmiar() == 4) {
                    if (czyKolizjaKulaKula(*drony[numerDrona].wezRamke(), *przeszkody[i])) {
                        if (!wyswietlonoOstrzezenie) {
                            std::cout << "Nie mozna wyladowac! \n\n";
                            std::cout << "Kolizja z Dronem numer " << numerDrona << "\n\n";
                            std::cout << "Ustalam nowe miejsce ladowania\n";
                            wyswietlonoOstrzezenie = true;
                        }

                        komendy.insert(komendy.begin(), Komenda{'P', 5});
                        return;
                    }
                }
                if (przeszkody[i]->wezRozmiar() == 6) {
                    if (czyKolizjaKulaProstopadloscian(*drony[numerDrona].wezRamke(), *przeszkody[i])) {
                        if (!wyswietlonoOstrzezenie) {
                            std::cout << "Nie mozna wyladowac! \n\n";
                            std::cout << "Kolizja z " << typeid(*elementyTerenu[i - 3]).name() + 1 << "\n\n";
                            std::cout << "Ustalam nowe miejsce ladowania\n";
                            wyswietlonoOstrzezenie = true;
                        }
                        komendy.insert(komendy.begin(), Komenda{'P', 5});
                        return;
                    }
                }
            }
            drony[numerDrona].laduj();
            if (drony[numerDrona].wezSrodekSymetrii()[1] <= 0) {
                komendy.erase(komendy.begin());
                wyswietlonoOstrzezenie = false;
            }
            break;
        default:
            break;
    }

}

void Scena::obrot() {
    double kat = 0;
    std::cout << "Podaj kat obrotu: ";
    std::cin >> kat;
    if (drony[numerDrona].wezSrodekSymetrii()[1] > 2 || !komendy.empty()) { komendy.push_back(Komenda({'O', kat})); }
    else std::cout << "Nie mozna obrocic, gdy sie nie wystartowalo !\n";
}

void Scena::wystartuj() {
    double wysokosc = 0;
    std::cout << "Podaj wysokosc: ";
    std::cin >> wysokosc;
    if (drony[numerDrona].wezSrodekSymetrii()[1] < 2 || komendy.empty()) { komendy.push_back(Komenda({'W', wysokosc})); }
    else std::cout << "Dron juz wystartowal !\n";
}

void Scena::wybierzDrona() {
    for (int i = 0; i < drony.size(); ++i) {
        std::cout << "Dron nr " << i << ". Polozenie: " << drony[i].wezSrodekSymetrii();
        if (numerDrona == i) std::cout << "   <-- dron aktywny \n";
        else std::cout << "\n";
    }

    std::cout << "Podaj numer drona: ";
    std::cin >> numerDrona;
    if (numerDrona > drony.size() || numerDrona < 0) throw std::invalid_argument("Bledny index drona!\n");
}

void Scena::przesun() {
    double odleglosc = 0;
    std::cout << "Podaj odleglosc: ";
    std::cin >> odleglosc;
    if (drony[numerDrona].wezSrodekSymetrii()[1] > 2 || !komendy.empty()) { komendy.push_back(Komenda({'P', odleglosc})); }
    else std::cout << "Nie mozna leciec, gdy sie nie wystartowalo !\n";
}

void Scena::ladowanie() {
    if (drony[numerDrona].wezSrodekSymetrii()[1] > 2 || !komendy.empty()) { komendy.push_back(Komenda({'L', 0})); }
    else std::cout << "Nie mozna ladowac, gdy sie nie wystartowalo !\n";
}

void Scena::dodajPrzeszkode() {
    char opcja = ' ';
    double dlugosc = 1;
    double szerokosc = 1;
    double wysokosc = 1;
    double x = 0, z = 0;
    std::cout << "Wybierz rodzaj powierzchniowego elementu \n";
    std::cout << "1 - Gora z ostrym sztytem \n";
    std::cout << "2 - Gora z jednym lagodnym szczytem\n";
    std::cout << "3 - Plaskowyz \n";
    std::cout << "Wpisz opcje: ";
    std::cin >> opcja;
    std::cout << "Podaj dlugosc :" ;
    std::cin >> dlugosc;
    std::cout << "Podaj wysokosc :" ;
    std::cin >> wysokosc;
    std::cout << "Podaj szerokosc :" ;
    std::cin >> szerokosc;
    std::cout << "Podaj wspolrzedne srodka x: \n";
    std::cin >> x;
    std::cout << "Podaj wspolrzedne srodka z: \n";
    std::cin >> z;
    Wektor<WEKTOR3D> wspolrzedneSrodkaPrzeszkody({x, 0, z});

    switch (opcja) {
        case '1':
            elementyTerenu.push_back(new Ostroslup(dlugosc, wysokosc, szerokosc));
            break;
        case '2':
            elementyTerenu.push_back(new Zbocze(dlugosc, wysokosc, szerokosc));
            break;
        case '3':
            elementyTerenu.push_back(new Plaskowyz(dlugosc, wysokosc, szerokosc));
            elementyTerenu[elementyTerenu.size() - 1]->translacja(Wektor({0, wysokosc / 2, 0}));
            break;
    }
    elementyTerenu[elementyTerenu.size() - 1]->translacja(wspolrzedneSrodkaPrzeszkody);
    przeszkody.push_back(elementyTerenu[elementyTerenu.size() - 1]->wezRamke());
}

void Scena::usunPrzeszkode() {
    if (elementyTerenu.size() == 0) return;
    int numer = 0;
    for (int i = 0; i < elementyTerenu.size(); ++i) {
        std::cout << "Przeszkoda nr " << i << ". " << elementyTerenu[i]->wezSrodekSymetrii() << std::endl;
    }
    std::cout << "Podaj numer: ";
    std::cin >> numer;
    elementyTerenu[numer]->translacja(Wektor({100000, 100000, 0}));
    elementyTerenu[numer]->rysowanie();
    przeszkody.erase(przeszkody.begin() + 3 + numer);
    elementyTerenu.erase(elementyTerenu.begin() + numer);
}

bool Scena::translacjaWykonana() {
    bool x = porownanieDoPrecyzji(drony[numerDrona].wezTranslacjeCalkowita()[0],
                                  drony[numerDrona].policzTrase(komendy[0].wartosc)[0], 5);

    bool y = porownanieDoPrecyzji(drony[numerDrona].wezTranslacjeCalkowita()[1],
                                  drony[numerDrona].policzTrase(komendy[0].wartosc)[1], 5);

    bool z = porownanieDoPrecyzji(drony[numerDrona].wezTranslacjeCalkowita()[2],
                                  drony[numerDrona].policzTrase(komendy[0].wartosc)[2], 5);
    return x && y && z;
}

void Scena::narysujTrase() {
    for (int i = 0; i < trasa.size(); ++i) {
        trasa[i].ustawKolor("#FFFF0000");
        trasa[i].translacja(Wektor({1000000, 10000, 100000}));
        trasa[i].rysowanie();
    }

    std::string kolorDrona = drony[numerDrona].wezKolor();
    double kat = komendy[1].wartosc;
    Wektor orientacja({0, komendy[1].wartosc, 0});

    Wektor<WEKTOR3D> miejsceStartu = drony[numerDrona].wezSrodekSymetrii();
    trasa[0] = Wielokat<LINIA>({miejsceStartu, Wektor({0, komendy[0].wartosc, 0}) + miejsceStartu}, kolorDrona);

    Wektor miejsceLadowaniaDolne = drony[numerDrona].policzTrase(komendy[2].wartosc, orientacja);
    miejsceLadowaniaDolne = drony[numerDrona].wezSrodekSymetrii() + miejsceLadowaniaDolne;

    Wektor miejsceLadowaniaGorne = Wektor({0, komendy[0].wartosc, 0}) + miejsceLadowaniaDolne;

    trasa[1] = Wielokat<LINIA>({Wektor({0, komendy[0].wartosc, 0}) + miejsceStartu, miejsceLadowaniaGorne}, kolorDrona);
    trasa[2] = Wielokat<LINIA>({miejsceLadowaniaGorne, miejsceLadowaniaDolne}, kolorDrona);
}

void Scena::usunTrase() {
    trasa[0] = Wielokat<LINIA>({Wektor({99999, 9999, 9999}), Wektor({99998, 9998, 9998})}, KOLOR);
    trasa[1] = Wielokat<LINIA>({Wektor({99999, 9999, 9999}), Wektor({99998, 9998, 9998})}, KOLOR);
    trasa[2] = Wielokat<LINIA>({Wektor({99999, 9999, 9999}), Wektor({99998, 9998, 9998})}, KOLOR);

}

bool porownanieDoPrecyzji(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}
