#include <iostream>

namespace s3e2 {
    struct Beta {
        explicit Beta(int& z) : m_z{z} {}
        int m_z;
    };

    class Alpha {
    public: //add public:
        Alpha(int i) : m_i{i} {}
        int get() const { return m_i; } //add const
        void set(int i) { m_i = i; }
    private: //add private:
        int m_i;
    };

    struct Gamma {
        Gamma() {}
        Gamma(const Gamma &o) {
            *m_d = *o.m_d;
        }
        Gamma &operator=(const Gamma &o) {
            *m_d = *o.m_d;
        }

        // remove constructor, since Gamma
        // didn't create the double
        // so it's not responsible for the deallocation
        //~Gamma() { delete m_d; }
        void set(double *d) { m_d = d; }
    private:
        double *m_d{nullptr};
    };

    int main() {
        //2.1
        const Alpha a{7};
        std::cout << a.get() << std::endl;

        //2.2
        int val{9};
        Beta b{val};

        int val2{42};
        b = Beta{val2};

        //2.3
        double pi{3.14}, e{2.62};
        Gamma g, h;
        g.set(&pi);
        h.set(&e);
        g = h;
    }
}
