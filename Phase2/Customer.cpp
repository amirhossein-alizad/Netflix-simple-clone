#include "Customer.h"
int Customer::how_many_films_bought() const
{
	return films_bought.size();
}
void Customer::show_followers() const
{}
bool Customer::is_flag_one(int film_id)
{
	for(int i = 0; i < films_bought.size(); i++)
		if(films_bought[i].return_PLPYI(FILM_ID) == film_id && films_bought[i].flag == 1)
			return true;
	return false;
}
void Customer::put_flag_one(int film_id)
{
	for(int i = 0; i < films_bought.size(); i++)
		if(films_bought[i].return_PLPYI(FILM_ID) == film_id)
			films_bought[i].flag = 1;
}
std::string Customer::get_email() const
{
	return email;
}
void Customer::add_money(int amount)
{
	cash += amount;
}
bool Customer::has_bought_film(int film_id) 
{
	for(int i = 0; i < films_bought.size(); i++)
	{
		if(films_bought[i].return_PLPYI(FILM_ID) == film_id)
			return true;
	}
	return false;
}
void Customer::buy_a_film(Film new_film, int price)
{
	if (cash < price)
		throw Permission_Denied();
	cash -= price;
	films_bought.push_back(new_film);
}
void Customer::change_rate(int newrate, int film_id)
{
	for(int i = 0; i < films_bought.size(); i++)
	{
		if(film_id == films_bought[i].return_PLPYI(FILM_ID))
			films_bought[i].new_rate(newrate);
	}
}
void Customer::show_films_bought(std::vector<std::string> lines_seperated, int min_year, int max_year, int min_rate, int price, std::string film_name, std::string director)
{
	for(int j = 0; j < films_bought.size(); j++)
	{		
		int print_status = NOT_TO_PRINT;
		if(lines_seperated.size() > WHERE_QUESTION_MARK_IS)
		{
			if(max_year != NOT_VALUATED || min_year != NOT_VALUATED || price != NOT_VALUATED || min_rate != NOT_VALUATED || director != "" || film_name != "")
			{
				int counter = ZERO ;	
				if(max_year != NOT_VALUATED || min_year != NOT_VALUATED)
				{
					if(max_year != NOT_VALUATED && min_year == NOT_VALUATED && films_bought[j].return_PLPYI(YEAR) <= max_year)
						print_status = PRINT;
					else if (max_year == NOT_VALUATED && min_year != NOT_VALUATED && films_bought[j].return_PLPYI(YEAR) >= max_year)
						print_status = PRINT;
					else if (max_year != NOT_VALUATED && min_year != NOT_VALUATED && films_bought[j].return_PLPYI(YEAR) >= min_year 
						&& films_bought[j].return_PLPYI(YEAR) <= max_year)
						print_status = PRINT;
					else 
						continue;
				}
				else if(price != NOT_VALUATED)
				{
					if(films_bought[j].return_PLPYI(PRICE) <= price)
						print_status = PRINT;
					else 
						continue;
				}
				else if(min_rate != NOT_VALUATED)
				{
					if(films_bought[j].return_PLPYI(RATE) >= min_rate)
						print_status = PRINT;
					else 
						continue;
				}
				else if(director != "")
				{
					if(films_bought[j].return_NDS(DIRECTOR) == director)
						print_status = PRINT;
					else 
						continue;
				}
				else if(film_name != "")
				{
					if(films_bought[j].return_NDS(NAME) == film_name)
						print_status = PRINT;
					else 
						continue;
				}
				if(print_status == NOT_TO_PRINT)
					continue;
				else
					print_film(counter, films_bought, j);
			}
			else
			{	
				print_film(j, films_bought, j);
				j--;
			}
		}
		else
		{	
			print_film(j, films_bought, j);
			j--;
		}
	}
}
void Customer::print_film(int &counter, std::vector<Film> films_bought, int j)
{
	std::cout<< counter + 1<<DOT<<films_bought[j].return_PLPYI(FILM_ID)<<SEPERATOR<<films_bought[j].return_NDS(NAME);
	std::cout<<SEPERATOR<<films_bought[j].return_PLPYI(LENGTH)<<SEPERATOR<<films_bought[j].return_PLPYI(PRICE);
	std::cout<<SEPERATOR<<films_bought[j].return_PLPYI(RATE)<<SEPERATOR<<films_bought[j].return_PLPYI(YEAR);
	std::cout<<SEPERATOR<<films_bought[j].return_NDS(DIRECTOR)<<std::endl;
	counter++;
}
void Customer::show_notifications()
{
	int how_many = unread_notifications.size();
	for(int i = 0; i < how_many; i++)
		std::cout<<i + 1<<DOT<<unread_notifications[i]<<std::endl;
	for(int i = 0; i < how_many; i++)
		unread_notifications.erase(unread_notifications.begin());
}
void Customer::show_notifications_limited(int limit)
{
	int counter = 1;
	if(limit > notifications.size())
		throw Bad_Request();
	for(int i = notifications.size() - 1; i < notifications.size() - limit; i--)
	{
		std::cout<<counter<<DOT<<notifications[i]<<std::endl;
		counter++;
	}
}