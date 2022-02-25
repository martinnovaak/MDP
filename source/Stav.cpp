#include "Stav.h"


void Stav::max()
{
	int index = 0;
	for (int i = 1; i < 4; i++)
	{
		if (hodnoty[index] < hodnoty[i])
		{
			index = i;
		}
	}
	optSmer = index;
	odmena = hodnoty[index];
}

void Stav::spoctiSmer(double koef, double krok)
{
	if (pristupny)
	{
		double se = (this->sever == nullptr || this->sever->pristupny == false) ? this->odmena : this->sever->odmena;
		double ji = (this->jih == nullptr || this->jih->pristupny == false) ? this->odmena : this->jih->odmena;
		double za = (this->zapad == nullptr || this->zapad->pristupny == false) ? this->odmena : this->zapad->odmena;
		double vy = (this->vychod == nullptr || this->vychod->pristupny == false) ? this->odmena : this->vychod->odmena;

		hodnoty[0] = koef * (pravdepodobnost[0] * se + pravdepodobnost[1] * vy + pravdepodobnost[2] * za + pravdepodobnost[3] * ji) - krok;
		hodnoty[1] = koef * (pravdepodobnost[3] * se + pravdepodobnost[2] * vy + pravdepodobnost[1] * za + pravdepodobnost[0] * ji) - krok;
		hodnoty[2] = koef * (pravdepodobnost[1] * se + pravdepodobnost[0] * vy + pravdepodobnost[3] * za + pravdepodobnost[2] * ji) - krok;
		hodnoty[3] = koef * (pravdepodobnost[2] * se + pravdepodobnost[3] * vy + pravdepodobnost[0] * za + pravdepodobnost[1] * ji) - krok;
		max();
	}
}