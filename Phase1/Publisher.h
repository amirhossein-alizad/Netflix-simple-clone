#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "User.h"
#include "Film.h"
#include "Customer.h"
#include "Exception.h"
#define FILM_ID "film_id"
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
#define USERNAME "username"
#define GOOD 8
#define BAD 5
#define BAD_PERCENTAGE 0.8
#define GOOD_PERCENTAGE 0.95
#define NOT_BAD_NOT_GOOD_PERCENTAGE 0.9
#define ONE 1
class Publisher : public User
{
public:
	Publisher(std::string _role, std::string _email, std::string _username, std::string _password, int _age, int _id)
	: User(_role, _email, _username, _password, _age, _id), username(_username), id(_id), email(_email) 
	{
		cash_not_sent = ZERO;
		cash = ZERO;
	}
	std::string return_username(){ return username; }
	void publishers_film(Film );
	std::vector<Film> films_published;
	std::vector<Film> films_bought;
	std::vector<User*> followers;
	void edit_bought_films();
	int how_many_films_bought() const;
	int return_id(){ return id; }
	void add_follower(User* follower){ followers.push_back(follower); }
	void add_notification(std::string notification)  { notifications.push_back(notification);  unread_notifications.push_back(notification); }
	int how_many_followers();
	void show_followers() const;
	std::string get_email() const;
	int get_id() const { return id; }
	void add_money(int amount);
	bool has_bought_film(int film_id);
	void buy_a_film(Film new_film, int price);
	int how_much_money() { return cash; }
	int get_money(int film_price, float film_rate);
	void set_new_money();
	void change_rate(int newrate, int film_id);
	void show_films_bought(std::vector<std::string> lines_seperated, int min_year, int max_year, int min_rate, int price, std::string film_name, std::string director);
	void print_film(int &counter, std::vector<Film> films_bought, int j);
	void show_notifications();
	void show_notifications_limited(int limit);
private:
	std::string username;
	std::string email;
	int id;
	int cash;
	int cash_not_sent;
	std::vector<std::string> notifications;
	std::vector<std::string> unread_notifications;
};
#endif