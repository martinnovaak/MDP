#ifndef STAV_H
#define STAV_H

#include <float.h>

struct Souradnice
{
    int x;
    int y;

    Souradnice(int x, int y) : x(x), y(y) {};
};

//kazdy Stav {state} ma:
// 1. souradnice (pozici v grafu)
// 2. akce {action} (ukazatele na sousedy - vysledek akce)
// 3. odmenu {reward}
// 4  hodnotovou fci
class Stav
{
private:
    Souradnice xy; //souradnice
    // akce
    Stav* sever;  //0
    Stav* jih;	  //1
    Stav* vychod; //2
    Stav* zapad;  //3

    //R(S)
    double odmena;
    //hodnotova fce
    double hodnoty[4];
    int optSmer;

    bool pristupny;
    bool koncovy;

    double pravdepodobnost[4] = { 0.8, 0.1, 0.1, 0.0 };



    //fce na vypocet maximalizaci hodnotove fce
    //(nalezeni maxima ze vsech smeru)
    void max();

    void spoctiSmer(double koef, double krok);

    friend class MDP;
    friend class MainWindow;
public:
    Stav(Souradnice xy, double odmena = 0.0) : xy(xy), odmena(odmena), optSmer(-1), pristupny(true), koncovy(false)
    {
        sever = jih = vychod = zapad = nullptr;
        for (int i = 0; i < 4; i++)
            hodnoty[i] = DBL_MIN;
    }
};

#endif // STAV_H
