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

	char smer(Stav* pom);

	void pridejSousedy(std::queue<Stav*>& fronta, Stav* stav);
	void vytvorSeznamStavu(std::vector<Stav*>& vector, std::vector<double>& U);
	bool konverguje(std::vector<Stav*>& vector, std::vector<double>& U, double eps);
public:
    MDP(int R, int S, double krok, double faktor);
	~MDP();

	void nastavOdmenu(Souradnice xy, double odmena);
	void nastavPristupnost(Souradnice xy, bool pristupny);
	bool mimo(Souradnice xy);

	void vyres(double epsilon);

	void print();
	void prints();
};
