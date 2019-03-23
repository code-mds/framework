//
// Created by Massimo De Santi on 2019-03-23.
//

#include "TodoElement.h"

void TodoElement::importanza(Importanza v) {
    m_importanza = v;
}

Importanza TodoElement::importanza() const {
    return m_importanza;
}

void TodoElement::descrizione(const string &v) {
    m_descrizione = v;
}

string TodoElement::descrizione() const {
    return m_descrizione;
}

void TodoElement::titolo(const string &titolo) {
    m_titolo = titolo;
}

string TodoElement::titolo() const {
    return m_titolo;
}

TodoElement::TodoElement(string titolo, string descrizione, Importanza importanza) :
    m_titolo{titolo},
    m_descrizione{descrizione},
    m_importanza{importanza}
{

}
