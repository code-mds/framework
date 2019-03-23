#include <iostream>

/* Tasso di cambio EURO-CHF */
static const double tasso{1.2};

// passaggio parametro per valore
double convert(double chf) {
    return chf / tasso;
}

// passaggio parametro per riferimento
double convert2(double& chf) {
    return chf / tasso;
}

void testAlias(double& chf) {
    chf *= 10;
}
void s2e1()
{
    double a, b;
    double *x, *y;
    a = 120;

    //testAlias(a);

    x = &a; // *x: 120
    y = &b; // *y: undefined

    // in "convert2" ho un alias alla variabile passata come argomento, mentre in "convert"
    // ho una copia del valore. Con un alias potrei modificare la variabile passata dal chiamante
    // mentre le modifiche di convert sarebbero locali alla funzione, essendo il parametro una copia
    // della variabile originale.
    b = convert(*x); // b,*y: 100
    *y = convert2(b); // b,*y = 83.33

    a = 240;
    a = convert(a); // a: 200

    // se commento using devo aggiungere std:: a cout e endl
    std::cout << a << ","<< b << std::endl;
}
