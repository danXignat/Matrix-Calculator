#pragma once
#include <numeric>
#include <fstream>
#include <string>

struct Fraction
{
private:
	void simplify();
	static const int precision = 6;
public:
	long long numerator;
	long long denominator;

	Fraction();
	Fraction(const int& num, const int& den);
	~Fraction() = default;
	Fraction(const int& num);
	Fraction(const unsigned int& num);
	Fraction(const long int& num);
	Fraction(const unsigned long int& num);
	Fraction(const long long & num);
	Fraction(const unsigned long long & num);
	Fraction(const short& num);
	Fraction(const unsigned short& num);
	Fraction(float num);
	Fraction(double num);

	Fraction operator+(const Fraction& other) const;
	Fraction operator+(const int& other) const;
	Fraction operator-(const Fraction& other) const;
	Fraction operator-(const int& other) const;
	Fraction operator*(const Fraction& other) const;
	Fraction operator*(const int& other) const;
	Fraction operator/(const Fraction& other) const;
	Fraction operator/(const int& other) const;

	bool operator==(const Fraction& other) const;
	bool operator==(const int& other) const;
	bool operator!=(const Fraction& other) const;
	bool operator!=(const int& other) const;

	friend std::istream& operator>>(std::istream& in, Fraction& object);
	friend std::ostream& operator<<(std::ostream& out, const Fraction& object);

	std::string getAsString() const;
	float getAsFloat() const;
	double getAsDouble() const;
};

