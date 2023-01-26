/** @file
*/

#ifndef FUNKCJE_H
#define FUNKCJE_H

struct MVP;

struct individual;

typedef std::map<int, std::pair<double, double>> graph;

typedef std::vector<std::vector<double>> ww;

typedef std::vector<MVP> outputv;

int rand_num(int start, int end);

bool repeat(std::string s, char ch);

std::string mutatedGene(std::string gnome, ww distances);

std::string create_gnome(ww distances);

double cal_fitness(std::string gnome, ww distances);

double cal_fitness(std::string gnome, ww distances);

int cooldown(int wkonca);

bool lessthan(individual t1, individual t2);

outputv TSPUtil(ww distances, int POP_SIZE, int gen_thres);

ww dystans(graph mapa);

void wypisz(outputv dane, std::string wynik);

#endif // !FUNKCJE_H
