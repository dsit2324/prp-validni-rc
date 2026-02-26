#ifndef RC_H
#define RC_H

#include <string>
#include <ostream>

using std::string;

class rc {
public:
    rc();

    string get_rodneCislo() const;

    bool set_rodneCislo(string);

    // generovani RC
    string vygeneruj(int rok, int mesic, int den, char pohlavi, int trojcisli);

private:
    string rodneCislo;

    static bool jeValidni(string);
};

std::ostream &operator<<(std::ostream &os, const rc &c);

#endif
