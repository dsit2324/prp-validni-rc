#include <iostream>
#include <limits>
#include <string>
#include "rc.h"

bool jePrestupny(int rok) {
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
}

int maxDniVMesici(int rok, int mesic) {
    if (mesic == 2) {
        return jePrestupny(rok) ? 29 : 28;
    }

    if (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11) {
        return 30;
    }

    return 31;
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
                std::cout << "Chyba: zadej cislo.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (rok >= 1954 && rok <= 2053) {
                break;
            }
            else {
                std::cout << "Chyba: rok musi byt v intervalu 1954 - 2053.\n";
            }
        }

        // mesic
        while (true) {
            std::cout << "Zadej mesic v intervalu 1 a 12: ";
            if (std::cin >> mesic && mesic >= 1 && mesic <= 12) {
                break;
            }

            std::cout << "Chyba: mesic musi byt v intervalu 1 - 12.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // den
        while (true) {
            int maxDni = maxDniVMesici(rok, mesic);

            std::cout << "Zadej den v intervalu 1 a " << maxDni << ": ";

            if (!(std::cin >> den)) {
                std::cout << "Chyba: zadej cislo.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (den >= 1 && den <= maxDni) {
                break;
            }
            else {
                std::cout << "Chyba: den musi byt v intervalu 1 - " << maxDni << ".\n";
            }
        }

        // pohlavi
        while (true) {
            std::cout << "Zadej pohlavi (0 - zena, 1 - muz) v intervalu 0 a 1: ";
            if (std::cin >> pohlaviInt && (pohlaviInt == 0 || pohlaviInt == 1)) {
                pohlavi = (pohlaviInt == 0) ? 'Z' : 'M';
                break;
            }

            std::cout << "Chyba: zadej 0 pro zenu nebo 1 pro muze.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // trojcisli
        while (true) {
            std::cout << "Zadej trojcisli za lomitkem v intervalu 0 a 999: ";
            if (std::cin >> trojcisli && trojcisli >= 0 && trojcisli <= 999) {
                break;
            }

            std::cout << "Chyba: trojcisli musi byt v intervalu 0 - 999.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // generovani rodneho cisla
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
