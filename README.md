# MDP - Markovův rozhodovací proces
## Algoritmus
Implementovaný algoritmus se nachází v souborech MDP.h, MDP.cpp, Stav.h a Stav.cpp
### Použití algoritmu 
1) Instance se vytvoří pomocí `MDP instance(POCET RADKU, POCET SLOUPCU, KROK, FAKTOR);`.
2) Jedná-li se o nepřístupné pole (o překážku) nastaví se pomocí `instance.nastavPristupnost(Souradnice(X, Y), false);`.
3) Odměna koncových polí se dá nastavuje `instance.nastavOdmenu(Souradnice(X, Y), ODMENA);`.
4) Úloha se vyřeší příkazem `instance.vyres(epsilon);`, kde epsilon je povolená chyba algoritmu.
5) Výpis optimálních směrů se dá vypsat pomocí `instance.prints();`.
6) Hodnoty jednotlivých polí se dají vypsat pomocí `instance.print();`.

## Grafické rozhraní
V souborech mainwindow.h, mainwindow.cpp, dialog.h, dialog.cpp a main.cpp je jednoduché grafické rozhraní postavené na algoritmu.
