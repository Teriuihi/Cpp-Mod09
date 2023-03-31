#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "BitcoinExchange.hpp"

static double stringToDouble(const std::string &str) {
	double result;
	std::istringstream iss(str);
	if (!(iss >> result) || iss.fail()) {
		throw std::invalid_argument("Error: invalid double: " + str);
	}
	return result;
}


int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " input_file.txt" << std::endl;
		return 1;
	}

	BitcoinExchange exchange("data.csv");

	std::ifstream inputFile(argv[1]);
	if (!inputFile.is_open()) {
		std::cerr << "Error: could not open input file.\n";
		return 1;
	}

	std::string line;
	std::getline(inputFile, line); //Ignore header
	while (std::getline(inputFile, line)) {
		std::istringstream ss(line);
		std::string dateStr, valueStr;
		double value;

		if (!std::getline(ss, dateStr, '|') || !std::getline(ss, valueStr, '|')) {
			std::cout << "Error: invalid line: " << line << std::endl;
			continue;
		}
		dateStr.erase(std::remove(dateStr.begin(), dateStr.end(), ' '), dateStr.end());
		valueStr.erase(std::remove(valueStr.begin(), valueStr.end(), ' '), valueStr.end());
		try {
			value = stringToDouble(valueStr);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			continue;
		}
		if (value <= 0) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		double bitcoinPrice;
		try {
			bitcoinPrice = exchange.findBitcoinPrice(dateStr);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			continue;
		}
		if (bitcoinPrice < 0) {
			std::cout << "Error: could not find a valid date." << std::endl;
			continue;
		}
		double convertedValue = value * bitcoinPrice;
		if (convertedValue > 1000) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		std::cout << dateStr << " => " << value << " = " << convertedValue << std::endl;
	}

	return 0;
}
