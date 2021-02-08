#ifndef MANAGER_H
#define MANAGER_H

#define DOES_NOT_EXIST 0
#define EXISTS 1
#define WRONG 0
#define RIGHT 1
#define HAS_BOUGHT 1
#define HAS_NOT_BOUGHT 0
#define USERNAME "username"
#define PASSWORD "password"
#define PUBLISHER "publisher"
#define CUSTOMER "customer"
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
#define ADMIN "admin"

#include "Publisher.h"
#include "Exception.h"
#include "Admin.h"
#include "../utils/response.hpp"
#include <iostream>
#include <string>	
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>
#include <algorithm>

class Manager
{
public:
	Manager();
	~Manager();
	std::vector<User*> user;
	void hash(std::string &str);
	void set_online_user(std::string  username){ online_user = username; }
	std::string get_online_user(){ return online_user; }
	void change_matrix_elements(int film_id, int index, std::string username);
	bool signup_exists(std::string username);
	Response* signup(std::string &username, std::string &password, std::string email, int age, std::string is_publisher, int &status);
	Response* login(std::string &username, std::string &password, int &status, int &wrong);
	int return_publisher_id(std::string username);
	void add_film(std::string username, std::string name, std::string director, std::string summary, int year, int length, int price);
	void buy_for_user(std::string username, int &publisher_id, int film_id);
	bool check_if_bought(std::string username, int film_id);
 	void delete_films(std::string username, int film_id);
 	void post_money(int amount, std::string username);
 	void get_film_info(std::string username, std::vector<std::string> lines_seperated, int & repeatition);
 	bool user_is_publisher(std::string username);
 	void send_money_to_publisher(int film_id, std::string username);
 	void buy(std::string username, int film_id);
 	void rate(int film_id, int rate);
 	void add_comment(std::string comment, int film_id, std::string username);
 	double round(double var) { double value = (int)(var * 100 + .5); return (double)value / 100; }
 	void recommend(std::string username, int film_id, std::string &body);
 	void search_for_reccommend(std::vector<Film> films_copy, std::string username, std::string &body, int film_id);
	std::vector<Publisher> publisher;
	std::vector<Film> film;
private:
	int user_id; 
	int film_id;
	int comment_id;
	double network_money;
	std::string online_user;
	std::vector<std::vector<int>> matrix;
	std::vector<int> lines_of_matrix;
	std::vector<Customer> customer;
};
#endif