#ifndef CUSTOMER_H
#define CUSTOMER_H 
#include "User.h"
#include "Exception.h"
#define ZERO 0
#define NAME "name"
#define DIRECTOR "director"
#define FILM_ID "film_id"
#define SUMMARY "summary"
#define PUBLISHER_ID "publisher_id"
#define YEAR "year"
#define PRICE "price"
#define LENGTH "length"
#define RATE "rate"
#define SEPERATOR " | "
#define DOT ". "
#define NOT_VALUATED -1
#define WHERE_QUESTION_MARK_IS 2
class Customer : public User
{
public:
	Customer(std::string _role, std::string _email, std::string _username, std::string _password, int _age, int _id)
	: User(_role, _email, _username, _password, _age, _id), id(_id) 
	{
		cash = ZERO;
	}
	std::vector<Film> films_bought;
	int how_many_films_bought() const; 
	void add_notification(std::string notification)  { notifications.push_back(notification); unread_notifications.push_back(notification); }
	void show_followers() const;
	std::string get_email() const;
	void add_money(int amount);
	bool has_bought_film(int film_id);
	void buy_a_film(Film new_film, int price);
	int how_much_money() { return cash; }
	void change_rate(int newrate, int film_id);
	std::string get_username() { return username; }
	int get_id() const { return id; }
	void show_films_bought(std::vector<std::string> lines_seperated, int min_year, int max_year, int min_rate, int price, std::string film_name, std::string director);
	void print_film(int &counter, std::vector<Film> films_bought, int j);
	void show_notifications();
	void show_notifications_limited(int limit);
private:
	int id;
	int cash;
	std::vector<std::string> notifications;
	std::vector<std::string> unread_notifications;
};
#endif	