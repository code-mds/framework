//
// Created by Massimo De Santi on 2019-03-23.
//

#ifndef FRAMEWORK_CONVETITORE_H
#define FRAMEWORK_CONVETITORE_H

#include <string>
using namespace std;

class Convertitore {
private:
    string m_labelFrom;
    string m_labelTo;
    double m_rate;

public:
    Convertitore(string labelFrom, string labelTo, double rate = 1.2);
    void displayInfo(void);
    double convert(double from);
    double iconvert(double to);
    void convertFromFile(string fileName);
};


#endif //FRAMEWORK_CONVETITORE_H
