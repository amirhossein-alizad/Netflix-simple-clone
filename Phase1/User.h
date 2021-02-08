#ifndef USER_H
#define USER_H
#include <string>
#include "Film.h"
#include "Exception.h"
#define USERNAME "username"
#define PASSWORD "password"
#define ROLE "role"
#define PRINT 1
#define NOT_TO_PRINT 0
class User
{
protected:
	std::string role;
	std::string email;
	std::string username;
	std::string password;
	int id;
	int age;
public:
	User(std::string _role, std::string _email, std::string _username, std::string _password, int _age, int _id)
	: role(_role), email(_email), username(_username), password(_password), age(_age), id(_id){}
	std::string get_RUP(std::string);
	virtual int get_id() const = ZERO;
	virtual int how_many_films_bought() const = ZERO;
	virtual void add_notification(std::string notification) = ZERO ;
	virtual void show_followers() const = ZERO;
	virtual std::string get_email() const = ZERO;
	virtual void add_money(int amount) = ZERO;
	virtual bool has_bought_film(int film_id) = ZERO;
	virtual void buy_a_film(Film new_film, int price) = ZERO;
	virtual int how_much_money()  = ZERO;
	virtual void change_rate(int newrate, int film_id) = ZERO;
	virtual void show_films_bought(std::vector<std::string> lines_seperated, int min_year, int max_year, int min_rate, int price, std::string film_name, std::string director) = ZERO;
	virtual void show_notifications() = ZERO;
	virtual void show_notifications_limited(int limit) = ZERO;
};
#endif