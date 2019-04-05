//
// Created by massi on 01.04.2019.
//

#ifndef FRAMEWORK_ALPHA_H
#define FRAMEWORK_ALPHA_H

namespace bar {
    struct Alpha {
        virtual ~Alpha();
        virtual void set(double v=0);
        operator double() const;

    private:
        double m_v{-1};
    };
    struct Beta : Alpha {
        virtual ~Beta();
    };

}

#endif //FRAMEWORK_ALPHA_H
