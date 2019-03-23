#include "s2e1.cpp"
#include "s2e2.cpp"
#include "Convertitore.h"

int main(void) {
    //s2e1();
    //s2e2::main();

    Convertitore conv("CHF", "EUR", 1.2);
    conv.convertFromFile("../../serie2/res/values.txt");
    return 0;
}
