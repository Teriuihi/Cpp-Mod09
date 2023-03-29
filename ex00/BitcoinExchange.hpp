#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <map>
#include <string>

struct PriceEntry {
	std::string date;
	double price;
};

class BitcoinExchange {
public:
	// Constructors and destructor
	BitcoinExchange(const std::string& filename);
	~BitcoinExchange();

	// Assignment operator
	BitcoinExchange& operator=(const BitcoinExchange& other);

	// Public member functions
	double findBitcoinPrice(const std::string& date) const;

private:
	// Private data members
	std::map<std::string, PriceEntry> bitcoinPrices;

	// Private member functions
	std::string findClosestDate(const std::string& date) const;
	static time_t dateToTime(const std::string& dateStr) ;
};

#endif
