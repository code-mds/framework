#include <memory>
#include <iostream> // std:: cin, cout, cerr, endl
#include <string>
#include <sstream>
#include <vector>

#include "Alpha.h"

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

 In C++03, the compiler provides, for classes that do not provide them for themselves, a default constructor,
 a copy constructor, a copy assignment operator (operator=), and a destructor.




 */

using namespace std; //Rende visibili i nomi definiti in questo namespace


class Collaboratore {
    string m_nome;
    string m_istituto;
    int m_nrcollab;
public:
    Collaboratore() = default;
    Collaboratore(string nome, string istituto, int nr_collab) :
            m_nome{nome}, m_istituto{istituto}, m_nrcollab{nr_collab}
    {
        cout << "Collaboratore Ctor" << endl;
    }


    string nome() const { return m_nome; }
    string istituto() const { return m_istituto; }
    int nrcollab() const { return m_nrcollab; }
    string nomeclasse() const { return "Collaboratore"; }
    //virtual string toString()=0; // abstract class
    virtual string toString() { return nome() + ", " + istituto(); }
};

class Docente : public virtual Collaboratore {
    string m_corso;
public:
    Docente(string nome, string istituto, int nr_collab, string corso) :
            Collaboratore{nome, istituto, nr_collab},
            m_corso{corso}
    {}
    string corso() const { return m_corso;}
    string nomeclasse() const { return "Docente"; }

    string toString() override // il compilatore controlla che esista un metodo virtual
    { return nomeclasse() + ": " + corso(); }
};


class Ricercatore : public virtual Collaboratore {
    string m_arearicerca;
public:
    Ricercatore(string nome, string istituto, int nr_collab, string arearicerca) :
            Collaboratore{nome, istituto, nr_collab},
            m_arearicerca{arearicerca}
    {}
    string arearicerca() const {return m_arearicerca; }
    string nomeclasse() const { return "Ricercatore"; }
};

// ereditarieta' multipla: uso virtual base class
// ora il compilatore usa costruttore vuoto di Collaboratore
// invece di quello usato nella init-list di Docente e Ricercatore.
// Quindi il costruttore vuoto va dichiarato esplicito
// il costruttore con parametri va richiamato esplicitamente in
// DocenteRicercatore
class DocenteRicercatore : public Docente, public Ricercatore {
    double m_percRicerca;
public:
    DocenteRicercatore(string nome, string istituto,
                       int nr_collab, string corso, string arearicerca,
                       double percRicerca) :
            Collaboratore(nome, istituto, nr_collab),
            Docente{nome, istituto, nr_collab, corso},
            Ricercatore{nome, istituto, nr_collab, arearicerca},
            m_percRicerca{percRicerca}
    {}
    double percRicerca() const { return m_percRicerca; }
    string nomeclasse() const { return "DocenteRicercatore"; }
};


enum class Sesso { Maschio, Femmina }; // strongly typed, non convertito in num
struct Persona { string nome; }; //typedef non necessario

void testCast();

void testAuto();

void ordineCostrDestr();

void binding();

int moltiplica(int a, int b) noexcept { return a * b; }
namespace supsi {
    namespace dti {
        int moltiplica(int a, int b) { return ::moltiplica(a, b); }
}}

void swap(int& x, int& y) {
    int temp{x};
    x = y;
    y = temp;
}

/*
int& sbagliato(int& x, int& y) {
    int temp;
    return temp; // Attenzione! Ritorno un rif. a una variabile locale!!!!
}*/

namespace xyz = supsi::dti; // alias namespace

struct A {
    A() { cout << "create A" << endl; }
    ~A() { cout << "destr A" << endl; }
    string foo() { return "A.foo() "; }
//    VISIBILITA:
//      Un metodo con lo stesso nome di un metodo di una classe
//      base nasconde tutte le funzioni sovraccaricate con lo stesso
//      nome nella classe base
    string p(int v) { return "A.p(int) "; }
    string p() { return "A.p() "; }

    virtual string f() { return "A.f() "; }
};

struct B : A {
    B() { cout << "create B" << endl; }
    ~B() { cout << "destr B" << endl; }

    string p(string f) { return "B.p(str) "; }

    string foo() { return "B.foo() "; }
    string f() final { return "B.f() "; }

