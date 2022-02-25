#include "MDP.h"
#include <iostream>



MDP::MDP(int r, int s, double krok, double faktor) : R(r), S(s), krok(krok), faktor(faktor)
{
	cil = nullptr;
	radky = new Stav*[R];
	Stav **pomRadky = new Stav * [R];
	
	for (int i = 0; i < R; i++)
	{
		this->radky[i] = new Stav(Souradnice(i, 0));
		pomRadky[i] = radky[i];
	}
	//pomRadky = radky;

	//vytvoreni obousmernych <- -> spojovych seznamu
	for (int i = 0; i < r; i++)
	{
		Stav* hlava = radky[i];
		for (int j = 1; j < s; j++)
		{
			Stav* pom = new Stav(Souradnice(i, j));
			hlava->vychod = pom;
			pom->zapad = hlava;
			hlava = pom;
		}
	}

	for (int j = 0; j < s; j++)
	{
		for (int i = 0; i < r; i++)
		{
			pomRadky[i]->jih = (i == r - 1) ? nullptr : pomRadky[i + 1];
			pomRadky[i]->sever = (i == 0) ? nullptr : pomRadky[i - 1];
		}
		for (int i = 0; i < r; i++)
		{
			pomRadky[i] = pomRadky[i]->vychod;
		}
	}
}

Stav* MDP::najdi(Souradnice xy)
{
	if (!mimo(xy))
	{
		Stav* pom = this->radky[xy.x];
		int i = 0;
		while (i < xy.y)
		{
			pom = pom->vychod;
			i++;
		}
		return pom;
		
	}
	return nullptr;
}

void MDP::nastavOdmenu(Souradnice xy, double odmena)
{
	Stav* pom = najdi(xy);
	if (pom)
	{
		pom->odmena = odmena;
		pom->koncovy = true;
	}
	if (cil == nullptr || cil->odmena < odmena)
		cil = pom;
}

void MDP::nastavPristupnost(Souradnice xy, bool pristupny)
{
	Stav* pom = najdi(xy);
	if (pom)
	{
		pom->pristupny = pristupny;
		pom->odmena = DBL_MIN;
		pom->optSmer = -1;
	}
}

MDP::~MDP()
{
	Stav* pom;
	Stav* p;
	for (int i = 0; i < R; i++)
	{
		p = radky[i];
		for (int j = 0; j < S; j++)
		{
			pom = p->vychod;
			delete p;
			p = pom;
		}
	}
	delete[] radky;
}

bool MDP::mimo(Souradnice xy)
{
	if (xy.x < 0 || xy.y < 0)
		return true;
	if (xy.x > this->R || xy.y > this->S)
		return true;
	return false;
}

void MDP::print()
{
	for (int i = 0; i < R; i++)
	{
		Stav* pom = this->radky[i];
		for (int j = 0; j < S; j++)
		{
			std::cout.precision(2);
			if(pom->pristupny || pom->koncovy)
				std::cout << pom->odmena << " ";
			else
                std::cout << "x ";
			pom = pom->vychod;
		}
		std::cout<<std::endl;
	}
	std::cout << std::endl;
}

char MDP::smer(Stav* pom)
{
	int i = pom->optSmer;
	switch (i)
	{
	case -2:
		return pom->odmena;
	case -1:
		return 'x';
	case 0:
		return '^';
	case 1:
		return 'v';
	case 2: 
		return '>';
	case 3:
		return '<';
    default:
        return '.';
	}
}

void MDP::prints()
{
	for (int i = 0; i < R; i++)
	{
		Stav* pom = this->radky[i];
		for (int j = 0; j < S; j++)
		{
			if (!pom->pristupny)
				std::cout << "x ";
			else
				std::cout << smer(pom) << " ";
			pom = pom->vychod;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void MDP::vyres(double epsilon)
{
	std::vector<Stav*> stavy;
	std::vector<double> U_predchozi;
	vytvorSeznamStavu(stavy, U_predchozi);
	do
	{
        for (unsigned int j = 0; j < stavy.size(); j++)
		{
			U_predchozi.at(j) = stavy.at(j)->odmena;
			stavy.at(j)->spoctiSmer(faktor, krok);
		}
		this->print();
	} while (!konverguje(stavy, U_predchozi, epsilon));
}

bool MDP::konverguje(std::vector<Stav*>& stavy, std::vector<double>& U_predchozi, double epsilon)
{
    for (unsigned int i = 0; i < stavy.size(); i++)
	{
		double delta = stavy.at(i)->odmena - U_predchozi.at(i);
        if (std::abs(delta) > epsilon)
			return false;
	}
	return true;
}

void MDP::vytvorSeznamStavu(std::vector<Stav*>& stavy, std::vector<double>& U_predchozi)
{
	Stav* pom;
	std::queue<Stav*> fronta;
	pridejSousedy(fronta, cil);
	while (!fronta.empty())
	{
		pom = fronta.front();
		fronta.pop();
		pridejSousedy(fronta, pom);
		stavy.push_back(pom);
		U_predchozi.push_back(pom->odmena);
	}
	for (int i = 0; i < stavy.size(); i++) stavy.at(i)->pristupny = true;
}

void MDP::pridejSousedy(std::queue<Stav*>& fronta, Stav* pom)
 {
	Stav* soused;
	soused = pom->sever;
	if (soused && soused->pristupny && !soused->koncovy)
	{
		fronta.push(soused);
		soused->pristupny = false;
	}
	soused = pom->jih;
	if (soused && soused->pristupny && !soused->koncovy)
	{
		fronta.push(soused);
		soused->pristupny = false;
	}
	soused = pom->zapad;
	if (soused && soused->pristupny && !soused->koncovy)
	{
		fronta.push(soused);
		soused->pristupny = false;
	}
	soused = pom->vychod;
	if (soused && soused->pristupny && !soused->koncovy)
	{
		fronta.push(soused);
		soused->pristupny = false;
	}
}
