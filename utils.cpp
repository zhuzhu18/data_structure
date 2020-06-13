#pragma once
#include<exception>

class illegalParameterValue :public std::exception {
public:
	illegalParameterValue(const char* s) {
		str = s;
	}
	virtual const char* what() const throw() {
		return str;
	}
private:
	const char* str;
};
