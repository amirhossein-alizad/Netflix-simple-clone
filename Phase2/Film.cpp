 #include "Film.h"
void Film::add_comment(std::string new_comment, int id, std::string username)
{
	Comment newcomment(new_comment, id, username);
	comments.push_back(newcomment);
}
std::string Film::return_NDS(std::string _name)
{
	if( _name == NAME)
		return name;
	if( _name == DIRECTOR)
		return director;
	if( _name == SUMMARY)
		return summary;
}
int Film::return_PLPYI(std::string _name)
{
	if(_name == FILM_ID)
		return film_id;
	if(_name == YEAR)
		return year;
	if(_name == PRICE)
		return price;
	if(_name == LENGTH)
		return length;
	if(_name == PUBLISHER_ID)
		return publisher_id;
}
void Film::new_rate(int newrate)
{
	how_many_rated++;
	rate = ((how_many_rated - 1) * rate + newrate) / how_many_rated ; 
}