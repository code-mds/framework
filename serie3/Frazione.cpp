//
// Created by Massimo De Santi on 2019-03-23.
//
#include <iostream>
#include "Frazione.h"

using namespace std;
ostream& operator << (ostream& o, const Frazione& f)
{
    o << f.num() << "/" << f.den();
    return o;
}

//Primo operando (a sinistra) seoncondo operando a destra
Frazione operator+(Frazione a, const Frazione& b)
{
    return a += b;
}

Frazione operator-(Frazione a, const Frazione& b)
{
    return a -= b;
}

Frazione operator-(const Frazione& a)
{
    return { - a.num(), a.den() };
}

Frazione &Frazione::operator+=(const Frazione &f) {
    int temp_numeratore { f.m_numeratore * m_denominatore };
    m_denominatore *= f.m_denominatore;
    m_numeratore *= f.m_denominatore;
    m_numeratore += temp_numeratore;
    return *this;
}

Frazione &Frazione::operator-=(const Frazione &f) {
    int temp_numeratore { f.m_numeratore * m_denominatore };
    m_denominatore *= f.m_denominatore;
    m_numeratore *= f.m_denominatore;
    m_numeratore -= temp_numeratore;
    return *this;
}

Frazione &Frazione::operator*=(const Frazione &f) {
    m_denominatore *= f.m_numeratore;
    m_numeratore *= f.m_denominatore;
    return *this;
}

Frazione &Frazione::operator/=(const Frazione &f) {
    m_denominatore *= f.m_denominatore;
    m_numeratore *= f.m_numeratore;
    return *this;
}