    using A::p;  // risolvo problema di HIDING, alternativa  b.A::p(12)

//    funzioni mai ereditate, hanno bisogno info su oggetto
//    – I costruttori di copia
//    – Gli operatori di assegnamento di copia
//    – I distruttori
};

// B e' final: impedisce ulteriori derivazioni
struct C final : B {
    // ctor with initializer_list HA PRECEDENZA
    C(const std::initializer_list<int>& valori) {
        cout << "C ctor init_list" << endl;
        for (const auto& v : valori) {
            m_vect.push_back(v);
        }
    }

    C(int sz) {
        cout << "C ctor int" << endl;
        m_vect.reserve(sz); }

    //string f() {} non posso piu' fare override perche' f e' final in B

    void print() {
        for (const auto& x : m_vect) {
            cout << x;
        }
        cout << endl;
    }
    void removeAt(int pos) {
        m_vect.erase(m_vect.begin() + pos);
    }
    void append(int v) {
        m_vect.push_back(v);
    }
    int size() {
        return m_vect.size();
    }
private:
    vector<int> m_vect;
};


void test_std() {
    // String Stream
    stringstream sstr;
    for (int i=0; i<10; i++) {
        sstr << i;
    }
    cout << sstr.str() << endl;

    // vector, map, list
    C c2(1); // per forzare uso di costruttore con int
    C c{1,2,3,4,5,6};
    c.removeAt(3); // 0 based
    c.append(8);
    c.print();     // 123568

    // list
//    l1.push_back(5);
//    l1.push_front(5);
//    l1.pop_back();
//    l1.pop_front();

//    map<string,int> contatti { {"Pinco", 123456},
//                               {"Pallino", 2342342}};
//    contatti ["Alfonso"] = 32333;
//    if (contatti.count("Pinco") == 1) {
//        cout << "Pinco esiste" << endl;
//    }
//    contatti.erase ("Pallino");
}



void binding() {
    // statico: compile time, non permette polimorfismo. ma piu' efficiente
    // polimorfismo: capacita' di scegliere il metodo giusto in base oggetto
    // dinamico: late run time, richiede uso di virtual (default in Java)
    // vtable all'interno della classe (condivisa tra tutti gli oggetti)
    A a; B b;
    A& ab{b};
    cout << "a " << a.foo() << a.f() << a.p() << a.p(12) << endl;
    cout << "b " << b.foo() << b.f() << b.A::f() << b.p() << b.p("c") << endl;
    cout << "ab " << ab.foo() << ab.f() << endl;
}

void ordineCostrDestr() {
//        A <- B
//        DERIVAZIONE: protected: i metodi public diventano protected, protected rimangono protected
//        quando istanzio un oggetto di tipo B prima di tutto creo un oggetto A
//        se nella init-list non chiamo esplicitamente un ctor di A, viene cercato il default cto()
//        se non esiste non compila. I ctor classi basi sono chiamati prima di ctor derivate

//        ## A a -> create A
//        ## B b -> create A, create B
//        ## end scope -> destr B, destr A, destr A
        cout << "## A a" << endl; A a;
        cout << "## B b" << endl; B b;
        cout << "## end scope" << endl;
    }

