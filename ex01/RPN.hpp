#ifndef RPN_HPP
#define RPN_HPP
#include <stdexcept>
#include <stack>
#include <string>
#include <sstream>

class RPN {
public:
	RPN(const std::string& input);
	~RPN();
	RPN& operator=(const RPN& other);
	int evaluate();

private:
	bool is_operator(const std::string& token);

	int apply_operator(int lhs, int rhs, const std::string& op);

	std::string input;
	std::stack<int> stack;
};


#endif
