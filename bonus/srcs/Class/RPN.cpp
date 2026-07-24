#include "RPN.hpp"
#include <sstream>

RPN::RPN() {

}

RPN::RPN(const RPN &copy) {
	(void)copy;
}

RPN::~RPN() {

}

RPN	&RPN::operator=(const RPN &copy) {
	(void)copy;
	return (*this);
}

std::string	RPN::_rpn_error() {
	while (!this->_stack.empty())
		this->_stack.pop();
	return ("RPN Error format :(");
}

std::string	RPN::rpn(std::string expression) {
	size_t	i = 0;
	std::ostringstream oss;
	int	result = 0, a, b;
	while (i < expression.length()) {
		if (expression[i] <= '9' && expression[i] >= '0') {
			int	n = 0;
			while (i < expression.length() && expression[i] <= '9' && expression[i] >= '0')
				n = n * 10 + static_cast<int>(expression[i++] - '0');
			if (i == expression.length())
				return (this->_rpn_error());
			this->_stack.push(n);
		} else {
			if (this->_stack.size() < 2)
				return (this->_rpn_error());
			b = this->_stack.top();
			this->_stack.pop();
			a = this->_stack.top();
			this->_stack.pop();
			switch (expression[i]) {
				case '+':
					result = a + b;
					break;
				case '-':
					result = a - b;
					break;
				case '*':
					result = a * b;
					break;
				case '/':
					if (b == 0)
						return (this->_rpn_error());
					result = a / b;
					break;
				default:
					return (this->_rpn_error());
			}
			this->_stack.push(result);
			++i;
		}
		if (i == expression.length()) {
			if (this->_stack.size() != 1)
				return (this->_rpn_error());
			result = this->_stack.top();
			this->_stack.pop();
			oss << "Your RPN result is => " << result;
			return (oss.str());
		} else if (expression[i] != ' ')
			return (this->_rpn_error());
		++i;
	}
	return (this->_rpn_error());
}
