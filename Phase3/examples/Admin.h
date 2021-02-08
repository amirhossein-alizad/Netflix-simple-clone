#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
class Admin : public User
{
public:
	Admin(std::string _role, std::string _email, std::string _username, std::string _password, int _age, int _id)
	: User(_role, _email, _username, _password, _age, _id) {}
	int get_id() const {}
	int how_many_films_bought() const {}
	void add_notification(std::string notification) {}
	void show_followers() const {}
	std::string get_email() const {}
	void add_money(int amount){} 
	bool has_bought_film(int film_id) {}
	void buy_a_film(Film new_film, int price) {}
	int how_much_money(){}
	void change_rate(int newrate, int film_id){}
	void show_films_bought(std::vector<std::string> lines_seperated, int min_year, int max_year, int min_rate, int price, std::string film_name, std::string director){}
	void show_notifications(){}
	void show_notifications_limited(int limit){}
	void put_flag_one(int film_id){}
	bool is_flag_one(int film_id){}

private:

};
#endif