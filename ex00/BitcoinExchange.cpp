#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <limits>
#include <iostream>

static int stringToInt(const std::string& str) {
	int result;
	std::istringstream ss(str);
	if (!(ss >> result) || ss.fail()) {
		throw std::invalid_argument("Error: invalid integer: " + str);
	}
	return result;
}

static double stringToDouble(const std::string &str) {
	double result;
	std::istringstream iss(str);
	if (!(iss >> result) || iss.fail()) {
		std::cout << result << std::endl;
		throw std::invalid_argument("Error: invalid double: " + str);
	}
	return result;
}

BitcoinExchange::BitcoinExchange(const std::string& filename) {
	std::ifstream input(filename.c_str());
	if (!input) {
		std::cout << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(input, line);  // Ignore the line header
	while (std::getline(input, line)) {
		std::istringstream iss(line);
		std::string dateStr, exchangeRateStr;
		double exchangeRate;
		if (!(std::getline(iss, dateStr, ',') && std::getline(iss, exchangeRateStr))) {
			std::cout << "Error: bad input line: " << line << std::endl;
			continue;
		}
		try {
			exchangeRate = stringToDouble(exchangeRateStr);
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			continue;
		}
		PriceEntry priceEntry = {dateStr, exchangeRate};
		bitcoinPrices[dateStr] = priceEntry;
	}

}

std::time_t BitcoinExchange::dateToTime(const std::string& dateStr) {
	int year = stringToInt(dateStr.substr(0, 4));
	int month = stringToInt(dateStr.substr(5, 2));
	int day = stringToInt(dateStr.substr(8, 2));

	if (year < 1900 || month < 1 || month > 12 || day < 1 || day > daysInMonth(month, year)) {
		throw std::invalid_argument("Error: invalid date string: " + dateStr);
	}

	std::tm tm = {0, 0, 0,
				day, month - 1, year - 1900,
				0, 0, 0, 0, NULL};

	std::time_t result = std::mktime(&tm);
	if (result == -1) {
		throw std::invalid_argument("Error: invalid date string: " + dateStr);
	}
	return result;
}

int BitcoinExchange::daysInMonth(int month, int year) {
	static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
		return 29;
	} else {
		return days[month - 1];
	}
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const {
	std::string closestDate;
	double minDiff = std::numeric_limits<double>::max();

	std::time_t inputTime = dateToTime(date);

	for (std::map<std::string, PriceEntry>::const_iterator it = bitcoinPrices.begin();
			it != bitcoinPrices.end();
			++it) {
		std::time_t priceTime = dateToTime(it->first);

		if (priceTime <= inputTime) {
			double diff = std::difftime(inputTime, priceTime);
			if (diff < minDiff) {
				minDiff = diff;
				closestDate = it->first;
			}
		}
	}

	return closestDate;
}


double BitcoinExchange::findBitcoinPrice(const std::string& date) const {
	if (bitcoinPrices.count(date) > 0) {
		return bitcoinPrices.find(date)->second.price;
	}
	std::string closestDate = findClosestDate(date);
	if (!closestDate.empty()) {
		return bitcoinPrices.find(closestDate)->second.price;
	}
	return -1;
}

BitcoinExchange::~BitcoinExchange() {

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		bitcoinPrices = other.bitcoinPrices;
	}
	return *this;
}

