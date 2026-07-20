#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>

class RPN
{
	public:
		RPN();
		RPN(const RPN &copy);
		~RPN();
		RPN	&operator=(const RPN &copy);
		std::string	rpn(std::string expression);
	private:
		std::stack<int>	_stack;
		std::string	_rpn_error();
};

#endif