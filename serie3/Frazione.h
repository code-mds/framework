//
// Created by Massimo De Santi on 2019-03-23.
//

#ifndef FRAMEWORK_FRAZIONE_H
#define FRAMEWORK_FRAZIONE_H


class Frazione {
    int m_numeratore;
    int m_denominatore;
public:
    Frazione() : Frazione(0, 1) {};
    Frazione(int numeratore, int denominatore=1) :
            m_numeratore{numeratore},
            m_denominatore{denominatore} {};
    ~Frazione() {};

    int num() const { return m_numeratore; }
    void num(int numeratore) { m_numeratore = numeratore; }

    int den() const { return m_denominatore; }
    void den(int denominatore) { m_denominatore = denominatore; }

    Frazione& operator += (const Frazione& f) {
        int temp_numeratore { f.m_numeratore * m_denominatore };
        m_denominatore *= f.m_denominatore;
        m_numeratore *= f.m_denominatore;
        m_numeratore += temp_numeratore;
        return *this;
    }

    Frazione& operator -= (const Frazione& f) {
        int temp_numeratore { f.m_numeratore * m_denominatore };
        m_denominatore *= f.m_denominatore;
        m_numeratore *= f.m_denominatore;
        m_numeratore -= temp_numeratore;
        return *this;
    }
};



#endif //FRAMEWORK_FRAZIONE_H
