#include "s2e1.cpp"
#include "s2e2.cpp"
#include "Convertitore.h"

int main(void) {
    //s2e1();
    //s2e2::main();

    Convertitore conv("CHF", "EUR", 1.2);

    // conv è un oggetto di tipo Convertitore
    cout << conv << endl; // Stampa a schermo il tasso di cambio

    cout << (conv << 200.0) << endl; // Stampa il valore 2 nella seconda valuta
    cout << (conv >> 200.0) << endl; // Stampa il valore 2 nella prima valuta

    conv.convertFromFile("../../serie2/res/values.txt");
    return 0;
}
