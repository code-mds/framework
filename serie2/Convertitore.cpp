//
// Created by Massimo De Santi on 2019-03-23.
//
#include <fstream>
#include <iostream>
#include <string>
#include "Convertitore.h"
using namespace std;

Convertitore::Convertitore(string labelFrom, string labelTo, double rate) :
    m_labelFrom{labelFrom}, m_labelTo{labelTo}, m_rate{rate}
{

}

void Convertitore::displayInfo(void) {
    cout << m_labelFrom << "\t" << m_labelTo << endl;
    cout << m_rate << "\t" << 1 << endl;
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
            return;
        }

        double val;
        input >> val;
        cout << i << ")" << convert(val) << endl;
        i++;
    }
}
