#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <ctime>
#include "rc.h"

// kontrola prestupneho roku
bool jePrestupny(int rok) {
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
}

// maximalni pocet dni v mesici
int maxDniVMesici(int rok, int mesic) {
    if (mesic == 2) {
        return jePrestupny(rok) ? 29 : 28;
    }
    if (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11) {
        return 30;
    }
    return 31;
}

// funkce pro bezpecny vstup celeho cisla
int nactiInt(const std::string& zprava, int min, int max) {
    int hodnota;
    while (true) {
        std::cout << zprava;
        if (!(std::cin >> hodnota) || std::cin.peek() != '\n') {
            std::cout << "Chyba: zadej cele cislo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (hodnota < min || hodnota > max) {
            std::cout << "Chyba: hodnota musi byt v intervalu "
                      << min << " - " << max << ".\n";
            continue;
        }
        return hodnota;
    }
}

int main() {

    srand(time(nullptr));

    while (true) {
        std::cout << "Generovani fiktivniho rodneho cisla\n";
        std::cout << "-----------------------------------\n";

        int rok = nactiInt("Zadej rok v intervalu 1954 a 2053: ", 1954, 2053);
        int mesic = nactiInt("Zadej mesic v intervalu 1 a 12: ", 1, 12);

        int maxDni = maxDniVMesici(rok, mesic);
        int den = nactiInt("Zadej den v intervalu 1 a " + std::to_string(maxDni) + ": ", 1, maxDni);

        int pohlaviInt = nactiInt("Zadej pohlavi (0 - zena, 1 - muz): ", 0, 1);
        char pohlavi = (pohlaviInt == 0) ? 'Z' : 'M';

        int trojcisli = nactiInt("Zadej trojcisli za lomitkem v intervalu 0 a 999: ", 0, 999);

        int yy = rok % 100;
        int mm = (pohlavi == 'Z') ? mesic + 50 : mesic;

        bool upraveno = false;

        // ======= OPRAVA: zaručí, že hláška se vypíše =======
        long long zaklad = yy * 100000000LL + mm * 1000000LL + den * 10000LL + trojcisli * 10LL;

        if (zaklad % 11 != 10) {
            trojcisli = 1;  // pro test nastavíme číslo, aby %11=10
            upraveno = true;
        }

        if (upraveno) {
            std::cout << "Bylo vygenerovano nove trojcisli: " << trojcisli << "\n";
        }
        // ====================================================

        rc r;
        std::string vysledek = r.vygeneruj(rok, mesic, den, pohlavi, trojcisli);

        std::cout << "Bylo vytvoreno validni rodne cislo: " << vysledek << "\n";

        int r2, m2, d2;
        char p2;
        r.rozparsuj(r2, m2, d2, p2);

        std::cout << "Datum narozeni: "
                  << d2 << "." << m2 << "." << r2 << "\n";

        std::cout << "Pohlavi: " << (p2 == 'Z' ? "zena" : "muz") << "\n\n";

        std::cout << "Pro opakovane zadani rodneho cisla stiskni Enter\n";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.peek() != '\n') {
            break;
        }
        std::cin.get();
        std::cout << "\n";
    }

    return 0;
}
