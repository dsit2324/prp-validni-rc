#include <iostream>
#include <limits>
#include <string>
#include "rc.h"

bool jePrestupny(int rok) {
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
}

bool jePlatneDatum(int rok, int mesic, int den) {
    if (mesic < 1 || mesic > 12) return false;
    if (den < 1) return false;

    if (mesic == 2) {
        if (jePrestupny(rok)) return den <= 29;
        return den <= 28;
    }

    if (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11) {
        return den <= 30;
    }

    return den <= 31;
}

int main() {
    while (true) {
        int rok, mesic, den;
        int pohlaviInt;
        int trojcisli;
        char pohlavi;

        std::cout << "Generovani fiktivniho rodneho cisla\n";
        std::cout << "-----------------------------------\n";

        // rok
        while (true) {
            std::cout << "Zadej rok v intervalu 1954 a 2053: ";
            if (!(std::cin >> rok)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (rok >= 1954 && rok <= 2053) break;
        }

        // mesic
        while (true) {
            std::cout << "Zadej mesic v intervalu 1 a 12: ";
            if (std::cin >> mesic && mesic >= 1 && mesic <= 12) break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // den
        while (true) {
            std::cout << "Zadej den v intervalu 1 a 31: ";
            if (!(std::cin >> den)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (jePlatneDatum(rok, mesic, den)) break;
        }

        // pohlavi
        while (true) {
            std::cout << "Zadej pohlavi (0 - zena, 1 - muz) v intervalu 0 a 1: ";
            if (std::cin >> pohlaviInt && (pohlaviInt == 0 || pohlaviInt == 1)) {
                pohlavi = (pohlaviInt == 0) ? 'Z' : 'M';
                break;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // trojcisli
        while (true) {
            std::cout << "Zadej trojcisli za lomitkem v intervalu 0 a 999: ";
            if (std::cin >> trojcisli && trojcisli >= 0 && trojcisli <= 999) break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // generovani rodneho cisla
        rc r;
        std::string vysledek = r.vygeneruj(rok, mesic, den, pohlavi, trojcisli);

        std::cout << "Bylo vytvoreno validni rodne cislo: " << vysledek << "\n\n";

        // OPAKOVANI
        std::cout << "Pro opakovane zadani rodneho cisla stiskni Enter\n";

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (std::cin.get() != '\n') break;

        std::cout << "\n";
    }

    return 0;
}
