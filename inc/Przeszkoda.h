#pragma once

#include "Obiekt.h"
#include "Ramka.h"

class Przeszkoda : public Obiekt {
protected:
    Ramka ramka;
public:
    Ramka *wezRamke() {
        return &ramka;
    }
};
