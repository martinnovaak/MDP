#pragma once
#include "Stav.h"
#include <queue>

class MDP
{
private:
	int R;
	int S;
	Stav** radky;

	Stav* cil;
	Stav* najdi(Souradnice xy);

	//
	double krok;
	double faktor;

	void pridejSousedy(std::queue<Stav*>& fronta, Stav* stav);
	void vytvorSeznamStavu(std::vector<Stav*>& vector, std::vector<double>& U);
	bool konverguje(std::vector<Stav*>& vector, std::vector<double>& U, double eps);
    bool mimo(Souradnice xy);
public:
    MDP(int R, int S, double krok, double faktor);
	~MDP();

	void nastavOdmenu(Souradnice xy, double odmena);
	void nastavPristupnost(Souradnice xy, bool pristupny);
	void vyres(double epsilon);
    Stav * operator[](unsigned int i);
	void print();
	void prints();
    char smer(Stav* pom);
    bool jeCilovy(Stav * cil){return this->cil->odmena == cil->odmena;};
};
