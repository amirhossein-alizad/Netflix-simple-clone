#ifndef MANAGER_H
#define MANAGER_H

#define FIRST_ELEMENT 0
#define SECOND_ELEMENT 1
#define THIRD_ELEMENT 2
#define FOURTH_ELEMENT 3
#define START_OF_ACTION 3
#define IS_PUBLISHER 1
#define NOT_PUBLISHER 0
#define DOES_NOT_EXIST 0
#define EXISTS 1
#define BREAK 1
#define NOT_TO_BREAK 0
#define PRINT 1
#define NOT_TO_PRINT 0
#define HAS_BOUGHT 1
#define HAS_NOT_BOUGHT 0
#define REPEAT 1
#define NOT_TO_REPEAT 0
#define ZERO 0
#define NOTIFICATIONS "notifications"
#define PURCHASED "purchased"
#define COMMENTS "comments"
#define POST "POST"
#define PUT "PUT"
#define LOGIN "login"
#define SIGNUP "signup"
#define FILMS "films"
#define USERNAME "username"
#define PASSWORD "password"
#define EMAIL "email"
#define AGE "age"
#define PUBLISHER "publisher"
#define CUSTOMER "customer"
#define OK "OK"
#define QUESTION_MARK "?"
#define DELETE "DELETE"
#define FOLLOWERS "followers"
#define GET "GET"
#define PUBLISHED "published"
#define MONEY "money"
#define AMOUNT "amount"
#define RATE "rate"
#define FILM_ID "film_id"
#define YEAR "year"
#define BUY "buy"
#define NAME "name"
#define ROLE "role"
#define LENGTH "length"
#define PRICE "price"
#define SUMMARY "summary"
#define DIRECTOR "director"
#define PUBLISHER_ID "publisher_id"
#define USER_ID "user_id"
#define MAX_YEAR "max_year"
#define MIN_YEAR "min_year"
#define MIN_RATE "min_rate"
#define SCORE "score"
#define COMMENT_ID "comment_id"
#define REPLIES "replies"
#define READ "read"

#include "Publisher.h"
#include "Exception.h"
#include <iostream>
#include <string>	
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>

class Manager
{
public:
	Manager();
	~Manager();
	void run();
	std::vector<std::string> seperate_lines(std::string input);
	bool signup_exists(std::vector<std::string> lines_seperated, int username_index);
	void signup(std::string &username, std::string &password, std::string email, int &age, std::vector<std::string> lines_seperated);
	void find_username_and_password(std::string & _username, std::string &_password, std::vector<std::string>);
	void login(std::string &username, std::string &password, std::vector<std::string>);
	void check_if_user_is_publisher(std::string username);
	int return_publisher_id(std::string username);
	void hash(std::string &str);
	void add_film(std::string username, std::vector<std::string> lines_seperated);
	int find_film_id(std::vector<std::string> lines_seperated);
	void edit_film_for_every_one(std::string username, std::vector<std::string> lines_seperated, int &year, int &length, int &price, std::string &film_name,
 	std::string &director, std::string &summary, int film_id);
	bool is_email_valid(const std::string& email);
	void buy_for_user(std::string username, int &publisher_id, int film_id);
	std::string add_notification_for_buying(int publisher_id, std::string username, int film_id);
	void add_notification_for_rate(std::string username, int film_id, int publisher_id);
	void check_if_bought(std::string username, int film_id);
	bool check_if_has_char(std::string input);
 	void edit_film_for_publisher(std::string username, int film_id, int year, int length, int price, std::string film_name, std::string director, std::string summary);
 	void delete_films(std::string username, std::vector<std::string> lines_seperated);
 	int find_user_id(std::vector<std::string> lines_seperated);
 	void follow(std::vector<std::string> lines_seperated, std::string username);
 	void get_followers(std::string username);
 	int how_many_published(std::string username);
 	void show_films(std::vector<std::string> lines_seperated, std::string username);
 	void post_money(std::vector<std::string> lines_seperated, std::string username);
 	void get_film_info(std::string username, std::vector<std::string> lines_seperated, int & repeatition);
 	bool user_is_publisher(std::string username);
 	void send_money_to_publisher(int film_id, std::string username, std::string notification);
 	void buy(std::string username, std::vector<std::string> lines_seperated);
 	void add_money_to_publisher(std::string username);
 	void rate(std::string username, std::vector<std::string> lines_seperated);
 	int find_id(std::string username);
 	std::string find_film_name(int film_id);
 	void print_film(int &counter, std::vector<Film> films_published, int j);
 	void search_films(std::string username, std::vector<std::string> lines_seperated, int repeatition);
 	std::string find_comment(std::vector<std::string> lines_seperated);
 	void add_comment(std::vector<std::string> lines_seperated, std::string username);
 	void reply(std::string username, std::vector<std::string> lines_seperated);
 	void get_purchased(std::vector<std::string> lines_seperated, std::string username);
 	void get_notifications(std::string username);
 	void show_notifications_with_limit(std::string username, std::vector<std::string> lines_seperated);
 	void delete_comments(std::string username, std::vector<std::string> lines_seperated);
 	void edit_film(std::string username, std::vector<std::string> lines_seperated);
 	void find_signup_stats(std::vector<std::string> lines_seperated, std::string &username, std::string &password, std::string &email, int &age, int &is_publisher);
 	void find_film_stats(std::vector<std::string> lines_seperated, std::string &name, int &year, int &length, int &price, std::string &summary, std::string &director);
 	void added_film_notification(std::string username);
 	void set_film_changes(int film_id, int year, int length, int price, std::string film_name, std::string director, std::string summary);
 	void follow_notification(int _user_id, std::string username);
 	void show_all_films(std::vector<std::string>lines_seperated, std::string username, int max_year, int min_year, int price, int min_rate, std::string director, std::string film_name);
 	void recommend(std::string username, int film_id);
 	void show_purchased_without_filter(std::string username, std::vector<std::string> lines_seperated);
 	void show_purchased_with_filter(std::vector<std::string> lines_seperated, std::string username);
 	void filter_for_user(int max_year, int min_year, int price, int min_rate, std::string director, std::string film_name,int i);
 	void filter_for_publisher(int max_year, int min_year, int price, int min_rate, std::string director, std::string film_name,int i);
private:
	int user_id; 
	int film_id;
	int comment_id;
	int network_money;
	std::vector<Customer> customer;
	std::vector<Publisher> publisher;
	std::vector<User*> user;
	std::vector<Film> film;
};
#endif