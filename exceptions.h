#include <exception>
#pragma once

class custom_exceptions:public std::exception{
public: 
	std::string message;
}

class network_exception: public custom_exceptions{
public:
	network_exception():message("Network exception occured!");
}
class database_exception: public custom_exceptions{
public:
	database_exception():message("Database error occurred!");
}
class user_password_exception: public custom_exceptions{
public:
	user_password_exeption():message("Wrong username or password");
}
