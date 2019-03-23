//
// Created by Massimo De Santi on 2019-03-23.
//

#include "TodoContainer.h"

TodoElement &TodoContainer::operator[](unsigned int index) const {
    if(index >= m_elements.size())
        throw out_of_range("Indice non valido");

    return *m_elements[index];
}

void TodoContainer::clear() {
    m_elements.clear();
}

void TodoContainer::write(ostream &out) const {

}

void TodoContainer::read(const istream &in) {

}

TodoElement &TodoContainer::push_back(TodoElement *e) {
    m_elements.push_back(e);
    return *e;
}

void TodoContainer::erase(unsigned int index) {
    if(index >= m_elements.size())
        throw out_of_range("Indice non valido");

    m_elements.erase(m_elements.begin() + index);
}

int TodoContainer::size() const {
    return m_elements.size();
}

TodoContainer::~TodoContainer() {

}
