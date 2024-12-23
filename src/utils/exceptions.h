// Exception Handling support header.

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

#define VALIDATE_ARGUMENT(condition, arg, message)\
	if(!(condition)){\
		throw std::invalid_argument((std::string(message) + "\r\nParameter name: " + #arg).c_str());\
	}

#define VALIDATE_ARGUMENT_RANGE(arg, min, max)\
	if(((arg) < (min) && std::fabs((arg) - (min)) > Constants::DoubleEpsilon) || \
	  ((arg) > (max) && std::fabs((arg) - (max)) > Constants::DoubleEpsilon)){\
		throw std::out_of_range("Argument is out of range["#min","#max"]\r\nParameter name: " #arg);\
	}

#endif