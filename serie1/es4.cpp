#include <iostream>
#include <fstream>

using namespace std;

enum class importanza { BASSO, MEDIO, ALTA, FATTO };

struct Todo {
    string titolo;
    string descrizione;
    importanza importanza;
};

void aggiungi() {
    ofstream outputFile("Toto.dat");

    Todo item;
    cout << "Inserisci nuovi dati" << endl;
    cout << "Titolo?" << flush;
    cin >> item.titolo;
    cout << "Descrizione?" << flush;
    cin >> item.descrizione;
    cout << "Importanza? [1 Bassa, 2 Media, 3 Alta, 4 Fatto]" << flush;
    cin >> item.titolo;

    char procedere;
    cout << "Procedere? [S/N]" << flush;
    cin.get(procedere);
    if(procedere == 'S') {
        outputFile << item.titolo << endl;
        outputFile << item.descrizione << endl;
        outputFile << int(item.importanza) << endl;
        cout << "Dati modificati" << endl;
    }
    outputFile.close();
}

void rimuovi() {
    cout << "Quale elemento vuoi rimuovere? (0 per annullare)" << flush;

}

void lista() {
    ifstream inputFile("Toto.dat");
    inputFile.close();
}

void modifica() {
    cout << "======= Elenco elementi =======" << endl;
    lista();
    cout << "===============================" << endl;

    cout << "Quale elemento vuoi modificare? (0 per annullare)" << flush;
}

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
