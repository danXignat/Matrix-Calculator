#pragma once
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <cwchar>
#include <stdexcept>
#include <optional>

#include "Fraction.h"

template <typename T>
class Square_Matrix
{
private:
	size_t m_order;
	T** m_data;

public:
	Square_Matrix<T> zeroMatrix() const;
	Square_Matrix<T> identityMatrix() const;

	std::optional<size_t> findNonZero(const size_t& start);
	void swapRows(const size_t& initial, const size_t& target);
	T getCoeffToZero(const size_t& index1, const size_t& index2);
	T getCoeffToOne(const size_t& target);
	void updateRowtoZero(const size_t& index1, const size_t& index2, const T& coefficient);
	void updateRowtoOne(const size_t& target, const T& coefficient);

public:
	Square_Matrix();
	Square_Matrix(const size_t& order);
	Square_Matrix(const Square_Matrix<T>& other);
	~Square_Matrix();

	template <typename T> friend std::istream& operator>>(std::istream& in, Square_Matrix<T>& other);
	template <typename T> friend std::ostream& operator<<(std::ostream& in, const Square_Matrix<T>& other);

	void resize(const size_t& newSize);
	const size_t order() const;
	T* operator[](const size_t& index);
	const T* operator[](const size_t& index) const;

	bool& operator==(const Square_Matrix<T>& other) const;
	bool& operator!=(const Square_Matrix<T>& other) const;

	Square_Matrix<T>& operator=(const Square_Matrix<T>& other);
	Square_Matrix<T>& operator+=(const Square_Matrix<T>& other);
	Square_Matrix<T>& operator-=(const Square_Matrix<T>& other);
	Square_Matrix<T>& operator*=(const Square_Matrix<T>& other);
	Square_Matrix<T> operator+(const Square_Matrix<T>& other) const;
	Square_Matrix<T> operator-(const Square_Matrix<T>& other) const;
	Square_Matrix<T> operator*(const Square_Matrix<T>& other) const;
	Square_Matrix<T> operator*(const T& scalar) const;
	Square_Matrix<T> operator^(int power);
	Fraction operator!() const;

	Fraction determinant() const;
	Square_Matrix<T> transpose() const;
	Square_Matrix<Fraction> inverse() const;
};

// Constructors, copy Constructor, Destructor
template <typename T>
Square_Matrix<T>::Square_Matrix()
	: m_order(0), m_data(nullptr) {}

template <typename T>
Square_Matrix<T>::Square_Matrix(const size_t& order)
	: m_order(order)
{
	m_data = new T * [m_order];
	for (size_t i = 0; i < m_order; i++) {
		m_data[i] = new T[m_order];
	}
}

template <typename T>
Square_Matrix<T>::Square_Matrix(const Square_Matrix& other)
	: m_order(other.m_order)
{
	m_data = new T * [m_order];
	for (size_t i = 0; i < m_order; i++) {
		m_data[i] = new T[m_order]();
		for (size_t j = 0; j < m_order; j++) {
			m_data[i][j] = other.m_data[i][j];
		}
	}
}
template <typename T>
Square_Matrix<T>::~Square_Matrix()
{
	for (size_t i = 0; i < m_order; i++) {
		delete[] m_data[i];
	}
	delete[] m_data;
}

//Overloads Extraction and Insertion
template <typename T>
std::istream& operator>>(std::istream& in, Square_Matrix<T>& other)
{
	for (size_t i = 0; i < other.m_order; i++) {
		for (size_t j = 0; j < other.m_order; j++) {
			in >> other.m_data[i][j];
		}
	}

	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const Square_Matrix<T>& other)
{
	if (other.m_order == 0) {
		return out;
	}

	if (other.m_order == 1) {
		out << '(' << other.m_data[0][0] << ')' << std::endl;
		return out;
	}

	size_t padding_size = 0;
	for (size_t i = 0; i < other.m_order; i++) {
		for (size_t j = 0; j < other.m_order; j++) {
			std::string content_cell;

			if constexpr (std::is_same<T, std::string>::value)
				content_cell = other.m_data[i][j];
			else if constexpr (std::is_same<T, Fraction>::value) {
				content_cell = other.m_data[i][j].getAsString();
			}
			else
				content_cell = std::to_string(other.m_data[i][j]);

			padding_size = std::max(padding_size, content_cell.size());
		}
	}

	for (size_t i = 0; i < other.m_order; i++) {
		if (i == 0)
			out << u8"\u239B";
		else if (i == other.m_order - 1)
			out << u8"\u239D";
		else
			out << u8"\u239C";

		for (size_t j = 0; j < other.m_order; j++) {
			std::string content_cell;

			if constexpr (std::is_same<T, std::string>::value) {
				content_cell = other.m_data[i][j];
			}
			else if constexpr (std::is_same<T, Fraction>::value) {
				content_cell = other.m_data[i][j].getAsString();
			}
			else
				content_cell = std::to_string(other.m_data[i][j]);

			out << std::setw(padding_size) << content_cell << ' ';
		}

		if (i == 0)
			out << u8"\u239E";
		else if (i == other.m_order - 1)
			out << u8"\u23A0";
		else
			out << u8"\u239F";

		out << std::endl;
	}

	return out;
}


