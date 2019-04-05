
/*
:: è chiamato operatore di risoluzione dello scope
l'overloading (sovraccarico) degli operatori (ridefinizione della loro semantica).
operatori << >> sovraccaricati dalle classi ostream e istream
endl e' un manipolatore, inserisce carattere nl e forza flush
OPERATORI BINARI forme equivalenti:
1) obj.operator<<(param);
2) operator<<(obj, param2);

Lvalue: oggetto con un nome (es. variabili) e un indirizzo di
memoria preciso che posso ottenere con l'operatore &.
Posso passari per riferimento

Rvalue: valore temporaneo che non esiste più dopo l'espressione che lo usa
 int f(int& x) {} f(6); KO, rvalue non accettato
 int f(const int& x) {} f(6); OK, const ref
 int f(int&& x) {}  f(6); OK, rvalue ref

int x = 7 + 10; // x Lvalue, (17) Rvalue
 */
#include <iostream> // std:: cin, cout, cerr, endl
#include <string>
#include "Alpha.h"

using namespace std; //Rende visibili i nomi definiti in questo namespace

enum class Sesso { Maschio, Femmina }; // strongly typed, non convertito in num
struct Persona { string nome; }; //typedef non necessario

int moltiplica(int a, int b) { return a*b; }
namespace supsi { namespace dti {
    int moltiplica(int a, int b) {
        return ::moltiplica(a, b);
    }
}}

void swap(int& x, int& y) {
    int temp{x};
    x = y;
    y = temp;
}

int& sbagliato(int& x, int& y) {
    int temp;
    return temp; // Attenzione! Ritorno un rif. a una variabile locale!!!!
}

namespace xyz = supsi::dti; // alias namespace


int main() {
    std::cout << xyz::moltiplica(3,2) << std::endl;
    string msg{"Ciao mondo!"};
// string str('x'); // Errore
    cout << msg << endl << msg.length() << endl << msg.empty() << endl;
    string mystr{"ciao"};
    if (mystr == msg) {
        cout << mystr[3]; // Accesso ai caratteri
    }
    mystr.insert(5, "grande"); // Inserimento di stringhe in stringhe
    cout << mystr.substr(1,3);
    mystr.erase(3,6);
    mystr.replace(0, 5, "Hello");
    size_t pos = mystr.find("mondo", 0);
    int pi_a = 3.14; // Diventa 3!
    int pi_b {3.14}; // Problema!
    auto r{1.2}; // compilatore cambia auto in double
    auto k{moltiplica(4,2)}; // compilatore cambia auto in int

    int mioarray[] { 1, 5, 3, 6, 2};
    for (auto i : mioarray) cout << i << endl;
    for (auto i : { 1, 5, 3, 6, 2}) cout << i << endl;

    int* jp{new int{13}}; // allocazione e iniziz
    char* p0{new char[10]}; // Array
    int* p1{new int[5]}; // Array
    delete jp;
    delete[] p0;
    delete[] p1;
    int* ip{nullptr};

    // oggetto stack distrutto:
    // Namespace scope: quando termina il programma
    // Class scope: quando l'istanza della classe viene distrutta

    // Riferimento a un intero (alias per a)
    // A differenza di un puntatore, un riferimento non
    //può essere modificato per “puntare” a qualcos'altro (e magari a niente!)
    int& c{pi_a}; //

    // modificare un array
    for (auto& i : mioarray) i++;
}
