//
// Created by massi on 01.04.2019.
//
#include <iostream>
#include "Alpha.h"

using namespace std;
namespace bar {
    void Alpha::set(double v) {
        cout << "set double: valore " << v << endl;
        m_v = v;
    }

    Alpha::operator double() const {
        return m_v;;
    }

    Alpha::~Alpha() {
        cout << "Alpha : distruzione" << endl;
    }

    Beta::~Beta() {
        cout << "Beta: distruzione" << endl;
    }
};