// Resize, Size getter, Accessor, Atribution overload
template<typename T>
void Square_Matrix<T>::resize(const size_t& newSize)
{
	T** newBlock;
	newBlock = new T* [newSize];
	for (size_t i = 0; i < newSize; i++) {
		newBlock[i] = new T[newSize];
	}

	for (size_t i = 0; i < std::min(newSize, m_order); i++) {
		for (size_t j = 0; j < std::min(newSize, m_order); j++) {
			newBlock[i][j] = m_data[i][j];
		}
	}

	for (size_t i = m_order; i < newSize; i++) {
		for (size_t j = 0; j <= i; j++) {
			newBlock[i][j] = newBlock[j][i] = 0;
		}
	}

	this->~Square_Matrix();

	m_order = newSize;
	m_data = newBlock;
}

template<typename T>
const size_t Square_Matrix<T>::order() const{
	return m_order;
}
template<typename T>
T* Square_Matrix<T>::operator[](const size_t& index) {
	return m_data[index];
}
template<typename T>
const T* Square_Matrix<T>::operator[](const size_t& index) const {
	return m_data[index];
}


// Op logici
template<typename T>
bool& Square_Matrix<T>::operator==(const Square_Matrix<T>& other) const{
	if (other.m_order != m_order)
		return false;

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			if (m_data[i][j] != other.m_data[i][j])
				return false;
		}
	}

	return true;
}

template<typename T>
bool& Square_Matrix<T>::operator!=(const Square_Matrix<T>& other) const{
	return !(*this == other);
}

// Operators
template<typename T>
Square_Matrix<T>& Square_Matrix<T>::operator=(const Square_Matrix<T>& other)
{
	if (this != &other) {
		this->~Square_Matrix();

		m_order = other.m_order;
		m_data = new T * [m_order];
		for (size_t i = 0; i < m_order; i++) {
			m_data[i] = new T[m_order];
		}

		for (size_t i = 0; i < m_order; i++) {
			for (size_t j = 0; j < m_order; j++) {
				m_data[i][j] = other.m_data[i][j];
			}
		}
	}

	return *this;
}

template<typename T>
Square_Matrix<T> Square_Matrix<T>::operator+(const Square_Matrix<T>& other) const {
	if (m_order != other.m_order) {
		throw std::invalid_argument("Matrices must have the same orders for addition");
	}

	Square_Matrix<T> result(m_order);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			result.m_data[i][j] = m_data[i][j] + other.m_data[i][j];
		}
	}

	return result;
}

template<typename T>
Square_Matrix<T> Square_Matrix<T>::operator-(const Square_Matrix<T>& other) const {
	if (m_order != other.m_order) {
		throw std::invalid_argument("Matrices must have the same orders for addition");
	}

	Square_Matrix<T> result(m_order);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			result.m_data[i][j] = m_data[i][j] - other.m_data[i][j];
		}
	}

	return result;
}

template <typename T>
Square_Matrix<T> Square_Matrix<T>::operator*(const Square_Matrix<T>& other) const {
	if (m_order != other.m_order) {
		throw std::invalid_argument("Matrices must have the same orders for addition");
	}

	Square_Matrix<T> result(m_order);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			result.m_data[i][j] = 0;
			for (size_t k = 0; k < m_order; k++) {
				result.m_data[i][j] = result.m_data[i][j] + m_data[i][k] * other.m_data[k][j];
			}
		}
	}

	return result;
}

template <typename T>
Square_Matrix<T> Square_Matrix<T>::operator*(const T& scalar) const {
	Square_Matrix<T> result = (*this);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			result.m_data[i][j] = result.m_data[i][j] * scalar;
		}
	}

	return result;
}

template <typename T>
Square_Matrix<T> Square_Matrix<T>::operator^(int power)  {
	Square_Matrix<T> result = this->identityMatrix();
	Square_Matrix<T> temp = (*this);

	while (power) {
		if (power % 2 == 1) {
			result = result * temp;
		}
		power /= 2;
		temp = temp * temp;
	}

	return result;
}

template<typename T>
Square_Matrix<T>& Square_Matrix<T>::operator+=(const Square_Matrix<T>& other)
{
	(*this) = (*this) + other;

	return *this;
}

template<typename T>
Square_Matrix<T>& Square_Matrix<T>::operator-=(const Square_Matrix<T>& other)
{
	(*this) = (*this) - other;

	return *this;
}

template<typename T>
Square_Matrix<T>& Square_Matrix<T>::operator*=(const Square_Matrix<T>& other)
{
	(*this) = (*this) * other;

	return *this;
}

template <typename T>
Fraction Square_Matrix<T>::operator!() const {
	return this->determinant();
}

