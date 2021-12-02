#include "spielfeld.h"


#include <array>
#include <time.h>
#include <vector>
#include <iostream>
#include <iomanip>


using namespace std;

void Spielfeld::initialisieren(int& pMinen_anzahl){
    for(int y=0;y<SIZE;y++){
        for(int x=0;x<SIZE;x++){
            spielfeld.at(y).at(x).belegung = Verdeckt;
            spielfeld.at(y).at(x).nachbar_anzahl = 0;
        }
    }

    for(int i=0;i<pMinen_anzahl;i++){
        Feld& minen_feld = rand_feld();
        minen_feld.belegung = Mine;
    }
    for(int y=0;y<SIZE;y++){
        for(int x=0;x<SIZE;x++){
            count_nachbarn(spielfeld.at(y).at(x), y,x);
        }
    }
}

void Spielfeld::darstellen(bool& pdebug){
    for(int y=0;y<SIZE;y++){
        cout << std::setfill('0') << std::setw(2) << y+1;
        cout << " |";
        for(int x=0;x<SIZE;x++){
            Feld feld = spielfeld.at(y).at(x);
            if(feld.belegung == Mine && pdebug){
                cout << " X";
            }else if(feld.belegung == Aufgedeckt){
                if(feld.nachbar_anzahl == 0){
                    cout << " .";
                }else{
                    cout << " " << feld.nachbar_anzahl;
                }
            }else if(feld.belegung == Verdeckt || (!pdebug && feld.belegung == Mine)){
               cout << " *";
            }else if(feld.belegung == Markiert){
                cout << " O";
            }
        }
        cout << endl;
    }

    //für die unteren Indices
    cout << "    ";
    for(int i=0;i<=SIZE*2;i++){
        cout << "_";
    }
    cout << endl << "     ";
    for(int i=0;i<SIZE;i++){
        cout << i+1 << " ";
    }
    cout << endl;
}
bool Spielfeld::hit(int& x, int& y){
    Feld pickedFeld = spielfeld.at(y).at(x);
    if(pickedFeld.belegung == Mine){
        return true;
    }
    return false;
}
bool Spielfeld::validateInput(int& i1, int& i2){
    if(i1 < SIZE && i1 > -1){
        if(i2 < SIZE && i2 > -1){
            return true;
        }
    }
    return false;
}
void Spielfeld::aufdecken(int& x, int& y){
    Feld& pickedFeld = spielfeld.at(y).at(x);
    pickedFeld.belegung = Aufgedeckt;
}
bool Spielfeld::nachbarnChecken(int& pfelder_anzahl){
    bool edited = false;
    for(int y=0;y<SIZE;y++){
        for(int x=0;x<SIZE;x++){
            Feld& current_feld = spielfeld.at(y).at(x);
            if(current_feld.belegung == Verdeckt || current_feld.belegung == Markiert){
                if(aufgedeckterLeererNachbar(x,y)){
                    current_feld.belegung = Aufgedeckt;
                    edited = true;
                    pfelder_anzahl-=1;
                }
            }
        }
    }
    return edited;
}
void Spielfeld::mark_feld(int& x, int& y){
    Feld& pickedFeld = spielfeld.at(y).at(x);
    if(pickedFeld.belegung == Verdeckt){
        pickedFeld.belegung = Markiert;
    }
}




Spielfeld::Feld& Spielfeld::rand_feld(){
    while(true){
        int y = rand() % SIZE;
        int x = rand() % SIZE;
        Feld& picked = spielfeld.at(y).at(x);
        if(picked.belegung != Mine){
            return picked;
        }
    }
}

int Spielfeld::mod(int x,int y){
       int c = x % y;
       return (c<0) ? c+y : c;
}
void Spielfeld::count_nachbarn(Feld& feld, int y, int x){
    for(int x_Offset=-1;x_Offset<=1;x_Offset++){
        for(int y_Offset=-1;y_Offset<=1;y_Offset++){
            int y_look = y+y_Offset;
            int x_look = x+x_Offset;

            if(y_look < SIZE && y_look > -1){//nicht außerhalb der Spielfeldes
                if(x_look < SIZE && x_look > -1){//nicht außerhalb der Spielfeldes
                    if(!(x_look == x && y_look == y)){//ist nicht das eigene Feld
                        Feld nachbar = spielfeld.at(y_look).at(x_look);
                        if(nachbar.belegung == Mine){
                            feld.nachbar_anzahl += 1;
                        }
                    }
                }
            }
        }
    }
}
bool Spielfeld::aufgedeckterLeererNachbar(int x, int y){
    bool found_nachbar = false;
    for(int x_Offset=-1;x_Offset<=1;x_Offset++){
        for(int y_Offset=-1;y_Offset<=1;y_Offset++){
            int y_look = y+y_Offset;
            int x_look = x+x_Offset;

            if(y_look < SIZE && y_look > -1){//nicht außerhalb der Spielfeldes
                if(x_look < SIZE && x_look > -1){//nicht außerhalb der Spielfeldes
                    if(!(x_look == x && y_look == y)){//ist nicht das eigene Feld
                        Feld nachbar = spielfeld.at(y_look).at(x_look);
                        if(nachbar.belegung == Aufgedeckt && nachbar.nachbar_anzahl == 0){
                            found_nachbar = true;
                        }
                    }
                }
            }
        }
    }
    return found_nachbar;
}
