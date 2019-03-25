//
// Created by Massimo De Santi on 2019-03-23.
//
#include <fstream>
#include <iostream>
#include <string>
#include "Convertitore.h"
using namespace std;

std::ostream & operator << (std::ostream &out, const Convertitore &conv) {
    out << conv.m_labelFrom << "\t" << conv.m_labelTo << endl;
    out << conv.m_rate << "\t" << 1 << endl;
    return out;
}


Convertitore::Convertitore(string labelFrom, string labelTo, double rate) :
    m_labelFrom{labelFrom}, m_labelTo{labelTo}, m_rate{rate}
{

}

double Convertitore::convert(double from) {
    return from / m_rate;
}

double Convertitore::iconvert(double from) {
    return from * m_rate;
}

void Convertitore::convertFromFile(string fileName) {
    ifstream input{fileName};
    string line;
    if(!input.is_open()) {
        cerr << "error opening: " << fileName << endl;
        return;
    }

    int i = 0;
    while(!input.eof()) {
        if(input.fail()) {
            cerr << "error reading file" << endl;
            input.close();
            return;
        }

        double val;
        input >> val;
        cout << i << ")" << convert(val) << endl;
        i++;
    }
    input.close();
}

double Convertitore::operator<<(double input) const {
    return convert(input);
}

double Convertitore::operator>>(double input) const {
    return iconvert(input);
}
