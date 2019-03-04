#include <iostream>
#include "frazione.h"

using namespace std;

// OPERATORI DEFINITI COME FUNZIONI ESTERNE ALLA CLASSE
Frazione& operator + (Frazione f1, const Frazione& f2) {
    return f1 += f2;
};

Frazione& operator - (Frazione f1, const Frazione& f2) {
    return f1 -= f2;
};

ostream& operator << (ostream& o, const Frazione& f) {
    o << f.num() << "/" << f.den() << endl;
    return o;
};

// OPERATORI DEFINITI COME METODI DI CLASSE
Frazione& Frazione::operator += (const Frazione& f) {
    int temp_numeratore { f.m_numeratore *
    m_denominatore };
    m_denominatore *= f.m_denominatore;
    m_numeratore *= f.m_denominatore;
    m_numeratore += temp_numeratore;

    return *this;
};

Frazione& Frazione::operator -= (const Frazione& f) {
    int temp_numeratore { f.m_numeratore *
    m_denominatore };
    m_denominatore *= f.m_denominatore;
    m_numeratore *= f.m_denominatore;
    m_numeratore -= temp_numeratore;
    return *this;
};
