#include "Log_System.h"

//Unicode pharanthesis
const char Log_System::left_top_bracket[4] = u8"\u239B";
const char Log_System::right_top_bracket[4] = u8"\u239D";
const char Log_System::left_bottom_bracket[4] = u8"\u239E";
const char Log_System::right_bottom_bracket[4] = u8"\u23A0";

const char Log_System::left_bracket[4] = u8"\u239C";
const char Log_System::right_bracket[4] = u8"\u239F";

const char Log_System::vertical_line[4] = u8"\u23D0";

const std::string Log_System::offset = "    ";

//Construtor Destructor
Log_System::Log_System(const std::string& purpose) {
	std::cout << "[WARNING]: " << purpose << " calculation\n";
}
Log_System::~Log_System() {
	std::cout << "[WARNING] Success";
}

//Methods
void Log_System::message(const std::string& message) {
	std::cout << "[WARNING] " << message;
}

void Log_System::intermediateStepsInverse(const Square_Matrix<Fraction>& first, const Square_Matrix<Fraction>& second)
{
	size_t padding_size = 0;
	for (size_t i = 0; i < first.order(); i++)
	{
		for (size_t j = 0; j < first.order(); j++) {
			std::string content_cell = first[i][j].getAsString();
			padding_size = std::max(padding_size, content_cell.size());

			content_cell = second[i][j].getAsString();
			padding_size = std::max(padding_size, content_cell.size());
		}
	}	

	for (size_t i = 0; i < first.order(); i++)
	{
		std::cout << offset;

		if (i == 0)
			std::cout << left_top_bracket;
		else if (i == first.order() - 1)
			std::cout << right_top_bracket;
		else
			std::cout << left_bracket;

		for (size_t j = 0; j < first.order(); j++) {
			std::cout << std::setw(padding_size + 1) << first[i][j];
		}

		std::cout << ' ' << vertical_line;

		for (size_t j = 0; j < second.order(); j++) {
			std::cout << std::setw(padding_size + 1) << second[i][j];
		}

		if (i == 0)
			std::cout << right_top_bracket;
		else if (i == first.order())
			std::cout << right_bottom_bracket;
		else
			std::cout << right_bracket;

		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Log_System::intermediateSteps(const Square_Matrix<Fraction>& object) {

}

void Log_System::updateInfoToOne(const size_t& row, const Fraction& coefficient) {

}

void Log_System::updateInfoToZero(const size_t& row1, const size_t& row2, const Fraction& coefficient) {

}