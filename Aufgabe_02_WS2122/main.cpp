#include <main.h>


void mark(){
    bool con = true;
    while(con){
        char answer = 'N';
        cout << "Moechtest du ein Feld markieren? [Y/N]" << endl;
        cin >> answer;
        if(answer == 'Y' || answer == 'y'){
            int x = 0, y = 0;
            cout << "Welches Feld moechtest du markieren? " << endl;
            cout << "Y: ";
            cin >> y;
            cout << "X: ";
            cin >> x;

            x-=1;
            y-=1;

            spielfeld.mark_feld(x,y);
            spielfeld.darstellen(debug);
        }else if(answer == 'N' || answer == 'n'){
            con = false;
        }
    }
}

bool play(int& felder_left){
    int x = 0, y = 0;

    cout << "Verbleibende verdeckte Felder: " << felder_left << endl;

    spielfeld.darstellen(debug);

    mark();

    cout << "Bitte waehlen sie ein Feld aus: " << endl;
    cout << "Y: ";
    cin >> y;
    cout << "X: ";
    cin >> x;

    x-=1;
    y-=1;

    if(spielfeld.validateInput(x,y)){
        if(spielfeld.hit(x,y)){
            cout << "**** BOOOOM ****" << endl;
            cout << "Leider verloren." << endl;
            return false;
        }
        spielfeld.aufdecken(x,y);
        felder_left-=1;
    }else{
        cout << "Du hast falsche Werte fuer X und Y eingegeben!" << endl;
    }

    bool nachbarncheck_edited = true;
    while(nachbarncheck_edited){
        nachbarncheck_edited = spielfeld.nachbarnChecken(felder_left);
    }

    return true;
}

int main()
{
    int minen_anzahl = 20;
    bool game = true;
    int felder_left = (spielfeld.SIZE * spielfeld.SIZE)-minen_anzahl;

    spielfeld.initialisieren(minen_anzahl);

    auto start = chrono::high_resolution_clock::now();

    while(game){
        if(felder_left == 0){ //ENDE
            auto finish = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(finish - start); //casted microsekunden in sekunden um
            game = false;
            cout << "Glückwunsch du hast gewonnen!" << endl;
            //elapsed.count() -> get time elapsed in seconds
            cout << "Benoetigte Zeit: " << (elapsed.count()) << " Sekunden" << endl;
        }
        game = play(felder_left);
    }


    return 0;
}
