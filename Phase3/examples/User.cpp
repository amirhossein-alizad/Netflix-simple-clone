#include "User.h"
std::string User::get_RUP(std::string input)
{
	if(input == ROLE)
		return role;
	else if(input == USERNAME)
		return username;
	else if(input == PASSWORD)
		return password;
}