void testAuto() {
    cout << supsi::dti::moltiplica(3, 2) << endl;
    string msg{"Ciao mondo!"};
// string str('x'); // Errore
//    cout << msg << endl << msg.length() << endl << msg.empty() << endl;
//    string mystr{"ciao"};
//    if (mystr == msg) {
//        cout << mystr[3]; // Accesso ai caratteri
//    }
//    mystr.insert(5, "grande"); // Inserimento di stringhe in stringhe
//    cout << mystr.substr(1,3);
//    mystr.erase(3,6);
//    mystr.replace(0, 5, "Hello");
//    size_t pos = mystr.find("mondo", 0);
    int pi_a = 3.14; // Diventa 3!
//   int pi_b {3.14}; // Problema!
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

    auto lamda = [](int par) -> void { cout << par << endl ; };

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

void testCast() {
    DocenteRicercatore dr{"Massimo", "SUPSI", 123, "DTI", "MED", 12.3};
    cout << dr.nome() << endl;
    cout << typeid(dr).name() << endl; // 18DocenteRicercatore

    Docente doc{"Giovanni", "ISIN", 42, "Linguaggi e framework"};
    cout << typeid(doc).name() << endl; // 7Docente

    // static_cast<tipo>(oggetto), check durante compilazione
// puntatori, riferimenti, oggettti. NO se: base (virtual) -> derivata
// conversione di oggetto
    Collaboratore coll = static_cast<Collaboratore>(doc);
    cout << typeid(coll).name() << endl; // 13Collaboratore

    // rif/puntatore
    Collaboratore& rc = static_cast<Collaboratore&>(doc);
    Collaboratore& drc = dynamic_cast<Collaboratore&>(doc);
    cout << typeid(rc).name() << endl; // 13Collaboratore
    cout << "D " << typeid(drc).name() << endl; // D 13Collaboratore

    Collaboratore* pc = static_cast<Collaboratore*>(&doc);
    Collaboratore* dpc = dynamic_cast<Collaboratore*>(&doc);
    Collaboratore* pd = &doc;
    cout << typeid(pc).name() << endl; // P 13Collaboratore
    cout << "D " << typeid(dpc).name() << endl; // D P13Collaboratore
    cout << "N " << typeid(pd).name() << endl; // M P13Collaboratore

    // errore non rilevato !!!
    DocenteRicercatore* pdr = static_cast<DocenteRicercatore*>(&doc);
    cout << pdr->percRicerca() << endl; //Spazzatura
    cout << typeid(pdr).name() << endl; //

    // dynamic_cast<tipo>(punt_o_rif)
// Effettua una conversione verificando, a compilazione e a runtime
// upcasting e downcasting (solo se oggetti base hanno almeno un virtual)
// no void* to Classe*

    // se non riesce ad effettuare il cast:
// - puntatore: ritorna un puntatore a 0
// - riferimento: lancia l'eccezione std::bad_cast

    // reinterpret_cast<tipo>(puntatore_o_rif);
// non fa nessun controllo sul contenuto, casta e basta.

    // const_cast<tipo>(puntatore_o_rif)
// per eliminare l'attributo const
//const Base* b{new Base};
//b->bar(); // Errore! Non è const!

    //Base* bc = static_cast<Base*>(b); // Non permesso
//Base* bc = reintepret_cast<Base*>(b); // Non permesso
//Base* bc = dynamic_cast<Base*>(b); // Non permesso
//Base* bc = const_cast<Base*>(b); // Ok
// bc->bar(); // Ok

    // operatore typeid permette di determinare la classe di
//un oggetto a runtime

}

unique_ptr<int> allocaArray()
{
    // alloco un int array sull'heap
    return unique_ptr<int>{new int{13}};
}

void smart_pointers() {
    // #include <memory>
    // memoria viene liberata automaticamente fuori dallo scope, chiamata a distruttore
    // get()     ottengo il puntatore
    // release() rilascio l'ownership

    // unique_ptr, unique ownership. non puo' essere copiato. devo usare reference
    {
        unique_ptr<int> p1{new int}; // alloco un int sull'heap
        unique_ptr<int>& r {p1};

        vector<unique_ptr<int>> v;
        unique_ptr<int> p {new int{13}};
        //v.push_back(p); // Errore! Non posso fare una copia
        v.push_back(move(p)); // Ok! Trasferisco l'ownership
        //cout << *p << endl; // Errore a runtime!!!! p non è più mio!

        unique_ptr<int> p3{allocaArray()};
        cout << *p3 << endl;  // posso dereferenziare come un puntatore normale
    }

    // smart_ptr, shared ownership. supportano la copia
    // quando l'ultima copia viene distrutta anche il puntatore viene distrutto
    {
        shared_ptr<int> p {new int{13}};
        shared_ptr<int> t = make_shared<int>(17);
        shared_ptr<int> r {p}; // Ok! Creo una copia
    }
}

void eccezioni() {
    //#include <stdexcept>
    // stack unwinding, distruzione di oggetti che escono da scope
    // parola chiave noexcept per marcare metodi che impediscono all'eccezione di propagarsi oltre
    // non esiste finally
    // throw out_of_range("errore")
    // throw 12; throw "ciao"; posso fare il throw con qualsiasi tipo
    // throw; rilancio l'eccezione
}

int main() {
    eccezioni();
    smart_pointers();
//    test_std();
//    binding();
//    ordineCostrDestr();
//    testAuto();
//    testCast();
}

