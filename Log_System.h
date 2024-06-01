#pragma once
#include <iostream>
#include "Square_Matrix.h"

class Log_System
{
private:
	static const char left_top_bracket[4];
	static const char right_top_bracket[4];
	static const char left_bottom_bracket[4];
	static const char right_bottom_bracket[4];

	static const char left_bracket[4];
	static const char right_bracket[4];

	static const char vertical_line[4];

	static const std::string offset;
public:
	Log_System() = default;
	Log_System(const std::string& purpose);
	~Log_System();

	void message(const std::string& message);
	void intermediateStepsInverse(const Square_Matrix<Fraction>& first, const Square_Matrix<Fraction>& second);
	void intermediateSteps(const Square_Matrix<Fraction>& object);
	void updateInfoToOne(const size_t& row, const Fraction& coefficient);
	void updateInfoToZero(const size_t& row1, const size_t& row2, const Fraction& coefficient);
};

