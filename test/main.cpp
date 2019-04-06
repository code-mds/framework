#include <memory>
#include <iostream> // std:: cin, cout, cerr, endl
#include <string>
#include <sstream>
#include <vector>

#include "Alpha.h"

using namespace std; //Rende visibili i nomi definiti in questo namespace
// namespace xyz = supsi::dti; // alias namespace

class Collaboratore {
    string m_nome;
public:
    Collaboratore() = default;
    Collaboratore(string nome) : m_nome{nome} {
        cout << "Collaboratore Ctor" << endl;
    }

    string nome() const { return m_nome; }
    string classe() const { return "Collaboratore"; }
    virtual string toString() { return nome(); }
};

// ereditarieta' multipla: uso virtual base class
class Docente : public virtual Collaboratore {
    string m_corso;
public:
    Docente(string nome, string corso) :
            Collaboratore{nome},
            m_corso{corso}
    {}
    string corso() const noexcept { return m_corso;}
    string classe() const { return "Docente"; }

    // il compilatore controlla che esista un metodo virtual
    string toString() override { return classe() + ": " + corso(); }
};

// ereditarieta' multipla: uso virtual base class
class Ricercatore : public virtual Collaboratore {
    string m_arearicerca;
public:
    Ricercatore(string nome, string arearicerca) :
            Collaboratore{nome},
            m_arearicerca{arearicerca}
    {}
    string arearicerca() const {return m_arearicerca; }
    string classe() const { return "Ricercatore"; }
};

// ereditarieta' multipla: uso virtual base class
// class Ricercatore : public virtual Collaboratore ...
// class Docente : public virtual Collaboratore ...
// ora il compilatore usa costruttore vuoto di Collaboratore
// invece di quello usato nella init-list di Docente e Ricercatore.
// Quindi il costruttore vuoto va dichiarato esplicito
// il costruttore con parametri va richiamato esplicitamente in
// DocenteRicercatore
class DocenteRicercatore : public Docente, public Ricercatore {
    double m_percRicerca;
public:
    DocenteRicercatore(string nome, string corso, string arearicerca, double percRicerca) :
            Collaboratore(nome),
            Docente{nome, corso},
            Ricercatore{nome, arearicerca},
            m_percRicerca{percRicerca}
    {}
    double percRicerca() const { return m_percRicerca; }
    string classe() const { return "DocenteRicercatore"; }
};

/*
int& sbagliato(int& x, int& y) {
    int temp;
    return temp; // Attenzione! Ritorno un rif. a una variabile locale!!!!
}*/


/*
Rvalue: valore temporaneo (non hanno nome) che non esiste più dopo l'espressione che lo usa
 int f(int& x) {} f(6); KO, rvalue non accettato
 int f(const int& x) {} f(6); OK, const ref
 int f(int&& x) {}  f(6); OK, rvalue ref
*/

class F {
public:
    F(int n=0, int d=1) : m_num{n}, m_den{d} {}

    int num() const { return m_num; } //getter
    void num(int n) { m_num = n; } //setter
    int den() const { return m_den; }
    void den(int d) { m_den = d; }

    F& operator += (const F& f){
        int temp_numeratore { f.m_num * m_den };
        m_den *= f.m_den;
        m_num *= f.m_den;
        m_num += temp_numeratore;
        return *this;
    };
    F& operator -= (const F& f){
        int temp_numeratore { f.m_num * m_den };
        m_den *= f.m_den;
        m_num *= f.m_den;
        m_num -= temp_numeratore;
        return *this;
    };
    // conversion/cast operator: F f{3,4}; double a=f;
    operator double() { return double(m_num) / m_den; }
    // prefix   ++f
    F& operator ++() { return *this += 1; }
    // postfix   f++ (inserisco un parametro fittizio)
    F operator ++(int) {
        F old{*this};
        *this += 1;
        return old;
    }

private:
    int m_num, m_den;
};

// f1 copy, f2 reference. return a copy
F operator + (F f1, const F& f2) {
    return f1 += f2;
};

// bitshift operator (binario), overload da ostream
// es. o << f; o.operator<<(f); operator<<(o, f);
// endl manipolatore, inserisce carattere nl e forza flush
ostream& operator << (ostream& o, const F& f) {
    o << f.num() << "/" << f.den() << endl;
    return o;
};

// il compilatore automaticamente crea:
//  default ctor (se altri costruttori non esplicitati)
//  copy ctor, copy assignment (operator=), destructor (non ereditati)
struct A {
    A() : m_num{-1} { cout << "A()" << endl; }
    // explicit: evita implicit conversion
    explicit A(int val) : m_num{val} { cout << "A(int)" << endl; }
    virtual ~A() { cout << "~A()" << endl; }
    virtual string f() { return "A.f() "; }
    string g() { return "A.g() "; }
    string h() { return "A.h() "; }
    string h(int v) { return "A.h(int) "; } //overloading di h()
private:
    int m_num;
};

struct B : A {
    B() { cout << "B()" << endl; }
    B(string str) : A{10}, m_str{"default"} { cout << "B(str)"; }
    virtual ~B() { cout << "~B()" << endl; }

    string f() override final { return "B.f() "; } // final method
    string g() { return "B.g() "; } // HIDING: perche' A::g() non virtual
    string h(string str) { m_str = str; return "B.h(str) "; }

    // HIDING: metodo con stesso nome definito in classe base
    // nasconde tutte i metodi sovraccaricati nella classe base
    // :: è chiamato operatore di risoluzione dello scope
    using A::h; // fix hiding, ora tutti gli h sono visibili
    // alternativa client chiama esplicit b.A::h(12)

private:
    string m_str;
};

// C e' final: impedisce ulteriori derivazioni
struct C final : B {
    // ctor with initializer_list HA PRECEDENZA
    C(const std::initializer_list<int>& valori) {
        cout << "C(init_list) " << endl;
        for (const auto& v : valori) { m_vect.push_back(v); }
    }

    explicit C(int sz) {
        cout << "C(int)" << endl;
        m_vect.reserve(sz);
    }

    //string f() {} non posso piu' fare override perche' f e' final in B

    void print() {
        for (const auto& x : m_vect) { cout << x; }
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
    cout << "a " << a.g() << a.f() << a.h() << a.h(12) << endl;
    cout << "b " << b.g() << b.f() << b.A::f() << b.h() << b.h("c") << endl;
    cout << "ab " << ab.g() << ab.f() << endl;
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
//    int pi_a = 3.14; // Diventa 3!
//   int pi_b {3.14}; // Problema!
    auto r{1.2}; // compilatore cambia auto in double
//    auto k{moltiplica(4,2)}; // compilatore cambia auto in int

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
    DocenteRicercatore dr{"Massimo", "DTI", "MED", 12.3};
    cout << dr.nome() << endl;
    cout << typeid(dr).name() << endl; // 18DocenteRicercatore

    Docente doc{"Giovanni", "Linguaggi"};
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
        //v.push_back(h); // Errore! Non posso fare una copia
        v.push_back(move(p)); // Ok! Trasferisco l'ownership
        //cout << *h << endl; // Errore a runtime!!!! h non è più mio!

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

