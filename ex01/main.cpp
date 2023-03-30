#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " \"<expression>\"" << std::endl;
		return 0;
	}
	std::string input(argv[1]);

	RPN rpn(input);
	try {
		int result = rpn.evaluate();
		std::cout << "Result: " << result << std::endl;
	} catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
	}

	return 0;
}
