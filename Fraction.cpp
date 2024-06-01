#include "Fraction.h"

//Simplify
void Fraction::simplify() {
	int gcd = std::gcd(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;

	if (denominator < 0) {
		numerator *= -1;
		denominator *= -1;
	}
}
// Constructors
Fraction::Fraction() 
	: numerator(0), denominator(1) {}
Fraction::Fraction(const int& num, const int& den) 
	: numerator(num), denominator(den)
{
	simplify();
}

Fraction::Fraction(const int& num) 
	: numerator(num), denominator(1) {}
Fraction::Fraction(const unsigned int& num)
	: numerator(num), denominator(1) {}
Fraction::Fraction(const long int& num)
	: numerator(num), denominator(1) {}
Fraction::Fraction(const unsigned long int& num)
	: numerator(num), denominator(1) {}
Fraction::Fraction(const long long& num)
	: numerator(num), denominator(1) {}
Fraction::Fraction(const unsigned long long& num)
	: numerator(num), denominator(1) {}
Fraction::Fraction(const short& num)
	: numerator(num), denominator(1) {}
Fraction::Fraction(const unsigned short& num)
	: numerator(num), denominator(1) {}

Fraction::Fraction(float num)
{
	int p = 1;
	int i = 0;
	while (num != int(num) && i < precision) {
		num *= 10;
		p *= 10;
		i++;
	}

	numerator = num;
	denominator = p;

	simplify();
}
Fraction::Fraction(double num)
{
	int p = 1;
	const int precision = 6;
	int i = 0;
	while (num != int(num) && i < precision) {
		num *= 10;
		p *= 10;
		i++;
	}

	numerator = num;
	denominator = p;

	simplify();
}



//Operations
Fraction Fraction::operator+(const Fraction& other) const {
	Fraction result;

	result.numerator = numerator * other.denominator + other.numerator * denominator;
	result.denominator = denominator * other.denominator;

	result.simplify();

	return result;
}
Fraction Fraction::operator+(const int& other) const {
	Fraction result;

	result.numerator = numerator + other * denominator;
	result.denominator = denominator;

	result.simplify();

	return result;
}
Fraction Fraction::operator-(const Fraction& other) const {
	Fraction result;

	result.numerator = numerator * other.denominator - other.numerator * denominator;
	result.denominator = denominator * other.denominator;

	result.simplify();

	return result;
}
Fraction Fraction::operator-(const int& other) const {
	Fraction result;

	result.numerator = numerator - other * denominator;
	result.denominator = denominator;

	result.simplify();

	return result;
}
Fraction Fraction::operator*(const Fraction& other) const {
	Fraction result;

	result.numerator = numerator * other.numerator;
	result.denominator = denominator * other.denominator;

	result.simplify();

	return result;
}
Fraction Fraction::operator*(const int& other) const {
	Fraction result;
	result.numerator = numerator * other;
	result.denominator = denominator;

	result.simplify();

	return result;
}
Fraction Fraction::operator/(const Fraction& other) const {
	Fraction result;

	result.numerator = numerator * other.denominator;
	result.denominator = denominator * other.numerator;

	result.simplify();

	return result;
}
Fraction Fraction::operator/(const int& other) const {
	Fraction result;
	result.numerator = numerator;
	result.denominator = denominator * other;

	result.simplify();

	return result;
}

// Logic operators
bool Fraction::operator==(const Fraction& other) const {
	return (numerator == other.numerator) && (denominator == other.denominator);
}
bool Fraction::operator==(const int& other) const {
	return (numerator == other) && (denominator == 1);
}
bool Fraction::operator!=(const Fraction& other) const {
	return !(*this == other);
}
bool Fraction::operator!=(const int& other) const {
	return !(*this == other);
}

//Insertion and Extraction
std::istream& operator>>(std::istream& in, Fraction& object) {
	in >> object.numerator >> object.denominator;

	return in;
}
std::ostream& operator<<(std::ostream& out, const Fraction& object) {
	out << object.numerator;
	if (object.denominator != 1) {
		out << '/' << object.denominator;
	}

	return out;
}

//Methods
std::string Fraction::getAsString() const {
	std::string result;

	result = std::to_string(numerator);
	if (denominator != 1) {
		result += '/' + std::to_string(denominator);
	}

	return result;
}

float Fraction::getAsFloat() const {
	return float(numerator) / denominator;
}
double Fraction::getAsDouble() const {
	return double(numerator) / denominator;
}