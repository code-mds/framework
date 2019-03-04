#ifndef FRAZIONE_H
#define FRAZIONE_H

class Frazione {
public:
    Frazione() : Frazione{0,1} {}
    Frazione(int numeratore = 0, int denominatore=1)
        : m_numeratore{numeratore}, m_denominatore{denominatore}
    {}

    int num() const { return m_numeratore; }
    void num(int numeratore) { m_numeratore = numeratore; }
    int den() const { return m_denominatore; }
    void den(int denominatore) { m_denominatore = denominatore; }

    Frazione& operator += (const Frazione& f);
    Frazione& operator -= (const Frazione& f);

    operator double() {
        return double(m_numeratore) / m_numeratore;
    }

    // prefix   ++f --f
    Frazione& operator ++() { return *this += 1; }
    Frazione& operator --() { return *this -= 1; }

    // postfix   f++ f--, inserisco un parametro fittizio
    Frazione operator ++(int) {
        Frazione old{*this};
        *this += 1;
        return old;
    }
    Frazione operator --(int) {
        Frazione old{*this};
        *this -= 1;
        return old;
    }

private:
    int m_numeratore;
    int m_denominatore;
};

#endif // FRAZIONE_H
