#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "funkcje.h"

struct MVP {
    int gen;
    std::string trasa;
    double fitness;
};

int main(int argc, char* argv[])
{
    if (argc == 9) {
        ww distances;
        int POP_SIZE;
        int gen_thres;
        std::string wejscie;
        std::string wynik;
        for (int i = 1; i < 9; i += 2) {
            std::string arg = argv[i];
            std::string temp = argv[i + 1];
            if (arg == "-g") {
                POP_SIZE = stoi(temp);
            }
            if (arg == "-n") {
                gen_thres = stoi(temp);
            }
            if (arg == "-i") {
                wejscie = temp;
            }
            if (arg == "-o") {
                wynik = temp;
            }

        }
        int punkt;          // deklaracja zmiennej dla miasta
        double x, y;        // deklaracja zmiennych miasta
        std::ifstream fin(wejscie);     // pobieranie danych z pliku
        if (fin) {
            graph punkty;    // deklaracja mapy
            std::string line; // deklaracja zmiennej dla lini
            while (std::getline(fin, line)) { //pętla wpisywania danych do mapy
                std::stringstream ss(line);
                ss >> punkt >> x >> y;
                punkty[punkt] = { x,y };
            }
            distances = dystans(punkty); // obliczanie odległości między miastami
            outputv dane;
            dane = TSP(distances, POP_SIZE, gen_thres);
            wypisz(dane, wynik);
        }
        else {
            std::cout << "Blad otwarcia pliku";
            return 1;
        }
    }
}
