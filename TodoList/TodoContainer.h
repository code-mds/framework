//
// Created by Massimo De Santi on 2019-03-23.
//

#ifndef FRAMEWORK_TODOCONTAINER_H
#define FRAMEWORK_TODOCONTAINER_H


#include <vector>
#include "TodoElement.h"

class TodoContainer {
public:
//    TodoContainer();
    virtual ~TodoContainer();
//
//    // Copia del container (deep copy)
//    TodoContainer(const TodoContainer& other);
//
//    // Copia del container (deep copy)
//    TodoContainer& operator=(const TodoContainer& other);
//
//    // Spostamento del container (move)
//    // Nota: compilare con -fno-elide-constructors per verificare il corretto funzionamento
//    TodoContainer(TodoContainer&& other);
//
//    // Spostamento del container (move)
//    TodoContainer& operator=(TodoContainer&& other);


    // Accesso agli elementi
    TodoElement& operator[](unsigned int index) const;

    // Svuota il contenuto
    void clear();

    // Scrive (serializza) il contenuto (gli elementi TodoElement) su uno stream // di output (per esempio un ofstream)
    void write(ostream& out) const;

    // Legge (deserializza) il contenuto da uno stream di input (p.es un ifstream) // istanziando gli elementi (TodoElement) del container
    void read(const istream& in);

    // Inserisce un nuovo elemento alla fine
    //TodoElement& push_back(const TodoElement* e); // ???
    TodoElement& push_back(TodoElement* e);

    // Elimina l'elemento alla posizione index
    void erase(unsigned int index);

    // Ritorna il numero di elementi
    int size() const;

    //friend std::ostream& operator << (std::ostream& o, const TodoContainer& c);

private:
    //vector<const TodoElement*> m_elements;
    vector<TodoElement*> m_elements;
};


#endif //FRAMEWORK_TODOCONTAINER_H
