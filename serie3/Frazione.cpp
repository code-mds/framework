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