#include <iostream>
#include "RPN.hpp"

RPN::RPN(const std::string& input) : input(input) {}

int static string_to_int(const std::string& str) {
	int result;
	std::istringstream iss(str);
	if (!(iss >> result) || iss.fail()) {
		throw std::invalid_argument("invalid int input [" + str + "]");
	}
	return result;
}

int RPN::evaluate() {
	std::string token;
	std::stringstream ss(input);

	while (ss >> token) {
		if (is_operator(token)) {
			if (stack.size() < 2) {
				throw std::invalid_argument("input results in calling operator on stack with less than 2 entries");
			}
			int rhs = stack.top();
			stack.pop();
			int lhs = stack.top();
			stack.pop();
			stack.push(apply_operator(lhs, rhs, token));
		} else {
			stack.push(string_to_int(token));
		}
	}

	if (stack.size() != 1) {
		throw std::invalid_argument("input contains too many/few numbers");
	}
	return stack.top();
}

bool RPN::is_operator(const std::string& token) {
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

int RPN::apply_operator(int lhs, int rhs, const std::string& op) {
	if (op == "+") {
		return lhs + rhs;
	} else if (op == "-") {
		return lhs - rhs;
	} else if (op == "*") {
		return lhs * rhs;
	} else if (op == "/") {
		if (rhs == 0) {
			throw std::invalid_argument("division by zero");
		}
		return lhs / rhs;
	} else {
		throw std::invalid_argument("unknown operator");
	}
}

RPN::~RPN() {

}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		input = other.input;
		stack = other.stack;
	}
	return *this;
}

