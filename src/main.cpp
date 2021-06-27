#include "Scena.h"
#include "Przeszkoda.h"

void wyswietlMenu();

int main(){
    Scena scena;
    char opcja = ' ';

    wyswietlMenu();

    do {
        std::cout << "Wpisz opcje: ";
        std::cin >> opcja;

        switch (opcja) {
            case 'D':
            case 'd':
                scena.wybierzDrona();
                break;
            case 'P':
            case 'p':
                scena.wystartuj();
                scena.obrot();
                scena.przesun();
                scena.ladowanie();
                scena.rysuj();
                break;
            case 'U':
            case 'u':
                scena.usunPrzeszkode();
                break;
            case 'E':
            case 'e':
                scena.dodajPrzeszkode();
                break;
            case 'M':
            case 'm':
                wyswietlMenu();
                break;
            case 'K':
            case 'k':
                break;
            default:
                std::cout << "Brak takiej opcji! \n";
                break;
        }

    } while (opcja != 'k' && opcja != 'K');



    return 0;
}

void wyswietlMenu() {
    std::cout << "D - wybor drona\n";
    std::cout << "P - przelot drona\n";
    std::cout << "E - dodaj element powierzchni\n";
    std::cout << "U - usun element powierzchni\n";
    std::cout << "M - menu\n";
    std::cout << "K - koniec\n";
}