//Private Methods

template<typename T>
Square_Matrix<T> Square_Matrix<T>::zeroMatrix() const {
	Square_Matrix<T> zero(m_order);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			zero[i][j] = 0;
		}
	}

	return zero;
}

template<typename T>
Square_Matrix<T> Square_Matrix<T>::identityMatrix() const {
	Square_Matrix<T> identity(m_order);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			if (i == j)
				identity[i][j] = 1;
			else
				identity[i][j] = 0;
		}
	}

	return identity;
}

template<typename T>
std::optional<size_t> Square_Matrix<T>::findNonZero(const size_t& start) {
	for (size_t i = start + 1; i < this->order(); i++) {
		if ((*this)[i][start] != 0) {
			return i;
		}
	}
	return std::nullopt;
}

template<typename T>
void Square_Matrix<T>::swapRows(const size_t& initial, const size_t& target)
{
	for (size_t i = 0; i < this->order(); i++) {
		(*this)[initial][i] = (*this)[initial][i] * (-1);
		std::swap((*this)[initial][i], (*this)[target][i]);
	}
}

template<typename T>
T Square_Matrix<T>::getCoeffToZero(const size_t& index1, const size_t& index2)
{
	T initialVal = (*this)[index1][index1];
	T targetVal = (*this)[index2][index1];
	T coefficient = targetVal / initialVal;

	return coefficient;
}

template<typename T>
T Square_Matrix<T>::getCoeffToOne(const size_t& target)
{
	T targetVal = (*this)[target][target];
	T coefficient = Fraction(1) / targetVal;

	return coefficient;
}

template<typename T>
void Square_Matrix<T>::updateRowtoZero(const size_t& index1, const size_t& index2, const T& coefficient)
{	
	/*		
				i1
			 -  -  - - -
		i1	 -  vi - - -
			 -  -  - - -
			 -  -  - - -
		i2	 -  vt - - -
	*/

	for (size_t j = 0; j < this->order(); j++) {
		(*this)[index2][j] = (*this)[index2][j] - coefficient * (*this)[index1][j];
	}
}

template<typename T>
void Square_Matrix<T>::updateRowtoOne(const size_t& target,  const T& coefficient)
{
	for (size_t j = 0; j < this->order(); j++) {
		(*this)[target][j] = (*this)[target][j] * coefficient;
	}
}

//Methods
template<typename T>
Fraction Square_Matrix<T>::determinant() const
{
	if constexpr (!(std::is_arithmetic<T>::value)) {
		throw std::invalid_argument("Type is not a number type");
	}

	Fraction result(1);

	Square_Matrix<Fraction> temp(m_order);
	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			temp[i][j] = Fraction( m_data[i][j] );
		}
	}

	for (size_t j = 0; j < m_order; j++) {

		if (temp[j][j] == 0) {
			auto found = temp.findNonZero(j);
			if (found.has_value()) {
				temp.swapRows(j, found.value());
				std::cout << temp;
			}
			else
				result = Fraction(0);
		}

		for (size_t i = j + 1; i < m_order; i++) {
			if (temp[i][j] != 0) {
				temp.updateRowtoZero(j, i, temp.getCoeffToZero(j, i));
				std::cout << temp;
			}
		}
	}

	for (size_t i = 0; i < m_order; i++) {
		result = result * temp[i][i];
	}

	return result;
}

template<typename T>
Square_Matrix<T> Square_Matrix<T>::transpose() const
{
	Square_Matrix<T> temp(m_order);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			temp[i][j] = m_data[j][i];
		}
	}

	return temp;
}

template<typename T>
Square_Matrix<Fraction> Square_Matrix<T>::inverse() const
{
	if constexpr (!(std::is_arithmetic<T>::value)) {
		throw std::invalid_argument("Type is not a number type");
	}

	Square_Matrix<Fraction> temp(m_order);
	Square_Matrix<Fraction> inverse(m_order);

	for (size_t i = 0; i < m_order; i++) {
		for (size_t j = 0; j < m_order; j++) {
			temp[i][j] = Fraction(m_data[i][j]);
		}
	}
	inverse = inverse.identityMatrix();

	for (size_t j = 0; j < m_order; j++) {
		if (temp[j][j] == 0) {
			auto found = temp.findNonZero(j);

			if (found.has_value()) {
				temp.swapRows(j, found.value());
				inverse.swapRows(j, found.value());

			}
		}

		if (temp[j][j] != 1) {
			auto coefficient = temp.getCoeffToOne(j);
			temp.updateRowtoOne(j, coefficient);
			inverse.updateRowtoOne(j, coefficient);

		}

		for (size_t i = 0; i < m_order; i++) {
			if (temp[i][j] != 0 && (i != j)) {
				auto coefficient = temp.getCoeffToZero(j, i);
				temp.updateRowtoZero(j, i, coefficient);
				inverse.updateRowtoZero(j, i, coefficient);

			}
		}
	}
	
	return inverse;
}