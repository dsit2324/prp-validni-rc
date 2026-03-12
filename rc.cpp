#include "rc.h"

#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream> // pro vypis hlasky

// konstruktor
rc::rc() : rodneCislo("") {}

// getter
string rc::get_rodneCislo() const {
    return rodneCislo;
}

// setter
bool rc::set_rodneCislo(const string& rc) {
    if (jeValidni(rc)) {
        rodneCislo = rc;
        return true;
    }
    return false;
}

// validace rodneho cisla
bool rc::jeValidni(const string& cislo) {
    if (cislo.length() != 10) return false;
    if (!std::all_of(cislo.begin(), cislo.end(), ::isdigit)) return false;

    int rok = stoi(cislo.substr(0, 2));
    int mesic = stoi(cislo.substr(2, 2));
    int den = stoi(cislo.substr(4, 2));

    int skutecnyMesic = mesic;

    if (mesic >= 71 && mesic <= 82) skutecnyMesic -= 70;
    else if (mesic >= 51 && mesic <= 62) skutecnyMesic -= 50;
    else if (mesic >= 21 && mesic <= 32) skutecnyMesic -= 20;

    if (skutecnyMesic < 1 || skutecnyMesic > 12) return false;
    if (den < 1 || den > 31) return false;

    int prvnich9 = stoi(cislo.substr(0, 9));
    int kontrola = cislo[9] - '0';

    int zbytek = prvnich9 % 11;

    if (zbytek == 10) return kontrola == 0;
    return kontrola == zbytek;
}

// generovani rodneho cisla
string rc::vygeneruj(int rok, int mesic, int den, char pohlavi, int trojcisli) {
    std::stringstream ss;
    int r = rok % 100;

    if (pohlavi == 'Z' || pohlavi == 'z') mesic += 50;

    ss << std::setw(2) << std::setfill('0') << r
       << std::setw(2) << std::setfill('0') << mesic
       << std::setw(2) << std::setfill('0') << den
       << std::setw(3) << std::setfill('0') << trojcisli;

    string prvnich9 = ss.str();
    int cislo9 = stoi(prvnich9);
    int zbytek = cislo9 % 11;

    int posledni;
    bool upraveno = false;

    if (zbytek == 10) {
        posledni = 0;
        upraveno = true;
    } else {
        posledni = zbytek;
    }

    rodneCislo = prvnich9 + std::to_string(posledni);

    return rodneCislo;
}

// rozparsovani rodneho cisla
void rc::rozparsuj(int &rok, int &mesic, int &den, char &pohlavi) const {
    int r = stoi(rodneCislo.substr(0, 2));
    int m = stoi(rodneCislo.substr(2, 2));
    int d = stoi(rodneCislo.substr(4, 2));

    if (m >= 71) {
        mesic = m - 70;
        pohlavi = 'Z';
    } else if (m >= 51) {
        mesic = m - 50;
        pohlavi = 'Z';
    } else if (m >= 21) {
        mesic = m - 20;
        pohlavi = 'M';
    } else {
        mesic = m;
        pohlavi = 'M';
    }

    den = d;

    if (r <= 53) rok = 2000 + r;
    else rok = 1900 + r;
}

// operator <<
std::ostream &operator<<(std::ostream &os, const rc &c) {
    os << c.get_rodneCislo();
    return os;
}
