#ifndef SPIELFELD_H
#define SPIELFELD_H

#include <array>
#include <time.h>
#include <vector>

using namespace std;

class Spielfeld{
public:
    static const int SIZE = 12;

    enum Belegung{Verdeckt, Mine, Aufgedeckt, Markiert};
    struct Feld{
        Belegung belegung;
        int nachbar_anzahl;
    };
    array<array<Feld, SIZE>, SIZE> spielfeld;

    Spielfeld(){
        srand(time(NULL));
    }

    void initialisieren(int& pMinen_anzahl);
    void darstellen(bool& pdebug);
    bool hit(int& x, int& y);
    bool validateInput(int& i1, int& i2);
    void aufdecken(int& x, int& y);
    bool nachbarnChecken(int& pfelder_anzahl);
    void mark_feld(int& x, int& y);

private:
    Feld& rand_feld();

    int mod(int x,int y);
    void count_nachbarn(Feld& feld, int y, int x);
    bool aufgedeckterLeererNachbar(int x, int y);

};
#endif // SPIELFELD_H
