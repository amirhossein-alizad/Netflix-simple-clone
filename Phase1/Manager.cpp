#include "Manager.h"
Manager::Manager() 
{
	user_id = 1;
	film_id = 1;
	comment_id = 1;
	network_money = 0;
}
bool Manager::is_email_valid(const std::string& email)
{
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return std::regex_match(email, pattern);
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
Manager::~Manager()
{
	int how_many = user.size();
	for(int i = 0; i < how_many; i++)
		delete user[i];
	user.resize(0);
}
void Manager::run()
{
	int film_id;
	int publisher_id;
	int customer_id;
	std::string input;
	std::vector<std::string> lines_seperated;
	std::string username = "";
	std::string password = "";
	std::string email = "";
	int age = -1;
	while(std::getline(std::cin, input))
	{
		try
		{
			lines_seperated = seperate_lines(input);
			if(lines_seperated.size() > 0)
			{
				if(lines_seperated[FIRST_ELEMENT] == POST && lines_seperated.size() >= 2)
				{
					if(lines_seperated[SECOND_ELEMENT] == SIGNUP && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						signup(username, password, email, age, lines_seperated);
					else if(lines_seperated[SECOND_ELEMENT] == LOGIN && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						login(username, password, lines_seperated);
					else if(lines_seperated[SECOND_ELEMENT] == FILMS && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						add_film(username, lines_seperated);
					else if(lines_seperated[SECOND_ELEMENT] == FOLLOWERS && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						follow(lines_seperated, username);
					else if(lines_seperated[SECOND_ELEMENT] == MONEY)
						post_money(lines_seperated, username); 
					else if(lines_seperated[SECOND_ELEMENT] == BUY && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						buy(username, lines_seperated);
					else if(lines_seperated[SECOND_ELEMENT] == MONEY && lines_seperated.size() == THIRD_ELEMENT)
						add_money_to_publisher(username);
					else if(lines_seperated[SECOND_ELEMENT] == RATE && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						rate(username, lines_seperated);
					else if(lines_seperated[SECOND_ELEMENT] == COMMENTS && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						add_comment(lines_seperated, username);
					else if(lines_seperated[SECOND_ELEMENT] == REPLIES && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						reply(username, lines_seperated);
					else
						throw Bad_Request();
				}
				else if(lines_seperated[FIRST_ELEMENT] == POST && lines_seperated.size() < 2)
					throw Bad_Request();
				else if(lines_seperated[FIRST_ELEMENT] == PUT && lines_seperated.size() > 3)
				{
					if(lines_seperated[SECOND_ELEMENT] == FILMS && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						edit_film(username, lines_seperated);	
					else
						throw Bad_Request();
				}
				else if(lines_seperated[FIRST_ELEMENT] == PUT && lines_seperated.size() < 3)
					throw Bad_Request();
				else if(lines_seperated[FIRST_ELEMENT] == DELETE && lines_seperated.size() > 3)
				{
					if(lines_seperated[SECOND_ELEMENT] == FILMS && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						delete_films(username, lines_seperated);
					else if(lines_seperated[SECOND_ELEMENT] == COMMENTS && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						delete_comments(username, lines_seperated);
					else
						throw Bad_Request();
				}
				else if(lines_seperated[FIRST_ELEMENT] == DELETE && lines_seperated.size() < 3)
					throw Bad_Request();
				else if(lines_seperated[FIRST_ELEMENT] == GET)
				{
					int repeatition = REPEAT;
					if(lines_seperated[SECOND_ELEMENT] == FOLLOWERS)
						get_followers(username);
					else if((lines_seperated[SECOND_ELEMENT] == PUBLISHED && lines_seperated.size() == 2)  
						|| (lines_seperated[SECOND_ELEMENT] == PUBLISHED && lines_seperated.size() > 2 && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK))
						show_films(lines_seperated, username);
					else if(lines_seperated[SECOND_ELEMENT] == FILMS &&  lines_seperated.size() > 2 && lines_seperated[FOURTH_ELEMENT] == FILM_ID && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK)
						get_film_info(username, lines_seperated, repeatition);
					else if((lines_seperated[SECOND_ELEMENT] == PURCHASED && lines_seperated.size() <= 2) 
						|| (lines_seperated[SECOND_ELEMENT] == PURCHASED && lines_seperated.size() > 2 && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK))
						get_purchased(lines_seperated, username);
					else if((lines_seperated[SECOND_ELEMENT] == FILMS && lines_seperated.size() <= 2) 
						|| (lines_seperated[SECOND_ELEMENT] == FILMS && lines_seperated.size() > 2 && lines_seperated[THIRD_ELEMENT] == QUESTION_MARK))
						search_films(username, lines_seperated, repeatition);
					else if(lines_seperated[SECOND_ELEMENT] == NOTIFICATIONS && lines_seperated.size() == 2)
						get_notifications(username);
					else if(lines_seperated[SECOND_ELEMENT] == NOTIFICATIONS && lines_seperated.size() > 2 && lines_seperated [THIRD_ELEMENT] == READ 
						&& lines_seperated[FOURTH_ELEMENT] == QUESTION_MARK)
						show_notifications_with_limit(username, lines_seperated);
					else
						throw Bad_Request();
				}
				else if(lines_seperated[FIRST_ELEMENT] == GET && lines_seperated.size() < 2)
					throw Bad_Request();  
				else if(lines_seperated[FIRST_ELEMENT][FIRST_ELEMENT] == '\0')
					continue;
				else
					throw Not_Found();
			}
		}catch(std::exception &ex){
			std::cout<< ex.what() << std::endl;
		}
	}
}

std::vector<std::string> Manager::seperate_lines(std::string line)
{
	std::string temp = "";
	std::vector<std::string> strings;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != ' ')
		{
			temp += line[i];
			if (line[i + 1] == ' ' && i < line.length() - 1)
			{
				strings.push_back(temp);
				temp = "";
			}
		}
	}
	strings.push_back(temp);
	return strings;
}
bool Manager::check_if_has_char(std::string input)
{
	for(int i = 0; i < input.length(); i++)
	{
		if(isalpha(input[i]))
			return true;
	}
	return false;
}
bool Manager::signup_exists(std::vector<std::string> lines_seperated, int username_index)
{
	for(int i = 0; i < user.size(); i++)
	{
		if(user[i]->get_RUP(USERNAME) == lines_seperated[username_index])
			return true;
	}
	return false;
}
void Manager::signup(std::string &username, std::string &password, std::string email, int &age, std::vector<std::string> lines_seperated)
{
	int is_publisher = NOT_PUBLISHER;
	find_signup_stats(lines_seperated, username, password, email, age, is_publisher);
	if(username == "" || password == "" || email == "" || age == -1 || age <= 0)
		throw Bad_Request();
	hash(password);
	if(is_publisher == IS_PUBLISHER)
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
	std::cout << OK << std::endl;
}

void Manager::find_username_and_password(std::string & _username, std::string &_password, std::vector<std::string> lines_seperated)
{
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i += 2)
	{
		if(lines_seperated[i] == USERNAME && i != lines_seperated.size() - 1)
			_username = lines_seperated[i + 1];
		else if(lines_seperated[i] == PASSWORD && i != lines_seperated.size() - 1)
			_password = lines_seperated[i + 1];
	}
	if(_username ==  "" || _password == "")
		throw Bad_Request();
	int existence = DOES_NOT_EXIST;
	for(int i = 0; i < user.size() ; i++)
	{
		if(user[i]->get_RUP(USERNAME) == _username)
		{
			existence = EXISTS;
			break;
		}
	}
	if(existence == DOES_NOT_EXIST)
		throw Bad_Request();
}
void Manager::login(std::string &username, std::string &password, std::vector<std::string> lines_seperated)
{
	std::string _username = "";
	std::string _password = "";
	find_username_and_password(_username, _password, lines_seperated);
	hash(_password);
	for(int i = 0; i < user.size(); i ++)
	{
		if(user[i]->get_RUP(USERNAME) == _username && user[i]->get_RUP(PASSWORD) == _password)
		{
			username = _username;
			password = _password;
			std::cout << OK << std::endl; 
		}
		if(user[i]->get_RUP(USERNAME) == _username && user[i]->get_RUP(PASSWORD) != _password)
			throw Bad_Request();
	}
}
void Manager::check_if_user_is_publisher(std::string username)
{
	if(username == "")
		throw Permission_Denied();
	for(int i = 0; i < user.size();i++)
	{
		if(user[i]->get_RUP(USERNAME) == username)
			if(user[i]->get_RUP(ROLE) == CUSTOMER)
				throw Permission_Denied();
	}
}
int Manager::return_publisher_id(std::string username)
{
	for(int i = 0; i < user.size(); i++)
		if(user[i]->get_RUP(USERNAME) == username)
			return user[i]->get_id();
}
void Manager::add_film(std::string username, std::vector<std::string> lines_seperated)
{
	check_if_user_is_publisher(username);
	std::string name = "";
	int year = -1;
	int length = -1;
	int price = -1;
	std::string summary = "";
	std::string director = "";
	find_film_stats(lines_seperated, name, year, length, price, summary, director);
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_NDS(NAME) == name)
			throw Bad_Request();
	}
	if(name == "" || summary == "" || director == "" || year <= 0 || length <= 0 || price <= 0)
		throw Bad_Request();
	film.push_back(Film(price, length, name, director, summary, year, film_id, return_publisher_id(username)));
	for(int i = 0; i < publisher.size(); i ++)
	{
		if(publisher[i].return_username() == username)
			publisher[i].publishers_film(Film(price, length, name, director, summary, year, film_id, return_publisher_id(username)));
	}
	film_id++;
	added_film_notification(username);
	std::cout << OK << std::endl;
}
int Manager::find_film_id(std::vector<std::string> lines_seperated)
{
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i++)
	{
		if(lines_seperated[i] == FILM_ID && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			return std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == FILM_ID && i == lines_seperated.size() - 1)
			throw Bad_Request();
	}
}
void Manager::edit_film_for_every_one(std::string username, std::vector<std::string> lines_seperated, int &year, int &length, int &price, std::string &film_name,
 std::string &director, std::string &summary, int film_id)
{
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			if(return_publisher_id(username) != film[i].return_PLPYI(PUBLISHER_ID))
				throw Permission_Denied();
		}
	}
	for (int i = START_OF_ACTION + 2 ; i < lines_seperated.size(); i += 2)
	{
		if(lines_seperated[i] == YEAR && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			year = std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == LENGTH && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			length = std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == PRICE && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			price = std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == NAME && i != lines_seperated.size() - 1)
			film_name = lines_seperated[i + 1];
		else if(lines_seperated[i] == DIRECTOR && i != lines_seperated.size() - 1)
			director = lines_seperated[i + 1];
		else if(lines_seperated[i] == SUMMARY && i != lines_seperated.size() - 1)
			summary = lines_seperated[i + 1];
		else 
			throw Bad_Request();
	}		
	set_film_changes(film_id, year, length, price, film_name, director, summary);
}
void Manager::edit_film_for_publisher(std::string username, int film_id, int year, int length, int price, std::string film_name, std::string director, std::string summary)
{
	for(int i = 0; i < publisher.size(); i++)
	{
		if (username == publisher[i].return_username())
		{
			for(int j = 0; j < publisher[i].films_published.size(); j ++)
			{
				if(film_id == publisher[i].films_published[j].return_PLPYI(FILM_ID))
				{
					if(year != -1)
						publisher[i].films_published[j].set_year(year);
					if(length != -1)
						publisher[i].films_published[j].set_length(length);
					if(price != -1)
						publisher[i].films_published[j].set_price(price);
					if(film_name != "")
						publisher[i].films_published[j].set_name(film_name);
					if(director != "")
						publisher[i].films_published[j].set_director(director);
					if(summary != "")
						publisher[i].films_published[j].set_summary(summary);
					break;
				}
			}
		}
	}
}
void Manager::delete_films(std::string username, std::vector<std::string> lines_seperated)
{
	check_if_user_is_publisher(username);
	int film_id = find_film_id(lines_seperated);
	int _publisher_id = return_publisher_id(username);
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(PUBLISHER_ID) == _publisher_id && film[i].return_PLPYI(FILM_ID) == film_id)
		{
			film.erase(film.begin() + i);
			break;
		}
		else if(film[i].return_PLPYI(PUBLISHER_ID) != _publisher_id && film[i].return_PLPYI(FILM_ID) == film_id)
			throw Permission_Denied();
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
	std::cout<<OK<<std::endl;
}
int Manager::find_user_id(std::vector<std::string> lines_seperated)
{
	std::string _user_id;
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i++)
	{
		if(lines_seperated[i] == USER_ID && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			_user_id = lines_seperated[i + 1];
			break;
		}
		if(lines_seperated[i] == USER_ID && i == lines_seperated.size() - 1)
			throw Bad_Request();
	}
	for(int i = 0; i < _user_id.length(); i++)
	{
		char c = _user_id[i];
		if((int) c < 48 || (int) c > 57 )
			throw Bad_Request();
	}
	return std::stoi(_user_id);
}
void Manager::follow(std::vector<std::string> lines_seperated, std::string username)
{
	int _user_id = -1;
	_user_id = find_user_id(lines_seperated);
	if(_user_id < 1)
		throw Bad_Request();
	if (username == "")
		throw Permission_Denied();
	follow_notification(_user_id, username);
	std::cout << OK << std::endl;
}
void Manager::get_followers(std::string username)
{
	check_if_user_is_publisher(username);
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_username() == username)
		{
			std::cout<<"List of Followers"<<std::endl;
			std::cout << "#. User Id | User Username | User Email" << std::endl;
			for(int j = 0; j < publisher[i].how_many_followers(); j++)
				publisher[i].show_followers();
		}
	}
}
int Manager::how_many_published(std::string username)
{
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_username() == username)
			return publisher[i].films_published.size();
	}
}
void Manager::print_film(int &counter, std::vector<Film> films_published, int j)
{
	std::cout<< counter + 1<<DOT<<films_published[j].return_PLPYI(FILM_ID)<<SEPERATOR<<films_published[j].return_NDS(NAME);
	std::cout<<SEPERATOR<<films_published[j].return_PLPYI(LENGTH)<<SEPERATOR<<films_published[j].return_PLPYI(PRICE);
	std::cout<<SEPERATOR<<films_published[j].return_PLPYI(RATE)<<SEPERATOR<<films_published[j].return_PLPYI(YEAR);
	std::cout<<SEPERATOR<<films_published[j].return_NDS(DIRECTOR)<<std::endl;
	counter++;
}
void Manager::show_films(std::vector<std::string> lines_seperated, std::string username)
{
	int min_rate = -1, min_year = -1, price = -1, max_year = -1;
	std::string director = "";
	std::string film_name = "";
	int is_published[how_many_published(username)] = { -1 };
	check_if_user_is_publisher(username);
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i++)
	{
		if(lines_seperated[i] == MAX_YEAR && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			max_year = std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == PRICE && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			price = std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == NAME && i != lines_seperated.size() - 1)
			film_name = lines_seperated[i + 1];
		else if(lines_seperated[i] == DIRECTOR && i != lines_seperated.size() - 1)
			director = lines_seperated[i + 1];
		else if(lines_seperated[i] == MIN_YEAR && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			min_year = std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == MIN_RATE && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			min_rate = std::stoi(lines_seperated[i + 1]);
		}
	}
	if(max_year < -1 || min_year < -1 || price < -1 || min_rate < -1)
		throw Bad_Request();
	show_all_films(lines_seperated, username, max_year, min_year, price, min_rate, director, film_name);
}
void Manager::post_money(std::vector<std::string> lines_seperated, std::string username)
{
	int amount;
	if(username == "")
		throw Permission_Denied();
	if(lines_seperated.size() > 2)
	{
		for(int i = START_OF_ACTION; i < lines_seperated.size(); i += 2)
		{
			if(lines_seperated[i] == AMOUNT && i != lines_seperated.size() - 1)
			{
				if(check_if_has_char(lines_seperated[i + 1]))
					throw Bad_Request();
				amount = std::stoi(lines_seperated[i + 1]);
			}
		}
		if(amount <= 0)
			throw Bad_Request();
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
	else
	{
		for(int i = 0; i < publisher.size(); i++)
			{
				if(publisher[i].return_username() == username)
					publisher[i].set_new_money();
			}
	}
	std::cout<<OK<<std::endl;
}
void Manager::recommend(std::string username, int film_id)
{
	std::cout<<"Recommendation Film"<<std::endl;
	std::cout<<"#. Film Id | Film Name | Film Length | Film Director"<<std::endl;  
	std::vector<Film> films_copy;
	for(int j = 0; j < film.size(); j++)
		films_copy.push_back(film[j]);
	int counter = 0;
	while(true)
	{
		for(int j = 0; j < user.size(); j++)
		{
			if(user[j]->get_RUP(USERNAME) == username)
			{
				for(int k = 0; k < films_copy.size(); k++)
				{
					if(films_copy[k].return_PLPYI(FILM_ID) == film_id)
					{
						films_copy.erase(films_copy.begin() + k);
						continue;	
					}
					if(!user[j]->has_bought_film(films_copy[k].return_PLPYI(FILM_ID)))
					{
						int highest_rate = 0;
						int index = 0;
						for(int l = 0; l < films_copy.size(); l++)
						{
							if(films_copy[l].return_PLPYI(RATE) > highest_rate)
							{
								index = l;
								highest_rate = films_copy[l].return_PLPYI(RATE);
							}
						}
						std::cout<<counter + 1 <<". "<< films_copy[index].return_PLPYI(FILM_ID) << SEPERATOR<<films_copy[index].return_NDS(NAME);
						std::cout<<SEPERATOR<<films_copy[index].return_PLPYI(LENGTH)<<SEPERATOR<<films_copy[index].return_NDS(DIRECTOR)<<std::endl;
						counter++;
						films_copy.erase(films_copy.begin() + index);
					}
					else
						films_copy.erase(films_copy.begin() + k);
					if(counter >= 4)
						break;
					if(films_copy.size() == 0)
						break;
				}		
			}
			if(counter >= 4)
				break;
			if(films_copy.size() == 0)
				break;
		}
		if(counter >= 4)
			break;
		if(films_copy.size() == 0)
			break;
	}
}
void Manager::get_film_info(std::string username, std::vector<std::string> lines_seperated, int & repeatition)
{
	if(username == "")
		throw Permission_Denied();
	int film_id = find_film_id(lines_seperated);
	int status = DOES_NOT_EXIST;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			status = EXISTS;
			std::cout<<"Details of Film "<<film[i].return_NDS(NAME)<<std::endl<<"Id = "<<film_id<<std::endl<<"Director = "<<film[i].return_NDS(DIRECTOR)<<std::endl;
			std::cout<<"Length = "<<film[i].return_PLPYI(LENGTH)<<std::endl<<"Year = "<<film[i].return_PLPYI(YEAR)<<std::endl;
			std::cout<<"Summary = "<<film[i].return_NDS(SUMMARY)<<std::endl<<"Rate = "<<film[i].return_PLPYI(RATE)<<std::endl;
			std::cout<<"Price = "<<film[i].return_PLPYI(PRICE)<<std::endl<<std::endl<<"Comments"<<std::endl;
			for(int j = 0; j < film[i].comments.size(); j++)
			{
				std::cout<<film[i].comments[j].return_cm_id()<<". "<<film[i].comments[j].show_comment()<<std::endl;
				film[i].comments[j].show_reply();
			}
			std::cout<<std::endl;
		}
	}
	if(status == DOES_NOT_EXIST)
		throw Not_Found();
	recommend(username, film_id);
	repeatition = NOT_TO_REPEAT;
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
void Manager::send_money_to_publisher(int film_id, std::string username, std::string notification)
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
			network_money += publisher[i].get_money(film_price, film_rate);
	}
}
int Manager::find_id(std::string username)
{
	if(user_is_publisher(username))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == username)
				return publisher[i].return_id();
		}
	}
	else
	{
		for(int i = 0; i < user.size(); i++)
		{
			if(user[i]->get_RUP(USERNAME) == username)
				return user[i]->get_id();
		}
	}
}
std::string Manager::find_film_name(int film_id)
{
	for(int i = 0; i < film.size(); i++)
		if(film[i].return_PLPYI(FILM_ID) == film_id)
			return film[i].return_NDS(NAME);
}
void Manager::buy_for_user(std::string username, int &publisher_id, int film_id)
{
	if(!user_is_publisher(username))
	{
		for(int i = 0; i < user.size(); i++)
			if(user[i]->get_RUP(USERNAME) == username)
				if(user[i]->has_bought_film(film_id))
					throw Bad_Request();
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
		for(int i = 0; i < publisher.size(); i++)
			if(publisher[i].return_username() == username)
				if(publisher[i].has_bought_film(film_id))
					throw Bad_Request();
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
std::string Manager::add_notification_for_buying(int publisher_id, std::string username, int film_id)
{
	std::string notification = "User ";
	notification += username;
	notification += " with id ";
	notification += std::to_string(find_id(username));
	notification += " buy your film ";
	notification += find_film_name(film_id);
	notification += " with id ";
	notification += std::to_string(film_id);
	notification += ".";
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_id() == publisher_id)
			publisher[i].add_notification(notification);
	}
	return notification;
}
void Manager::buy(std::string username, std::vector<std::string> lines_seperated)
{
	int publisher_id;
	int film_id = find_film_id(lines_seperated);
	buy_for_user(username, publisher_id, film_id);
	std::string notification = add_notification_for_buying(publisher_id, username, film_id);
	send_money_to_publisher(film_id, username, notification);
	std::cout<<OK<<std::endl;
}
void Manager::add_money_to_publisher(std::string username)
{
	check_if_user_is_publisher(username);
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_username() == username)
			publisher[i].set_new_money();
	}
	std::cout<<OK<<std::endl;
}
void Manager::add_notification_for_rate(std::string username, int film_id, int publisher_id)
{
	std::string notification ="User ";
	notification += username;
	notification += " with id ";
	notification += std::to_string(find_id(username));
	notification += " rate your film ";
	notification += find_film_name(film_id);
	notification += " with id ";
	notification += std::to_string(film_id);
	notification += ".";
	for(int i = 0; i < publisher.size(); i++)
		if(publisher[i].return_id() == publisher_id)
			publisher[i].add_notification(notification);
}
void Manager::check_if_bought(std::string username, int film_id)
{
	int has_bought = HAS_NOT_BOUGHT;
	if(user_is_publisher(username))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == username)
			{
				if(publisher[i].has_bought_film(film_id))
				{
					has_bought = HAS_BOUGHT;
					break;
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
				if(user[i]->has_bought_film(film_id))
				{
					has_bought = HAS_BOUGHT;
					break;
				}
			}
		}
	}
	if(has_bought == HAS_NOT_BOUGHT)
		throw Permission_Denied();
}
void Manager::rate(std::string username, std::vector<std::string> lines_seperated)
{
	if(username == "")
		throw Permission_Denied();
	int film_id = find_film_id(lines_seperated);
	int rate = -1;
	int publisher_id;
	check_if_bought(username, film_id);
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i++)
		if(lines_seperated[i] == SCORE && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			rate = std::stoi(lines_seperated[i + 1]);
		}

	if(film_id <= 0 || rate < 1 || rate > 10)
		throw Bad_Request();
	
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			film[i].new_rate(rate);						
			publisher_id = film[i].return_PLPYI(PUBLISHER_ID);
		}
	}
	for(int i = 0; i < user.size(); i++)
	{
		for(int j = 0; j < user[i]->how_many_films_bought(); j++)
			if(user[i]->has_bought_film(film_id))
				user[i]->change_rate(rate, film_id);
	}
	
	for(int i = 0; i < publisher.size(); i++)
		publisher[i].change_rate(rate , film_id);
	add_notification_for_rate(username, film_id, publisher_id);
	std::cout<<OK<<std::endl;
}
void Manager::search_films(std::string username, std::vector<std::string> lines_seperated, int repeatition)
{
	if(repeatition == REPEAT)
	{
		if(username == "")
			throw Permission_Denied();
		int min_rate = -1, min_year = -1, price = -1, max_year = -1;
		std::string director = "";
		std::string film_name = "";
		for(int i = START_OF_ACTION; i < lines_seperated.size(); i++)
		{
			if(lines_seperated[i] == MAX_YEAR && i != lines_seperated.size() - 1)
				max_year = std::stoi(lines_seperated[i + 1]);
			else if(lines_seperated[i] == PRICE && i != lines_seperated.size() - 1)
				price = std::stoi(lines_seperated[i + 1]);
			else if(lines_seperated[i] == NAME && i != lines_seperated.size() - 1)
				film_name = lines_seperated[i + 1];
			else if(lines_seperated[i] == DIRECTOR && i != lines_seperated.size() - 1)
				director = lines_seperated[i + 1];
			else if(lines_seperated[i] == MIN_YEAR && i != lines_seperated.size() - 1)
				min_year = std::stoi(lines_seperated[i + 1]);
			else if(lines_seperated[i] == MIN_RATE && i != lines_seperated.size() - 1)
				min_rate = std::stoi(lines_seperated[i + 1]);
		}
		if(max_year < -1 || min_year < -1 || price < -1 || min_rate < -1)
			throw Bad_Request();
		std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
		for(int i = 0 ; i  < film.size(); i++)
		{		
			int print_status = NOT_TO_PRINT;
			if(lines_seperated.size() > 2)
			{
				if(max_year != -1 || min_year != -1 || price != -1 || min_rate != -1 || director != "" || film_name != "")
				{
					int counter = ZERO;	
					if(max_year != -1 || min_year != -1)
					{
						if(max_year != -1 && min_year == -1 && film[i].return_PLPYI(YEAR) <= max_year)
							print_status = PRINT;
						else if (max_year == -1 && min_year != -1 && film[i].return_PLPYI(YEAR) >= max_year)
							print_status = PRINT;
						else if (max_year != -1 && min_year != -1 && film[i].return_PLPYI(YEAR) >= min_year && film[i].return_PLPYI(YEAR) <= max_year)
							print_status = PRINT;
						else 
							continue;
					}
					if(price != -1)
					{
						if(film[i].return_PLPYI(PRICE) == price)
							print_status = PRINT;
						else 
							continue;
					}
					if(min_rate != -1)
					{
						if(film[i].return_PLPYI(RATE) >= min_rate)
							print_status = PRINT;
						else 
							continue;
					}
					if(director != "")
					{
						if(film[i].return_NDS(DIRECTOR) == director)
							print_status = PRINT;
						else 
							continue;
					}
					if(film_name != "")
					{
						if(film[i].return_NDS(NAME) == film_name)
							print_status = PRINT;
						else 
							continue;
					}
					if(print_status == NOT_TO_PRINT)
						continue;
					else
						print_film(counter, film,i);
				}
				else
				{	
					print_film(i, film,i);
					i--;
				}
			}
			else
			{	
				print_film(i, film,i);
				i--;
			}
		}
	}
}
std::string Manager::find_comment(std::vector<std::string> lines_seperated)
{
	std::string content ="";
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i += 2)
	{
		if( lines_seperated[i] == "content" && i != lines_seperated.size() - 1)
			content = lines_seperated[i + 1];
		else if( lines_seperated[i] == "content" && i != lines_seperated.size() - 1 && content != "")
			throw Bad_Request();
	}
	return content;
}
void Manager::add_comment(std::vector<std::string> lines_seperated, std::string username)
{
	int film_id = find_film_id(lines_seperated);
	std::string comments_content = find_comment(lines_seperated);
	for(int i = 0; i < user.size(); i++)
	{
		if(user[i]->get_RUP(USERNAME) == username)
		{
			if(!user[i]->has_bought_film(film_id))
				throw Permission_Denied();
		}
	}
	int publisher_id;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			publisher_id = film[i].return_PLPYI(PUBLISHER_ID);
			film[i].add_comment(comments_content, comment_id, username);
			break;
		}
	}
	int status = DOES_NOT_EXIST;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
			status = EXISTS;
	}
	if(status == DOES_NOT_EXIST)
		throw Not_Found();
	std::string notification = "User ";
	notification += username;
	notification += " with id ";
	notification += std::to_string(find_id(username));
	notification += " comment on your film ";
	notification += find_film_name(film_id);
	notification += " with id ";
	notification += std::to_string(film_id);
	notification +=".";
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_id() == publisher_id)
			publisher[i].add_notification(notification);
	}
	comment_id++;
	std::cout<<OK<<std::endl;
}
void Manager::reply(std::string username, std::vector<std::string> lines_seperated)
{
	check_if_user_is_publisher(username);
	int film_id = find_film_id(lines_seperated);
	int comment_id;
	std::string content;
	std::string notification = "Publisher ";
	notification += username;
	notification += " with id ";
	notification += std::to_string(find_id(username));
	notification += " reply to your comment.";
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i += 2)
	{
		if(lines_seperated[i] == COMMENT_ID && i != lines_seperated.size() - 1)
			comment_id = std::stoi(lines_seperated[i + 1]);
		if(lines_seperated[i] == "content" && i != lines_seperated.size() - 1)
			content = lines_seperated[i + 1];
	}
	std::string commenter;
	int status = DOES_NOT_EXIST;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			if(film[i].return_PLPYI(PUBLISHER_ID) != find_id(username))
				throw Permission_Denied();
			for(int j = 0; j < film[i].comments.size(); j++)
			{
				if(film[i].comments[j].return_cm_id() == comment_id)
				{
					film[i].comments[j].set_reply(content);
					commenter = film[i].comments[j].return_commenter();
					status = EXISTS;
				}
			}
		}
	}
	if(status == DOES_NOT_EXIST)
		throw Bad_Request();
	if(user_is_publisher(commenter))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == commenter)
			{
				publisher[i].add_notification(notification);
				break;
			}
		}
	}
	else
	{
		for(int i = 0; i < user.size(); i++)
		{
			if(user[i]->get_RUP(USERNAME) == commenter)
			{
				user[i]->add_notification(notification);;
				break;
			}
		}
	}
	std::cout<<OK<<std::endl;
}
void Manager::get_purchased(std::vector<std::string> lines_seperated, std::string username)
{
	int min_rate = -1, min_year = -1, price = -1, max_year = -1;
	std::string director = "";
	std::string film_name = "";
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i++)
	{
		if(lines_seperated[i] == MAX_YEAR && i != lines_seperated.size() - 1)
			max_year = std::stoi(lines_seperated[i + 1]);
		else if(lines_seperated[i] == PRICE && i != lines_seperated.size() - 1)
			price = std::stoi(lines_seperated[i + 1]);
		else if(lines_seperated[i] == NAME && i != lines_seperated.size() - 1)
			film_name = lines_seperated[i + 1];
		else if(lines_seperated[i] == DIRECTOR && i != lines_seperated.size() - 1)
			director = lines_seperated[i + 1];
		else if(lines_seperated[i] == MIN_YEAR && i != lines_seperated.size() - 1)
			min_year = std::stoi(lines_seperated[i + 1]);
		else if(lines_seperated[i] == MIN_RATE && i != lines_seperated.size() - 1)
			min_rate = std::stoi(lines_seperated[i + 1]);
	}
	if(max_year < -1 || min_year < -1 || price < -1 || min_rate < -1)
		throw Bad_Request();
	std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
	show_purchased_without_filter(username, lines_seperated);
	show_purchased_with_filter(lines_seperated, username);
}
void Manager::get_notifications(std::string username)
{
	if(username == "")
		throw Permission_Denied();
	std::cout<<"#. Notification Message"<<std::endl;
	if(user_is_publisher(username))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == username)
				publisher[i].show_notifications();
		}
	}
	else
	{
		for(int i = 0; i < user.size(); i++)
		{
			if(user[i]->get_RUP(USERNAME) == username)
				user[i]->show_notifications();
		}
	}
}
void Manager::show_notifications_with_limit(std::string username, std::vector<std::string> lines_seperated)
{
	if(username == "")
		throw Permission_Denied();
	int limit;
	std::cout<<"#. Notification Message"<<std::endl;
	for(int i = START_OF_ACTION + 1; i < lines_seperated.size(); i += 2)
	{
		if(lines_seperated[i] == "limit" && i != lines_seperated.size() - 1)
			limit = std::stoi(lines_seperated[i + 1]);
	}
	if(limit < 0)
		throw Bad_Request();
	if(user_is_publisher(username))
	{
		for(int i = 0; i < publisher.size(); i++)
		{
			if(publisher[i].return_username() == username)
				publisher[i].show_notifications_limited(limit);
		}
	}
	else
	{
		for(int i = 0; i < user.size(); i++)
		{
			if(user[i]->get_RUP(USERNAME) == username)
				user[i]->show_notifications_limited(limit);
		}
	}
}
void Manager::delete_comments(std::string username, std::vector<std::string> lines_seperated)
{
	check_if_user_is_publisher(username);
	int film_id = find_film_id(lines_seperated);
	int comment_id;
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i += 2)
		if(lines_seperated[i] == COMMENT_ID && i != lines_seperated.size() - 1)
			comment_id = std::stoi(lines_seperated[i + 1]);
	int status = DOES_NOT_EXIST;
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			for(int j = 0; j < film[i].comments.size(); j++)
			{
				if(film[i].comments[j].return_cm_id() == comment_id)
				{
					status = EXISTS;
					film[i].comments.erase(film[i].comments.begin() + j);
					break;
				}
			} 
		}
	}
	if(status == DOES_NOT_EXIST)
		throw Not_Found();
	std::cout<<OK<<std::endl;
}
void Manager::edit_film(std::string username, std::vector<std::string> lines_seperated)
{
	check_if_user_is_publisher(username);
	int film_id = find_film_id(lines_seperated);
	std::string film_name = "";
	std::string director = "";
	std::string summary = "";
	int year = -1;
	int length = -1;
	int price = -1;
	edit_film_for_every_one(username, lines_seperated, year, length, price, film_name, director, summary, film_id);
	edit_film_for_publisher(username, film_id, year, length, price, film_name, director, summary);
	std::cout<<OK<<std::endl;
}
void Manager::find_signup_stats(std::vector<std::string> lines_seperated, std::string &username, std::string &password, std::string &email, int &age, int &is_publisher)
{
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i += 2)
	{
		if(lines_seperated[i] == USERNAME && i != lines_seperated.size() - 1)
		{
			if(signup_exists(lines_seperated, i + 1))
				throw Bad_Request();
			username = lines_seperated[i + 1];
		}
		else if (lines_seperated[i] == PASSWORD && i != lines_seperated.size() - 1)
			password = lines_seperated[i + 1];
		else if (lines_seperated[i] == EMAIL && i != lines_seperated.size() - 1)
		{
			email = lines_seperated[i + 1];
			if(!is_email_valid(email))
				throw Bad_Request();
		}
		else if (lines_seperated[i] == AGE && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			age = std::stoi(lines_seperated[i + 1]);
		}
		else if(lines_seperated[i] == PUBLISHER && i != lines_seperated.size() - 1)
			if(lines_seperated[i + 1] == "true")
				is_publisher = IS_PUBLISHER;
		else if((lines_seperated[i] == AGE && i != lines_seperated.size() - 1 && age != -1) || (lines_seperated[i] == EMAIL && i != lines_seperated.size() - 1 && email != "") 
			|| (lines_seperated[i] == PASSWORD && i != lines_seperated.size() - 1 && password != "") 
			|| (lines_seperated[i] == USERNAME && i != lines_seperated.size() - 1 && username != ""))
			throw Bad_Request();
	}
}
void Manager::find_film_stats(std::vector<std::string> lines_seperated, std::string &name, int &year, int &length, int &price, std::string &summary, std::string &director)
{
	for(int i = START_OF_ACTION; i < lines_seperated.size(); i += 2)
	{
		if(lines_seperated[i] == NAME && i != lines_seperated.size() - 1)
			name = lines_seperated[i + 1];
		else if (lines_seperated[i] ==  YEAR && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			year = std::stoi(lines_seperated[i + 1]);
		}
		else if (lines_seperated[i] == LENGTH && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			length = std::stoi(lines_seperated[i + 1]);
		}
		else if (lines_seperated[i] == PRICE && i != lines_seperated.size() - 1)
		{
			if(check_if_has_char(lines_seperated[i + 1]))
				throw Bad_Request();
			price = std::stoi(lines_seperated[i + 1]);
		}
		else if (lines_seperated[i] == SUMMARY && i != lines_seperated.size() - 1)
			summary = lines_seperated[i + 1];
		else if (lines_seperated[i] == DIRECTOR && i != lines_seperated.size() - 1)
			director = lines_seperated[i + 1];
		else if((lines_seperated[i] == NAME && i != lines_seperated.size() - 1 && name != "") ||
			(lines_seperated[i] ==  YEAR && i != lines_seperated.size() - 1 && year != -1) ||
			(lines_seperated[i] == LENGTH && i != lines_seperated.size() - 1 && length != -1) ||
			(lines_seperated[i] == PRICE && i != lines_seperated.size() - 1 && price != -1) ||
			(lines_seperated[i] == SUMMARY && i != lines_seperated.size() - 1 && summary != "") ||
			(lines_seperated[i] == DIRECTOR && i != lines_seperated.size() - 1 && director != ""))
			throw Bad_Request();
	}
}
void Manager::added_film_notification(std::string username)
{
	std::string notification = "Publisher ";
	notification += username;
	notification += "with id ";
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_username() == username)
		{
			notification += std::to_string(publisher[i].return_id());
			notification += " register new film.";
			for(int j = 0; j < publisher[i].how_many_followers(); j++)
			{
				for(int k = 0; k < user.size(); k++)
				{
					if(user[k]->get_RUP(USERNAME) == publisher[i].followers[j]->get_RUP(USERNAME))
					{
						if(user[k]->get_RUP(ROLE) == PUBLISHER)
						{
							for(int l = 0; l < publisher.size(); l++)
								if(user[k]->get_RUP(USERNAME) == publisher[l].return_username())
									publisher[l].add_notification(notification);
						}
						else
							user[k]->add_notification(notification);
					}
				}
			}
		}
	}
}
void Manager::set_film_changes(int film_id, int year, int length, int price, std::string film_name, std::string director, std::string summary)
{
	for(int i = 0; i < film.size(); i++)
	{
		if(film[i].return_PLPYI(FILM_ID) == film_id)
		{
			if(year != -1)
				film[i].set_year(year);
			if(length != -1)
				film[i].set_length(length);
			if(price != -1)
				film[i].set_price(price);
			if(film_name != "")
				film[i].set_name(film_name);
			if(director != "")
				film[i].set_director(director);
			if(summary != "")
				film[i].set_summary(summary);
			break;
		}
	}
}
void Manager::follow_notification(int _user_id, std::string username)
{
	for(int i = 0; i < publisher.size(); i++)
	{
		if(publisher[i].return_id() == _user_id)
		{
			check_if_user_is_publisher(publisher[i].return_username());
			for(int j = 0; j < user.size(); j++)
			{
				if(user[j]->get_RUP(USERNAME) == username)
				{
					int customer_id;
					publisher[i].add_follower(user[j]);
					std::string notification = "User ";
					notification += username;
					notification += " with id ";
					for(int k = 0; k < user.size(); k++)
					{
						if(username == user[k]->get_RUP(USERNAME))
						{	
							customer_id = user[k]->get_id();
							break;
						}
					}
					notification += std::to_string(customer_id);
					notification += " follow you.";
					publisher[i].add_notification(notification);
				} 
			}
		}
	}
}
void Manager::show_all_films(std::vector<std::string>lines_seperated, std::string username, int max_year, int min_year, int price, int min_rate, std::string director, std::string film_name)
{
	std::cout << "#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director" << std::endl;
	for(int i = 0 ; i  < publisher.size(); i++)
	{
		if(publisher[i].return_username() == username)
		{
			for(int j = 0; j < publisher[i].films_published.size(); j++)
			{		
				int print_status = NOT_TO_PRINT;
				if(lines_seperated.size() > 2)
				{
					if(max_year != -1 || min_year != -1 || price != -1 || min_rate != -1 || director != "" || film_name != "")
					{
						int counter = ZERO;
						if(max_year != -1 || min_year != -1)
						{
							if(max_year != -1 && min_year == -1 && publisher[i].films_published[j].return_PLPYI(YEAR) <= max_year)
								print_status = PRINT;
							else if (max_year == -1 && min_year != -1 && publisher[i].films_published[j].return_PLPYI(YEAR) >= max_year)
								print_status = PRINT;
							else if (max_year != -1 && min_year != -1 && publisher[i].films_published[j].return_PLPYI(YEAR) >= min_year && publisher[i].films_published[j].return_PLPYI(YEAR) <= max_year)
								print_status = PRINT;
							else 
								continue;
						}
						if(price != -1)
						{
							if(publisher[i].films_published[j].return_PLPYI(PRICE) <= price)
								print_status = PRINT;
							else 
								continue;
						}
						if(min_rate != -1)
						{
							if(publisher[i].films_published[j].return_PLPYI(RATE) >= min_rate)
								print_status = PRINT;
							else 
								continue;
						}
						if(director != "")
						{
							if(publisher[i].films_published[j].return_NDS(DIRECTOR) == director)
								print_status = PRINT;
							else 
								continue;
						}
						if(film_name != "")
						{
							if(publisher[i].films_published[j].return_NDS(NAME) == film_name)
								print_status = PRINT;
							else 
								continue;
						}
						if(print_status == NOT_TO_PRINT)
							continue;
						else
							print_film(counter, publisher[i].films_published, j);
					}
					else
					{	
						print_film(j, publisher[i].films_published, j);
						j--;
					}
				}
				else
				{	
					print_film(j, publisher[i].films_published, j);
					j--;
				}
			}
		}
	}
}
void Manager::show_purchased_without_filter(std::string username, std::vector<std::string> lines_seperated)
{
	if(lines_seperated.size() <= 3)
	{
		if(user_is_publisher(username))
		{
			for(int i = 0 ; i  < publisher.size(); i++)
			{
				if(publisher[i].return_username() == username)
				{
					int counter = 1;
					for(int j = 0; j < film.size(); j++)
						if(publisher[i].has_bought_film(film[j].return_PLPYI(FILM_ID)))
						{
							std::cout<<counter<<". "<<film[j].return_PLPYI(FILM_ID)<<SEPERATOR<<film[j].return_NDS(NAME)<<SEPERATOR<<film[j].return_PLPYI(LENGTH);
							std::cout<<SEPERATOR<<film[j].return_PLPYI(PRICE)<<SEPERATOR<<film[j].get_rate()<<SEPERATOR<<film[j].return_PLPYI(YEAR)<<SEPERATOR;
							std::cout<<film[j].return_NDS(DIRECTOR)<<std::endl;
							counter++;
						}
					break;
				}
			}
		}
		else
		{
			for(int i = 0; i < user.size(); i++)
			{
				if(user[i]->get_RUP(USERNAME) == username)
				{
					int counter = 1;
					for(int j = 0; j < film.size(); j++)
					{
						if(user[i]->has_bought_film(film[j].return_PLPYI(FILM_ID)))
						{
							std::cout<<counter<<". "<<film[j].return_PLPYI(FILM_ID)<<SEPERATOR<<film[j].return_NDS(NAME)<<SEPERATOR<<film[j].return_PLPYI(LENGTH);
							std::cout<<SEPERATOR<<film[j].return_PLPYI(PRICE)<<SEPERATOR<<film[j].get_rate()<<SEPERATOR<<film[j].return_PLPYI(YEAR)<<SEPERATOR;
							std::cout<<film[j].return_NDS(DIRECTOR)<<std::endl;
							counter++;
						}
					}
					break;
				}
			}
		}
	}
}
void Manager::filter_for_publisher(int max_year, int min_year, int price, int min_rate, std::string director, std::string film_name,int i)
{
	int counter = 0;
	for(int j = 0; j < film.size(); j++)
	{
		int print_status = PRINT;
		if(publisher[i].has_bought_film(film[j].return_PLPYI(FILM_ID)))
		{
			if(max_year != -1 || min_year != -1)
			{
				if(max_year != -1 && min_year == -1 && film[j].return_PLPYI(YEAR) <= max_year)
					print_status = PRINT;
				else if (max_year == -1 && min_year != -1 && film[j].return_PLPYI(YEAR) >= max_year)
					print_status = PRINT;
				else if (max_year != -1 && min_year != -1 && film[j].return_PLPYI(YEAR) >= min_year && film[j].return_PLPYI(YEAR) <= max_year)
					print_status = PRINT;
				else 
					continue;
			}
			if(price != -1)
			{
				if(film[j].return_PLPYI(PRICE) <= price)
					print_status = PRINT;
				else 
					continue;
			}
			if(min_rate != -1)
			{
				if(film[j].return_PLPYI(RATE) >= min_rate)
					print_status = PRINT;
				else 
					continue;
			}
			if(director != "")
			{
				if(film[j].return_NDS(DIRECTOR) == director)
					print_status = PRINT;
				else 
					continue;
			}
			if(film_name != "")
			{
				if(film[j].return_NDS(NAME) == film_name)
					print_status = PRINT;
				else 
					continue;
			}
			if(print_status == NOT_TO_PRINT)
				continue;
			else
				std::cout<<counter<<". "<<film[j].return_PLPYI(FILM_ID)<<SEPERATOR<<film[j].return_NDS(NAME)<<SEPERATOR<<film[j].return_PLPYI(LENGTH);
				std::cout<<SEPERATOR<<film[j].return_PLPYI(PRICE)<<SEPERATOR<<film[j].get_rate()<<SEPERATOR<<film[j].return_PLPYI(YEAR)<<SEPERATOR;
				std::cout<<film[j].return_NDS(DIRECTOR)<<std::endl;
				counter++;
		}
	}
}
void Manager::filter_for_user(int max_year, int min_year, int price, int min_rate, std::string director, std::string film_name,int i)
{
	int counter = 0;
	for(int j = 0; j < film.size(); j++)
	{
		int print_status = PRINT;
		if(user[i]->has_bought_film(film[j].return_PLPYI(FILM_ID)))
		{
			if(max_year != -1 || min_year != -1)
			{
				if(max_year != -1 && min_year == -1 && film[j].return_PLPYI(YEAR) <= max_year)
					print_status = PRINT;
				else if (max_year == -1 && min_year != -1 && film[j].return_PLPYI(YEAR) >= max_year)
					print_status = PRINT;
				else if (max_year != -1 && min_year != -1 && film[j].return_PLPYI(YEAR) >= min_year && film[j].return_PLPYI(YEAR) <= max_year)
					print_status = PRINT;
				else 
					continue;
			}
			if(price != -1)
			{
				if(film[j].return_PLPYI(PRICE) <= price)
					print_status = PRINT;
				else 
					continue;
			}
			if(min_rate != -1)
			{
				if(film[j].return_PLPYI(RATE) >= min_rate)
					print_status = PRINT;
				else 
					continue;
			}
			if(director != "")
			{
				if(film[j].return_NDS(DIRECTOR) == director)
					print_status = PRINT;
				else 
					continue;
			}
			if(film_name != "")
			{
				if(film[j].return_NDS(NAME) == film_name)
					print_status = PRINT;
				else 
					continue;
			}
			if(print_status == NOT_TO_PRINT)
				continue;
			else
				std::cout<<counter<<". "<<film[j].return_PLPYI(FILM_ID)<<SEPERATOR<<film[j].return_NDS(NAME)<<SEPERATOR<<film[j].return_PLPYI(LENGTH);
				std::cout<<SEPERATOR<<film[j].return_PLPYI(PRICE)<<SEPERATOR<<film[j].get_rate()<<SEPERATOR<<film[j].return_PLPYI(YEAR)<<SEPERATOR;
				std::cout<<film[j].return_NDS(DIRECTOR)<<std::endl;
				counter++;
		}
	}
}
void Manager::show_purchased_with_filter(std::vector<std::string> lines_seperated, std::string username)
{
	int max_year = -1, price = -1, min_year = -1, min_rate = -1;
	std::string film_name = "", director = "";
	if(lines_seperated.size() > 3)
	{
		for(int i = START_OF_ACTION; i < lines_seperated.size(); i++)
		{
			if(lines_seperated[i] == MAX_YEAR && i != lines_seperated.size() - 1)
			{
				if(check_if_has_char(lines_seperated[i + 1]))
					throw Bad_Request();
				max_year = std::stoi(lines_seperated[i + 1]);
			}
			else if(lines_seperated[i] == PRICE && i != lines_seperated.size() - 1)
			{
				if(check_if_has_char(lines_seperated[i + 1]))
					throw Bad_Request();
				price = std::stoi(lines_seperated[i + 1]);
			}
			else if(lines_seperated[i] == NAME && i != lines_seperated.size() - 1)
				film_name = lines_seperated[i + 1];
			else if(lines_seperated[i] == DIRECTOR && i != lines_seperated.size() - 1)
				director = lines_seperated[i + 1];
			else if(lines_seperated[i] == MIN_YEAR && i != lines_seperated.size() - 1)
			{
				if(check_if_has_char(lines_seperated[i + 1]))
					throw Bad_Request();
				min_year = std::stoi(lines_seperated[i + 1]);
			}
			else if(lines_seperated[i] == MIN_RATE && i != lines_seperated.size() - 1)
			{
				if(check_if_has_char(lines_seperated[i + 1]))
					throw Bad_Request();
				min_rate = std::stoi(lines_seperated[i + 1]);
			}
		}
		if(max_year < -1 || min_year < -1 || price < -1 || min_rate < -1)
			throw Bad_Request();
		if(user_is_publisher(username))
		{
			for(int i = 0 ; i  < publisher.size(); i++)
			{
				if(publisher[i].return_username() == username)
					filter_for_publisher(max_year, min_year, price, min_rate, director, film_name, i);
			}
		}
		else
		{
			for(int i = 0; i < user.size(); i++)
				if(user[i]->get_RUP(USERNAME) == username)
					filter_for_user(max_year, min_year, price, min_rate, director, film_name, i);
		}
	}
}
