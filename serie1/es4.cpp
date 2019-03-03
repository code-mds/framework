#include <iostream>

using namespace std;

void aggiungi() {}
void rimuovi() {}
void lista() {}
void modifica() {}

void mainMenu() {
    char option;
    do {
        cout << "[A]ggiungi, [R]imuovi, [L]ista, [M]odifica, [E]sci";
        cin >> option;

        switch(option) {
            case 'A':
                aggiungi();
                break;
            case 'R':
                rimuovi();
                break;
            case 'L':
                lista();
                break;
            case 'M':
                modifica();
                break;
        }

    } while(option != 'E');
}

void es4() {
    mainMenu();
}
