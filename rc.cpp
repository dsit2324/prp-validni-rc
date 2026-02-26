#include "rc.h"

#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>

rc::rc() : rodneCislo("") {
}

string rc::get_rodneCislo() const {
    return rodneCislo;
}

bool rc::set_rodneCislo(string rc) {
    if (jeValidni(rc)) {
        rodneCislo = rc;
        return true;
    }
    return false;
}

bool rc::jeValidni(string cislo) {
    if (cislo.length() != 10) {
        return false;
    }
    if (!std::all_of(cislo.begin(), cislo.end(), ::isdigit)) {
        return false;
    }
    int prvnich9 = stoi(cislo.substr(0, 9));
    int kontrola = stoi(cislo.substr(9, 1));
    if (prvnich9 % 11 == kontrola) {
        return true;
    }
    if (prvnich9 % 11 == 10 && kontrola == 0) {
        return true;
    }
    return false;
}

// 🔥 GENEROVANI
string rc::vygeneruj(int rok, int mesic, int den, char pohlavi, int trojcisli) {
    std::stringstream ss;

    int r = rok % 100;

    if (pohlavi == 'Z' || pohlavi == 'z') {
        mesic += 50;
    }

    ss << std::setw(2) << std::setfill('0') << r
            << std::setw(2) << std::setfill('0') << mesic
            << std::setw(2) << std::setfill('0') << den
            << std::setw(3) << std::setfill('0') << trojcisli;

    string prvnich9 = ss.str();
    int cislo9 = stoi(prvnich9);
    int zbytek = cislo9 % 11;

    if (zbytek == 10) {
        srand(time(nullptr));
        do {
            trojcisli = rand() % 1000;

            std::stringstream ss2;
            ss2 << std::setw(2) << std::setfill('0') << r
                    << std::setw(2) << std::setfill('0') << mesic
                    << std::setw(2) << std::setfill('0') << den
                    << std::setw(3) << std::setfill('0') << trojcisli;

            prvnich9 = ss2.str();
            cislo9 = stoi(prvnich9);
            zbytek = cislo9 % 11;
        } while (zbytek == 10);
    }

    int posledni = (zbytek == 10) ? 0 : zbytek;

    rodneCislo = prvnich9 + std::to_string(posledni);
    return rodneCislo;
}

// výpis
std::ostream &operator<<(std::ostream &os, const rc &c) {
    os << c.get_rodneCislo();
    return os;
}
