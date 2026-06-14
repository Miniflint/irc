#ifndef USER_HPP
# define USER_HPP

# include "string"
# include "iostream"

class User {
	protected:
		std::string		_nick;
	public:
		User();
		~User();
};

#endif