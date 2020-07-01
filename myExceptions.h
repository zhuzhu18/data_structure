#pragma once

#include<exception>
#include<string>

class illegalParameterValue :public std::exception {
public:
	illegalParameterValue(const std::string& s) {
		this->s = s;
	}
	virtual const char* what() const throw() {
		return s.c_str();
	}
private:
	std::string s;
};

class queueEmpty:public std::exception {
public:
	queueEmpty(std::string theMessage =
		"Invalid operation on empty queue\n") {
		message = theMessage;
	}
	virtual const char* what() const throw() {
		return message.c_str();
	}
private:
	std::string message;
};
