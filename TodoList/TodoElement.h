//
// Created by Massimo De Santi on 2019-03-23.
//

#ifndef FRAMEWORK_TODOELEMENT_H
#define FRAMEWORK_TODOELEMENT_H

#include <string>

using namespace std;

enum class Importanza { BASSA=1, MEDIA, ALTA, FATTO };

class TodoElement {
public:
    TodoElement(string titolo = "Titolo", string descrizione = "Descrizione", Importanza importanza = Importanza::BASSA);

    string titolo() const;  //il const dopo il nome del metodo dichiara che il
                            // metodo non ha side effect sullo stato della classe

    void titolo(const string& v); // il const prima del parametro dichiara che
                                  // il metodo non modifica il parametro

    string descrizione() const;
    void descrizione(const string& v);

    Importanza importanza() const;
    void importanza(Importanza v);

    // la classe non dichiara un distruttore esplicito
    // perche' non ha risorse da liberare in fase di distruzione
private:
    string m_titolo;
    string m_descrizione;
    Importanza m_importanza;
};

#endif //FRAMEWORK_TODOELEMENT_H
