#ifndef RC_H
#define RC_H

#include <string>
#include <ostream>

using std::string;

class rc {
public:
    rc();

    string get_rodneCislo() const;

    bool set_rodneCislo(const string&);

    // generovani RC
    string vygeneruj(int rok, int mesic, int den, char pohlavi, int trojcisli);

    // dekodovani RC
    void rozparsuj(int &rok, int &mesic, int &den, char &pohlavi) const;

private:
    string rodneCislo;

    static bool jeValidni(const string&);
};

std::ostream &operator<<(std::ostream &os, const rc &c);

#endif
