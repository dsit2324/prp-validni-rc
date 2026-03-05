#include <iostream>
#include <limits>
#include <string>
#include "rc.h"

// Kontrola přestupného roku
bool jePrestupny(int rok) {
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
}

// Maximální počet dní v měsíci
int maxDniVMesici(int rok, int mesic) {
    if (mesic == 2) {
        return jePrestupny(rok) ? 29 : 28;
    }
    if (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11) {
        return 30;
    }
    return 31;
}

// Funkce pro bezpečný vstup celého čísla
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
    while (true) {
        std::cout << "Generovani fiktivniho rodneho cisla\n";
        std::cout << "-----------------------------------\n";

        int rok = nactiInt("Zadej rok v intervalu 1954 a 2053: ", 1954, 2053);
        int mesic = nactiInt("Zadej mesic v intervalu 1 a 12: ", 1, 12);

        int maxDni = maxDniVMesici(rok, mesic);
        int den = nactiInt("Zadej den v intervalu 1 a " + std::to_string(maxDni) + ": ", 1, maxDni);

        int pohlaviInt = nactiInt("Zadej pohlavi (0 - zena, 1 - muz) v intervalu 0 a 1: ", 0, 1);
        char pohlavi = (pohlaviInt == 0) ? 'Z' : 'M';

        int trojcisli = nactiInt("Zadej trojcisli za lomitkem v intervalu 0 a 999: ", 0, 999);
        int puvodniTrojcislo = trojcisli; // uložíme původní hodnotu

        rc r;
        std::string vysledek = r.vygeneruj(rok, mesic, den, pohlavi, trojcisli);

        std::cout << "Bylo vytvoreno validni rodne cislo: " << vysledek << "\n";

        // Hlaska, pokud se posledni cislice trojcisli upravila
        if (puvodniTrojcislo != trojcisli) {
            std::cout << "Upozorneni: posledni cislice trojcisli byla upravena na 0 kvuli delitelnosti 11.\n";
        }

        // Parsování pro zobrazení dat a pohlaví
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
