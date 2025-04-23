#include "Fraction.h"
#include <stdexcept>
#include <cstdint>

int new_num;
int new_denom;

namespace mathlib
{
	Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom)
	{
		if (denom == 0) throw std::invalid_argument("Denominator cannot be zero");

	}

	Fraction Fraction::operator+(const Fraction& other) const {
		new_num = numerator * other.denominator + other.numerator * denominator;
		new_denom = denominator * other.denominator;

		return Fraction(new_num, new_denom).Simplify();
	}

	Fraction Fraction::operator-(const Fraction& other) const
	{
		new_num = numerator * other.denominator - other.numerator * denominator;
		new_denom = denominator * other.denominator;

		return Fraction(new_num, new_denom).Simplify();
	}

	Fraction Fraction::operator*(const Fraction& other)const
	{
		new_num = numerator * other.numerator;
		new_denom = denominator * other.denominator;

		return Fraction(new_num, new_denom).Simplify();
	}

	Fraction Fraction::operator/(const Fraction& other)const
	{
		new_num = numerator * other.denominator;
		new_denom = denominator * other.numerator;

		return Fraction(new_num, new_denom);
	}

	bool Fraction::operator==(const Fraction& other) const {
		if (this == &other) return true; 
		const int64_t lhs = static_cast<int64_t>(numerator) * other.denominator;
		const int64_t rhs = static_cast<int64_t>(denominator) * other.numerator;
		return lhs == rhs;
	}

	bool Fraction::operator!=(const Fraction& other) const {
		return !(*this == other);
	}

	bool Fraction::operator<(const Fraction& other) const {
		const int64_t lhs = static_cast<int64_t>(numerator) * other.denominator;
		const int64_t rhs = static_cast<int64_t>(denominator) * other.numerator;
		return lhs < rhs;
	}

	bool Fraction::operator<=(const Fraction& other) const {
		return !(*this > other);
	}

	bool Fraction::operator>(const Fraction& other) const {
		const int64_t lhs = static_cast<int64_t>(numerator) * other.denominator;
		const int64_t rhs = static_cast<int64_t>(denominator) * other.numerator;
		return lhs > rhs;
	}

	bool Fraction::operator>=(const Fraction& other) const {
		return !(*this < other); 
	}
	
	int Fraction::findGCD(int a, int b) {
		while (b != 0) {
			int temp = b;
			b = a % b;
			a = temp;
		}
		return a;
	}

	Fraction Fraction::Simplify()const
	{
		int gcd = findGCD(std::abs(numerator), std::abs(denominator));

		int simplyNum = numerator / gcd;
		int simplyDenom = denominator / gcd;

		if (simplyDenom < 0) {
			simplyNum = -simplyNum;
			simplyDenom = -simplyDenom;
		}
		return Fraction(simplyNum, simplyDenom);
	}

	float Fraction::ToFloat() const {
		return static_cast<float>(numerator) / denominator;
	}

	std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
		os << frac.numerator << "/" << frac.denominator;
		return os;
	}

	std::istream& operator>>(std::istream& is, Fraction& frac) {
		char slash;
		is >> frac.numerator >> slash >> frac.denominator;
		if (slash != '/' || frac.denominator == 0) {
			is.setstate(std::ios::failbit);
			throw std::invalid_argument("Invalid fraction format or zero denominator");
		}
		if (frac.denominator < 0) {
			frac.numerator = -frac.numerator;
			frac.denominator = -frac.denominator;
		}
		return is;
	}
}