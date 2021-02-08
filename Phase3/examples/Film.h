#ifndef FILMS_H
#define FILMS_H
#include <string>
#include <vector>
#include "Comment.h"
#define ZERO 0
#define NAME "name"
#define DIRECTOR "director"
#define FILM_ID "film_id"
#define SUMMARY "summary"
#define PUBLISHER_ID "publisher_id"
#define YEAR "year"
#define PRICE "price"
#define LENGTH "length"
class Film
{
public:
	Film(int _price, int _length, std::string _name, std::string _director, std::string _summary, int _year, int _film_id, int _publisher_id)
	: price(_price), length(_length), name(_name), director(_director), summary(_summary), year(_year), film_id(_film_id), publisher_id(_publisher_id) 
	{
		how_many_rated = ZERO;
		rate = ZERO;
		flag = 0;
	}
	int flag;
	void new_rate(int newrate);
	void add_comment(std::string new_comment, int id, std::string username);
	std::string return_NDS(std::string _name);
	int return_PLPYI(std::string);
	void set_year(int _year){ year = _year; }
	void set_price(int _price){ price = _price; }
	void set_length(int _length){ length = _length; }
	void set_name(std::string _name){ name = _name; }
	void set_director(std::string _director){ director = _director; }
	void set_summary(std::string _summary){ summary = _summary; }
	double get_rate(){ return rate; } 
	std::vector<Comment> comments;
private:
	double rate;
	int price;
	int length;
	int publisher_id;
	int year;
	int film_id;
	int how_many_rated;
	std::string name;
	std::string director;
	std::string summary;
};
#endif