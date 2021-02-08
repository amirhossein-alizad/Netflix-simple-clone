#include "Manager.h"
Manager::Manager() 
{
	user_id = 1;
	film_id = 1;
	comment_id = 1;
	network_money = 0;
	lines_of_matrix.push_back(0);
	matrix.push_back(lines_of_matrix);
}
Manager::~Manager()
{
	int how_many = user.size();
	for(int i = 0; i < how_many; i++)
		delete user[i];
	user.resize(0);
}
void Manager::hash(std::string &str) 
{ 
    int n = str.length(); 
    for (int i = 0; i < n; i++) 
    { 
          int count = 1; 
        while (i < n - 1 && str[i] == str[i + 1]) { 
            count++; 
            i++; 
        } 
    } 
} 
bool Manager::signup_exists(std::string username)
{
	for(int i = 0; i < user.size(); i++)
	{
		if(user[i]->get_RUP(USERNAME) == username)
			return true;
	}
	return false;
}
Response* Manager::signup(std::string &username, std::string &password, std::string email, int age, std::string is_publisher, int &status)
{
	Response* res = new Response();
	hash(password);
	if(signup_exists(username))
		status = EXISTS;
	else
	{
		if(is_publisher == "on")
		{
			User * new_user = new Publisher(PUBLISHER, email, username, password, age, user_id);
			user.push_back(new_user);
			publisher.push_back(Publisher(PUBLISHER, email, username, password, age, user_id));
		}
		else
		{
			User * new_user = new Customer(CUSTOMER, email, username, password, age, user_id);
			user.push_back(new_user);
			customer.push_back(Customer(CUSTOMER, email, username, password, age, user_id));
		}
		user_id++;
		status = DOES_NOT_EXIST;
	}
	return res;
}
Response* Manager::login(std::string &username, std::string &password, int &status, int &wrong)
{
	hash(password);
	Response* r = new Response();
	for(int i = 0; i < user.size(); i ++)
	{
		if(user[i]->get_RUP(USERNAME) == username && user[i]->get_RUP(PASSWORD) == password)
		{
			status = EXISTS;
			wrong = RIGHT;
			return r;
		}
		if(user[i]->get_RUP(USERNAME) == username && user[i]->get_RUP(PASSWORD) != password)
		{
			status = EXISTS;
			wrong = WRONG;
			return r;
		}
	}
	return r;
}
int Manager::return_publisher_id(std::string username)
{
	for(int i = 0; i < user.size(); i++)
		if(user[i]->get_RUP(USERNAME) == username)
			return user[i]->get_id();
}
void Manager::add_film(std::string username, std::string name, std::string director, std::string summary, int year, int length, int price)
{
	film.push_back(Film(price, length, name, director, summary, year, film_id, return_publisher_id(username)));
	for(int i = 0; i < publisher.size(); i ++)
	{
		if(publisher[i].return_username() == username)
			publisher[i].publishers_film(Film(price, length, name, director, summary, year, film_id, return_publisher_id(username)));
	}
	film_id++;
	if(film.size() > 1)
	{
		lines_of_matrix.push_back(0);
		for(int i = 0; i < matrix.size(); i++)
			matrix[i].push_back(0);
		matrix.push_back(lines_of_matrix);
	}
}
void Manager::delete_films(std::string username, int film_id)
{
	int _publisher_id = return_publisher_id(username);
	int index;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(PUBLISHER_ID) == _publisher_id && film[i].return_PLPYI(FILM_ID) == film_id)
		{
			index = i;
			film.erase(film.begin() + i);
			break;
		}
	}
	for( int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_username() == username)
		{
			for(int j = 0; j < publisher[i].films_published.size(); j++)
			{
				if(publisher[i].films_published[j].return_PLPYI(FILM_ID) == film_id)
				{
					publisher[i].films_published.erase(publisher[i].films_published.begin() + j);
					break;
				}
			}
		}
	}	
	for(int i = 0; i < matrix.size(); i++)
		matrix[i].erase(matrix[i].begin() + index);
	matrix.erase(matrix.begin() + index);
	lines_of_matrix.erase(lines_of_matrix.begin());
}
void Manager::post_money(int amount, std::string username)
{
	if(user_is_publisher(username))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == username)
				publisher[i].add_money(amount);
		}
	}
	else
	{
		for(int i = 0; i < user.size(); i++)
		{
			if(user[i]->get_RUP(USERNAME) == username)
				user[i]->add_money(amount);
		}
	}
}
void Manager::recommend(std::string username, int film_id, std::string &body)
{
	std::vector<Film> films_copy;
	int index;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
			index = i;
	}
	std::vector<int> copy_of_int = matrix[index];
	int new_index;
	sort(copy_of_int.begin(), copy_of_int.end());
	int status[copy_of_int.size()] = { -1 };
	for(int i = copy_of_int.size() - 1; i >= 0; i--)
	{
		for(int j = 0; j < matrix[index].size(); j++)
		{
			if(copy_of_int[i] == matrix[index][j] && status[j] != 1)
			{
				new_index = j;
				status[j] = 1;
				films_copy.push_back(film[new_index]);
				break;
			}
		}
	}
	search_for_reccommend(films_copy, username, body, film_id);
}
bool Manager::user_is_publisher(std::string username)
{
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_username() == username)
			return true;
	}
	return false;
}
void Manager::send_money_to_publisher(int film_id, std::string username)
{
	float film_rate = 0;
	int publisher_id;
	int film_price;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			film_rate = film[i].get_rate();
			publisher_id = film[i].return_PLPYI(PUBLISHER_ID);
			film_price = film[i].return_PLPYI(PRICE);
		}
	}
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher_id == publisher[i].return_id())
		{
			network_money += publisher[i].get_money(film_price, film_rate);
			network_money += publisher[i].not_sent_cash();
			publisher[i].set_new_money();
			break;
		}
	}
}
void Manager::buy_for_user(std::string username, int &publisher_id, int film_id)
{
	if(!user_is_publisher(username))
	{
		for(int i = 0; i < film.size(); i++)
			if(film[i].return_PLPYI(FILM_ID) == film_id)
				for(int j = 0; j < user.size(); j++)
					if(user[j]->get_RUP(USERNAME) == username)
					{	
						user[j]->buy_a_film(film[i], film[i].return_PLPYI(PRICE));
						publisher_id = film[j].return_PLPYI(PUBLISHER_ID);
						break;
					}
	}
	else
	{
		for(int i = 0; i < film.size(); i++)
			if(film[i].return_PLPYI(FILM_ID) == film_id)
				for(int j = 0; j < publisher.size(); j++)
					if(publisher[j].return_username() == username)
					{
						publisher[j].buy_a_film(film[i], film[i].return_PLPYI(PRICE));
						publisher_id = film[j].return_PLPYI(PUBLISHER_ID);
						break;
					}
	}
}
void Manager::buy(std::string username, int film_id)
{
	int publisher_id;
	buy_for_user(username, publisher_id, film_id);
	send_money_to_publisher(film_id, username);
	int index;
	for(int i= 0; i < film.size(); i++)
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			index = i;
			break;
		}
	change_matrix_elements(film_id, index, username);
}
bool Manager::check_if_bought(std::string username, int film_id)
{
	if(user_is_publisher(username))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == username)
			{
				if(publisher[i].has_bought_film(film_id))
					return true;
			}
		}
	}
	else
	{
		for(int i = 0; i < user.size(); i++)
		{
			if(user[i]->get_RUP(USERNAME) == username)
			{
				if(user[i]->has_bought_film(film_id))
					return true;
			}
		}
	}
	return false;
}
void Manager::rate(int film_id, int rate)
{
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI("film_id") == film_id)
		{
			film[i].new_rate(rate);						
			break;
		}
	}
	for(int i = 0; i < user.size(); i++)
	{
		if(user[i]->has_bought_film(film_id))
			user[i]->change_rate(rate, film_id);
	}
	
	for(int i = 0; i < publisher.size(); i++)
		publisher[i].change_rate(rate , film_id);
}
void Manager::add_comment(std::string comment, int film_id, std::string username)
{
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			film[i].add_comment(comment, comment_id, username);
			break;
		}
	}
}
void Manager::change_matrix_elements(int film_id, int index, std::string username)
{
	if(user_is_publisher(username))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == username)
			{
				for(int j = 0; j < publisher[i].films_bought.size(); j++)
				{
					for(int k = 0; k < film.size(); k++)
					{
						if(publisher[i].films_bought[j].return_PLPYI(FILM_ID) == film[k].return_PLPYI(FILM_ID) && film[k].return_PLPYI(FILM_ID) != film_id)
						{
							matrix[index][k]++;
							matrix[k][index]++;
						}
					}
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < user.size(); i++)
		{
			if(user[i]->get_RUP(USERNAME) == username)
			{
				for(int j = 0; j < film.size(); j++)
				{
					if(user[i]->has_bought_film(film[j].return_PLPYI(FILM_ID)) && film[j].return_PLPYI(FILM_ID) != film_id)
					{
						matrix[index][j]++;
						matrix[j][index]++;
					}
				}
			}
		}
	}
}
void Manager::search_for_reccommend(std::vector<Film> films_copy, std::string username, std::string &body, int film_id)
{
	int line_counter = 0;
	int counter = 0;
	body += "RECOMMENDED FILMS<br><br>";
	for(int i = 0; i < films_copy.size(); i++)
	{
		if(counter == 4)
			break;
		if(user_is_publisher(username))
		{
			for(int j = 0; j < publisher.size(); j++)
			{
				if(publisher[j].return_username() == username)
				{
					if(!publisher[j].has_bought_film(films_copy[i].return_PLPYI(FILM_ID)) && films_copy[i].return_PLPYI(FILM_ID) != film_id)
					{
						body += std::to_string(line_counter + 1);
						body +="<br>";
						body += "film name : ";
						body += films_copy[i].return_NDS(NAME);
						body += "<br>length : ";
						body += std::to_string(films_copy[i].return_PLPYI(LENGTH));
						body += "<br>director : ";
						body += films_copy[i].return_NDS(DIRECTOR);
						body += "<br><br>";
						line_counter++;
						break;
					}
					else 
						break;
				}
			}
		}
		else
		{
			for(int j = 0; j < user.size(); j++)
			{
				if(user[j]->get_RUP(USERNAME) == username)
				{
					if(!publisher[j].has_bought_film(films_copy[i].return_PLPYI(FILM_ID)) && films_copy[i].return_PLPYI(FILM_ID) != film_id)
					{
						body += std::to_string(line_counter + 1);
						body +="<br>";
						body += "film name : ";
						body += films_copy[i].return_NDS(NAME);
						body += "<br>length : ";
						body += std::to_string(films_copy[i].return_PLPYI(LENGTH));
						body += "<br>director : ";
						body += films_copy[i].return_NDS(DIRECTOR);
						body += "<br>";
						line_counter++;
						break;
					}
					else 
						break;
				}
			}
		}
		counter++;
	}
}