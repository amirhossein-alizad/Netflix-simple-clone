#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception> 
#define NOT_FOUND "Not Found"
#define BAD_REQUEST "Bad Request"
#define PERMISSION_DENIED "Permission Denied"

class Not_Found : public std::exception
{
public:
	const char * what() const throw() {return NOT_FOUND;}
};

class Bad_Request : public std::exception
{
public:
	const char* what() const throw() {return BAD_REQUEST;}
};

class Permission_Denied : public std::exception
{
public:
	const char* what() const throw() {return PERMISSION_DENIED;}
};

#endif