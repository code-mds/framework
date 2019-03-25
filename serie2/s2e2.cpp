#include <iostream>
using namespace std;

namespace s2e2 {
    /* Tasso di cambio EURO-CHF */
    static const double tasso{1.2};
    double tassoUtente;

    void displayInfo() {
        cout << "CHF" << "\t" << "EUR" << endl;
        cout << tassoUtente << "\t" << 1 << endl;
    }

    // passaggio parametro per valore
    double convert(double chf) {
        return chf / tasso;
    }

    double iconvert(double eur) {
        return eur*tasso;
    }

    void main()
    {
        cout << "inserire tasso di cambio" << endl;
        cin >> tassoUtente;
        if(tassoUtente <=0 || cin.fail()) {
            cout << "tasso di cambio invalido, uso default: " << tasso << endl;
            tassoUtente = tasso;
        }

        displayInfo();

        double a, b;
        double chf = 120;
        double eur = convert(chf);
        std::cout << chf << ","<< eur << std::endl;

        double chf2 = iconvert(eur);
        std::cout << chf2 << ","<< eur << std::endl;
    }


}
