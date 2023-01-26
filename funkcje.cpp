#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "funkcje.h"

struct MVP {
    int gen;
    std::string trasa;
    double fitness;
};

struct individual {
    std::string gnome;
    double fitness;
};

int rand_num(int start, int end)
{
    int r = end - start;
    int rnum = start + rand() % r;
    return rnum;
}

bool repeat(std::string s, char ch)
{
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ch)
            return true;
    }
    return false;
}

std::string mutatedGene(std::string gnome, ww distances)
{
    while (true) {
        int r = rand_num(1, distances.size());
        int r1 = rand_num(1, distances.size());
        if (r1 != r) {
            char temp = gnome[r];
            gnome[r] = gnome[r1];
            gnome[r1] = temp;
            break;
        }
    }
    return gnome;
}

std::string create_gnome(ww distances)
{
    std::string gnome = "0";
    while (true) {
        if (gnome.size() == distances.size()) {
            gnome += gnome[0];
            break;
        }
        int temp = rand_num(1, distances.size());
        if (!repeat(gnome, (char)(temp + 48)))
            gnome += (char)(temp + 48);
    }
    return gnome;
}

double cal_fitness(std::string gnome, ww distances)
{
    double f = 0;
    for (int i = 0; i < gnome.size() - 1; i++) {
        f += distances[gnome[i] - 48][gnome[i + 1] - 48];
    }
    return f;
}

int cooldown(int wkonca)
{
    return (95 * wkonca) / 100;
}

bool lessthan(individual t1, individual t2)
{
    return t1.fitness < t2.fitness;
}

outputv TSPUtil(ww distances, int POP_SIZE, int gen_thres)
{
    // Numer generacji
    int gen = 1;

    std::vector<individual> population;
    outputv dane;
    individual temp;

    // Toworzenie puli populacji
    for (int i = 0; i < POP_SIZE; i++) {
        temp.gnome = create_gnome(distances);
        temp.fitness = cal_fitness(temp.gnome, distances);
        population.push_back(temp);
    }

    bool found = false;
    int w_konca = 100000;

    // Mutacja i krzyzowanie
    while (w_konca > 1000 && gen <= gen_thres) {
        sort(population.begin(), population.end(), lessthan);
        MVP najlepszy;
        najlepszy.gen = gen;
        najlepszy.trasa = population[0].gnome;
        najlepszy.fitness = population[0].fitness;
        std::vector<individual> new_population;
        for (int i = 0; i < POP_SIZE; i++) {
            individual p1 = population[i];
            while (true) {
                std::string new_g = mutatedGene(p1.gnome, distances);
                individual new_gnome;
                new_gnome.gnome = new_g;
                new_gnome.fitness = cal_fitness(new_gnome.gnome, distances);

                if (new_gnome.fitness <= population[i].fitness) {
                    new_population.push_back(new_gnome);
                    break;
                }
                else {

                    // Accepting the rejected children at
                    // a possible probability above threshold.
                    float prob = pow(2.7,
                        -1 * ((float)(new_gnome.fitness
                            - population[i].fitness)
                            / w_konca));
                    if (prob > 0.3) {
                        new_population.push_back(new_gnome);
                        break;
                    }
                }
            }
        }

        w_konca = cooldown(w_konca);
        population = new_population;
        dane.push_back(najlepszy);
        gen++;
    }
    return dane;
}

ww dystans(graph mapa) {
    if (mapa.size() == 0) return {};
    double odleglosc = 0;   // deklaracja zmiennej odleg這sci
    ww odleglosci(mapa.size()); // deklaracja vektoru odleg這sci
    // p皻la wpisuj鉍a dane do vectora "odleglosci"
    for (auto& l : mapa) {
        for (auto& l2 : mapa) {
            odleglosc = sqrt(abs(pow((l2.second.first - l.second.first), 2) + pow((l2.second.second - l.second.second), 2))); // obliczanie odleg這sci
            odleglosci[l.first].push_back(odleglosc); // wpisanie odleg這sci do vectora "odleglosci"
        }
    }
    return odleglosci; // zwracanie vectora "odleg這sci"
}

void wypisz(outputv dane, std::string wynik) {
    std::ofstream wyjscie(wynik);
    for (auto& i : dane) {
        wyjscie << "Generacja " << i.gen << ", Dystans: " << i.fitness << std::endl;
        wyjscie << i.trasa << std::endl;
    }
}
