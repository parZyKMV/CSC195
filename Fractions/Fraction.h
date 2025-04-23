#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <stdexcept>

namespace mathlib {
    class Fraction {
    private:
        int numerator;
        int denominator;

        static int findGCD(int a, int b);

    public:
        Fraction(int num = 0, int denom = 1);

       
        Fraction operator+(const Fraction& other) const;
        Fraction operator-(const Fraction& other) const;
        Fraction operator*(const Fraction& other) const;
        Fraction operator/(const Fraction& other) const;

      
        bool operator==(const Fraction& other) const;
        bool operator!=(const Fraction& other) const;
        bool operator<(const Fraction& other) const;
        bool operator<=(const Fraction& other) const;
        bool operator>(const Fraction& other) const;
        bool operator>=(const Fraction& other) const;

        
        friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);
        friend std::istream& operator>>(std::istream& is, Fraction& frac);

        
        Fraction Simplify() const;
        float ToFloat() const;
    };
}

#endif