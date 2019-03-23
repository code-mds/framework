#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

namespace es4 {
    const int VERSION = 1;
    const string DB_NAME = "Todo.dat";

    enum class importanza { BASSA=1, MEDIA, ALTA, FATTO };

    struct TodoEntry {
        string titolo;
        string descrizione;
        importanza importanza;
    };

    std::ostream& operator << (std::ostream& stream, const importanza val)
    {
        string strVal;
        switch (val) {
            case importanza::BASSA:
                strVal = "Bassa";
                break;
            case importanza::MEDIA:
                strVal = "Media";
                break;
            case importanza::ALTA:
                strVal = "Alta";
                break;
            case importanza::FATTO:
                strVal = "Fatto";
                break;
        }
        return stream << strVal;
    }

    std::ostream& operator << (std::ostream& stream, const TodoEntry entry)
    {
        return stream   << entry.titolo << endl
                        << entry.descrizione << endl
                        << entry.importanza << endl;
    }

    std::istream& operator >> (std::istream& stream, TodoEntry& entry)
    {
        getline(stream, entry.titolo);
        getline(stream, entry.descrizione);
        string strImportanza;
        getline(stream, strImportanza);
        int iImp;
        if(stream >> iImp)
            entry.importanza = importanza(iImp);

        return stream;
    }


    vector<TodoEntry> entries;

    void init_db() {
        ifstream inputFile(DB_NAME);
        if(inputFile.good()) {
            TodoEntry entry;

            vector<TodoEntry>::iterator it;
            it = entries.begin();
            while(inputFile >> entry) {
                it = entries.insert(it, entry);
            }
        }
        inputFile.close();
    }

    void flush_db() {
        ofstream outputFile(DB_NAME);

        vector<TodoEntry>::iterator it;
        it = entries.begin();
        for (it=entries.begin(); it<entries.end(); it++)
            outputFile << *it;
    }

    void aggiungi() {
        TodoEntry item;
        cout << "Inserisci nuovi dati" << endl;
        cout << "Titolo?" << flush;
        cin >> item.titolo;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        cout << "Descrizione?" << flush;
        cin >> item.descrizione;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');


        cout << "Importanza? [1 Bassa, 2 Media, 3 Alta, 4 Fatto]" << flush;
        int iImp;
        if(cin >> iImp)
            item.importanza = importanza(iImp);

        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        char procedere;
        cout << "Procedere? [S/N]" << flush;
        cin.get(procedere);
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

        if(procedere == 'S') {
            entries.insert(entries.end(), item);
            cout << "Dati modificati" << endl;
        }
    }

    void rimuovi() {
        cout << "Quale elemento vuoi rimuovere? (0 per annullare)" << flush;
        int idx;
        cin >> idx;
        if(idx == 0)
            return;

    }

    void print_list() {
        int idx = 1;
        vector<TodoEntry>::iterator it;
        it = entries.begin();
        for (it=entries.begin(); it<entries.end(); it++) {
            cout << idx << " - "
                 << (*it).titolo << ","
                 << (*it).descrizione << ","
                 << (*it).importanza << endl;
            idx++;
        }
    }

    void modify_list() {
        cout << "======= Elenco elementi =======" << endl;
        print_list();
        cout << "===============================" << endl;

        cout << "Quale elemento vuoi modificare? (0 per annullare)" << flush;
        int idx;
        cin >> idx;
        if(idx == 0)
            return;

    }

    void mainMenu() {
        init_db();

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
                    print_list();
                    break;
                case 'M':
                    modify_list();
                    break;
            }

        } while(option != 'E');
    }
}
