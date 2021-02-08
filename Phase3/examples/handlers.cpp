#include "handlers.hpp"
using namespace std;
Response* CommentHandler::callback(Request *req)
{
	Response *res = new Response;
	string film_id = req->getBodyParam("film_id");
	string comment = req->getBodyParam("comment");
	manager->add_comment(comment, stoi(film_id), req->getSessionId());
	if(manager->user_is_publisher(req->getSessionId()))
		res = Response::redirect("/publisher");
	else 
		res = Response::redirect("/customer");
	return res;
}
Response* RateHandler::callback(Request *req)
{
	Response *res = new Response;
	string film_id = req->getBodyParam("film_id");
	string rate = req->getBodyParam("rate");
	manager->rate(stoi(film_id), stoi(rate));
	if(manager->user_is_publisher(req->getSessionId()))
		res = Response::redirect("/publisher");
	else 
		res = Response::redirect("/customer");
	return res;

}
Response *LogoutHandler::callback(Request *req)
{
	Response *res = new Response;
	res->setSessionId("0");
	res = Response::redirect("/");
	return res;
}
Response* FilterHandler::callback(Request *req)
{
	string director = req->getBodyParam("filter");
	Response *r = new Response;
	r->setHeader("Content-Type", "text/html");
	string body;
	body +=  "<!DOCTYPE html><style>h1{text-align: center;background-color: RGB(19,27,141);color: white;background-repeat: no-repeat;background-size: 150px;border: 1px solid black;";
	body += "padding: 5px;border-style: ridge;border-width: 4px;border-radius: 10px;border-color: RGB(196,255,14);}a:link {";
	body += "color: white;background-color: transparent;text-decoration: none;}a:visited {color: green;background-color: transparent;text-decoration: none;}a:hover {color: red;background-color:" ;
	body += "transparent;text-decoration: none;}.button {display: inline-block;border-radius: 10px;  background-color: RGB(196,255,14);  border: none;  color: RGB(19,27,141);  text-align: center;";
	body += " font-size: 25px;  padding: 10px;  width: 150px;  transition: all 0.5s;  cursor: pointer; margin: 5px;}";
	body += ".button span {  cursor: pointer;  display: inline-block;  position: relative;  transition: 0.5s;}.button span:after {  content:";
	body += "'" ;
	body += "\\";
	body += "00bb';   position: absolute;  opacity: 0;  top: 0;  right: -20px;  transition: 0.5s;}.button:hover span {  padding-right: 25px;}.button:hover span:after{  opacity: 1;  right: 0;}div {  border-style: ridge;";
	body +=" border-width: 4 px; border-radius: 10px;  border-color: RGB(196,255,14);  }table {  font-family: arial, sans-serif;  border-collapse: collapse;  width: 100%;}";
	body += "td, th {  border: 1px solid; border-color:RGB(196,255,14);  text-align: left; color:white;  padding: 8px;}tr:nth-child(even) {  background-color: RGB(19,27,141);}</style>";
	body += "</style><html><title>Published</title><link rel=\"shortcut icon\" href=\"index.png\" /><body style=\"text-align: center;background-image:url(bg.jpg)\">";
	body +=" <img src=\"index.png\" alt=\"utflix\" width=\"100px\" height=\"100px\"><h1>UTFLIX</h1><h1>PUBLISHED FILMS</h1>";
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 250px; border-radius: 3px; margin: auto; margin-bottom: 10px; \">";
	body += "<p style = \"font-size:30px; text-align:center;\">SEARCH</p>";
	body += "<form action = \"/filter\" method = \"post\">";
	body += "<input name=\"filter\" type=\"text\" placeholder=\"Username\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\"/>";
	body += "<button class=\"button\"><span>search</span></button></div></form>";	
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; \">";
	body +=" <table><tr><th>Name</th><th>Director</th><th>Year</th><th>Length</th><th>Price</th><th>Rate</th><th>Summary</th></tr>";
	for(int i = 0; i < manager->publisher.size(); i++)
	{
		if(manager->publisher[i].return_username() == req->getSessionId())
		{
			for(int j = 0; j < manager->publisher[i].films_published.size(); j++)
			{
				if(manager->publisher[i].films_published[j].return_NDS("director") == director)
				{
					body += "<tr><td>";
					body += manager->publisher[i].films_published[j].return_NDS("name");
					body += "</td><td>";
					body += manager->publisher[i].films_published[j].return_NDS("director");
					body += "</td><td>";
					body += to_string(manager->publisher[i].films_published[j].return_PLPYI("year"));
					body += "</td><td>";
					body += to_string(manager->publisher[i].films_published[j].return_PLPYI("length"));
					body += "</td><td>";
					body += to_string(manager->publisher[i].films_published[j].return_PLPYI("price"));
					body += "</td><td>";
					body += to_string(manager->publisher[i].films_published[j].get_rate());
					body += "</td><td>";
					body += manager->publisher[i].films_published[j].return_NDS("summary");
					body += "</td><td>";
					body += "<form action=\"/delete_film\" method=\"post\">";
					body += "<input type = \"hidden\" name=\"film_id\" value=\"";
					body += to_string(manager->publisher[i].films_published[j].return_PLPYI("film_id"));
					body += "\"><button class = \"button\" type = \"submit\" style=\" float:center;\"><span>delete</span></button></form>";
					body += "</td></tr>";
				}
			}
			break;
		}
	}
	body += "</table></div></body></html>";
	r->setBody(body);
	return r;
}
Response* SeedetailHandler::callback(Request *req)
{
	string body;
	Response * r = new Response;
	string film_id = req->getBodyParam("film_id");
	r->setHeader("Content-Type", "text/html");
	body +=  "<!DOCTYPE html><style>h1{text-align: center;background-color: RGB(19,27,141);color: white;background-repeat: no-repeat;background-size: 150px;border: 1px solid black;";
	body += "padding: 5px;border-style: ridge;border-width: 4px;border-radius: 10px;border-color: RGB(196,255,14);}a:link {";
	body += "color: white;background-color: transparent;text-decoration: none;}a:visited {color: green;background-color: transparent;text-decoration: none;}a:hover {color: red;background-color:" ;
	body += "transparent;text-decoration: none;}.button {display: inline-block;border-radius: 10px;  background-color: RGB(196,255,14);  border: none;  color: RGB(19,27,141);  text-align: center;";
	body += " font-size: 25px;  padding: 10px;  width: 200px;  transition: all 0.5s;  cursor: pointer; margin: 5px;}";
	body += ".button span {  cursor: pointer;  display: inline-block;  position: relative;  transition: 0.5s;}.button span:after {  content:";
	body += "'" ;
	body += "\\";
	body += "00bb';   position: absolute;  opacity: 0;  top: 0;  right: -20px;  transition: 0.5s;}.button:hover span {  padding-right: 25px;}.button:hover span:after{  opacity: 1;  right: 0;}div {  border-style: ridge;";
	body +=" border-width: 4 px; border-radius: 10px;  border-color: RGB(196,255,14);  }table {  font-family: arial, sans-serif;  border-collapse: collapse;  width: 100%;}";
	body += "td, th {  border: 1px solid; border-color:RGB(196,255,14);  text-align: left; color:white;  padding: 8px;}tr:nth-child(even) {  background-color: RGB(19,27,141);}</style>";
	body += "</style><html><title>films</title><link rel=\"shortcut icon\" href=\"index.png\" /><body style=\"text-align: center;background-image:url(bg.jpg)\">";
	body +=" <img src=\"index.png\" alt=\"utflix\" width=\"100px\" height=\"100px\"><h1>UTFLIX</h1><h1>FILM "; 
	body += req->getBodyParam("film_id");
	body += "</h1>";
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; margin-bottom: 10px; \">";	
	for(int i = 0; i < manager->film.size(); i++)
	{
		if(manager->film[i].return_PLPYI("film_id") == stoi(film_id))
		{
			body += "<p style=\" text-align:center; color:RGB(196,255,14); font-size:30px; \">";
			body += "film : ";
			body += manager->film[i].return_NDS("name");
			body += "<br>director : ";
			body += manager->film[i].return_NDS("director");
			body += "<br>year : ";
			body += to_string(manager->film[i].return_PLPYI("year"));
			body += "<br>length : ";
			body += to_string(manager->film[i].return_PLPYI("length"));
			body += "<br>price : ";
			body += to_string(manager->film[i].return_PLPYI("price"));
			body += "<br>rate : ";
			body += to_string(manager->film[i].get_rate());
			body += "<br>summary : ";
			body += manager->film[i].return_NDS("summary");
			body += "</p>";
			body += "</div><div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; margin-bottom: 10px; \">";	
			body += "<p style=\" text-align:center; color:RGB(196,255,14); font-size:30px; \"> comments</p>";
			for(int j = 0; j < manager->film[i].comments.size(); j++)
			{
				body += "<p style=\" text-align:center; color:RGB(196,255,14); font-size:30px; \">";
				body += to_string(j + 1);
				body += ". ";
				body += manager->film[i].comments[j].show_comment();
				body += "<br></p>";
			}
			body += "</div>";
			body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; margin-bottom: 10px; \">";
			body += "<p style=\" text-align:center; color:RGB(196,255,14); font-size:30px; \">";
			manager->recommend(req->getSessionId(), stoi(film_id), body);
			body += "</p></div>";
			break;
		}
	}
	body += "</body></html>";
	r->setBody(body);
	return r;
}
Response *SeefilmsHandler::callback(Request *req)
{
	string body;
	Response * r = new Response;
	r->setHeader("Content-Type", "text/html");
	body +=  "<!DOCTYPE html><style>h1{text-align: center;background-color: RGB(19,27,141);color: white;background-repeat: no-repeat;background-size: 150px;border: 1px solid black;";
	body += "padding: 5px;border-style: ridge;border-width: 4px;border-radius: 10px;border-color: RGB(196,255,14);}a:link {";
	body += "color: white;background-color: transparent;text-decoration: none;}a:visited {color: green;background-color: transparent;text-decoration: none;}a:hover {color: red;background-color:" ;
	body += "transparent;text-decoration: none;}.button {display: inline-block;border-radius: 10px;  background-color: RGB(196,255,14);  border: none;  color: RGB(19,27,141);  text-align: center;";
	body += " font-size: 25px;  padding: 10px;  width: 200px;  transition: all 0.5s;  cursor: pointer; margin: 5px;}";
	body += ".button span {  cursor: pointer;  display: inline-block;  position: relative;  transition: 0.5s;}.button span:after {  content:";
	body += "'" ;
	body += "\\";
	body += "00bb';   position: absolute;  opacity: 0;  top: 0;  right: -20px;  transition: 0.5s;}.button:hover span {  padding-right: 25px;}.button:hover span:after{  opacity: 1;  right: 0;}div {  border-style: ridge;";
	body +=" border-width: 4 px; border-radius: 10px;  border-color: RGB(196,255,14);  }table {  font-family: arial, sans-serif;  border-collapse: collapse;  width: 100%;}";
	body += "td, th {  border: 1px solid; border-color:RGB(196,255,14);  text-align: left; color:white;  padding: 8px;}tr:nth-child(even) {  background-color: RGB(19,27,141);}</style>";
	body += "</style><html><title>films</title><link rel=\"shortcut icon\" href=\"index.png\" /><body style=\"text-align: center;background-image:url(bg.jpg)\">";
	body +=" <img src=\"index.png\" alt=\"utflix\" width=\"100px\" height=\"100px\"><h1>UTFLIX</h1><h1>ALL FILMS</h1>";
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; \">";	
	body +=" <table><tr><th>Name</th><th>Director</th><th>Year</th><th>Length</th><th>Price</th><th>Rate</th><th>Summary</th></tr>";
	for(int i = 0; i < manager->film.size(); i++)
	{
		body += "<tr><td>";
		body += manager->film[i].return_NDS("name");
		body += "</td><td>";
		body += manager->film[i].return_NDS("director");
		body += "</td><td>";
		body += to_string(manager->film[i].return_PLPYI("year"));
		body += "</td><td>";
		body += to_string(manager->film[i].return_PLPYI("length"));
		body += "</td><td>";
		body += to_string(manager->film[i].return_PLPYI("price"));
		body += "</td><td>";
		body += to_string(manager->film[i].get_rate());
		body += "</td><td>";
		body += manager->film[i].return_NDS("summary");
		body += "</td><td>";
		body += "<form action=\"/see_detail\" method=\"post\">";
		body += "<input type = \"hidden\" name=\"film_id\" value=\"";
		body += to_string(manager->film[i].return_PLPYI("film_id"));
		body += "\"><button class = \"button\" type = \"submit\" style=\" float:center;\"><span>see details</span></button></form>";
		body += "</td></tr>";
	}
	body += "</table></div></body></html>";
	r->setBody(body);
	return r;
}
Response* SeeboughtHandler::callback(Request* req)
{
	string body;
	Response * r = new Response;
	r->setHeader("Content-Type", "text/html");
	body +=  "<!DOCTYPE html><style>h1{text-align: center;background-color: RGB(19,27,141);color: white;background-repeat: no-repeat;background-size: 150px;border: 1px solid black;";
	body += "padding: 5px;border-style: ridge;border-width: 4px;border-radius: 10px;border-color: RGB(196,255,14);}a:link {";
	body += "color: white;background-color: transparent;text-decoration: none;}a:visited {color: green;background-color: transparent;text-decoration: none;}a:hover {color: red;background-color:" ;
	body += "transparent;text-decoration: none;}.button {display: inline-block;border-radius: 10px;  background-color: RGB(196,255,14);  border: none;  color: RGB(19,27,141);  text-align: center;";
	body += " font-size: 25px;  padding: 10px;  width: 150px;  transition: all 0.5s;  cursor: pointer; margin: 5px;}";
	body += ".button span {  cursor: pointer;  display: inline-block;  position: relative;  transition: 0.5s;}.button span:after {  content:";
	body += "'" ;
	body += "\\";
	body += "00bb';   position: absolute;  opacity: 0;  top: 0;  right: -20px;  transition: 0.5s;}.button:hover span {  padding-right: 25px;}.button:hover span:after{  opacity: 1;  right: 0;}div {  border-style: ridge;";
	body +=" border-width: 4 px; border-radius: 10px;  border-color: RGB(196,255,14);  }table {  font-family: arial, sans-serif;  border-collapse: collapse;  width: 100%;}";
	body += "td, th {  border: 1px solid; border-color:RGB(196,255,14);  text-align: left; color:white;  padding: 8px;}tr:nth-child(even) {  background-color: RGB(19,27,141);}</style>";
	body += "</style><html><title>Published</title><link rel=\"shortcut icon\" href=\"index.png\" /><body style=\"text-align: center;background-image:url(bg.jpg)\">";
	body +=" <img src=\"index.png\" alt=\"utflix\" width=\"100px\" height=\"100px\"><h1>UTFLIX</h1><h1>BOUGHT FILMS</h1>";
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; \">";	
	body += "<form action= \"/send_to_add_money\"><button class=\"button\"  href = \"/add_money\"><span>add money</span></button></form>";
	body +=" <table><tr><th>Name</th><th>Director</th><th>Year</th><th>Length</th><th>Price</th><th>Rate</th><th>Summary</th></tr>";
	for(int i = 0; i < manager->film.size(); i++)
	{
		if(manager->check_if_bought(req->getSessionId(), manager->film[i].return_PLPYI("film_id")))
		{
			body += "<tr><td>";
			body += manager->film[i].return_NDS("name");
			body += "</td><td>";
			body += manager->film[i].return_NDS("director");
			body += "</td><td>";
			body += to_string(manager->film[i].return_PLPYI("year"));
			body += "</td><td>";
			body += to_string(manager->film[i].return_PLPYI("length"));
			body += "</td><td>";
			body += to_string(manager->film[i].return_PLPYI("price"));
			body += "</td><td>";
			body += to_string(manager->film[i].get_rate());
			body += "</td><td>";
			body += manager->film[i].return_NDS("summary");
			body += "</td><td>";
			body += "<form action= \"/rate\" method = \"post\"><input type =\"hidden\" name = \"film_id\" value = \"";
			body += to_string(manager->film[i].return_PLPYI("film_id"));
			body += "\"><input type = \"number\" name = \"rate\" placeholder = \"rate\"><button class=\"button\" type = \"submit\"><span>rate</span></button></form>";
			body += "<form action =\"/comment\" method=\"post\"><input type =\"hidden\" name = \"film_id\" value = \"";
			body += to_string(manager->film[i].return_PLPYI("film_id"));
			body += "\"><input type = \"text\" name = \"comment\" placeholder = \"comment\"><button class=\"button\" type = \"submit\"><span>comment</span></button></form>";
		}
	}
	body += "</table></div></body></html>";
	r->setBody(body);
	return r;
}
Response *BuyfilmHandler::callback(Request *req)
{
	manager->buy(req->getSessionId(), stoi(req->getBodyParam("film_id")));
	string body;
	Response * r = new Response;
	if(manager->user_is_publisher(req->getSessionId()))
		r = Response::redirect("/publisher");
	else 
		r = Response::redirect("/customer");
	return r;
}
Response *BuypageHandler::callback(Request *req)
{
	string body;
	Response * r = new Response;
	r->setHeader("Content-Type", "text/html");
	body +=  "<!DOCTYPE html><style>h1{text-align: center;background-color: RGB(19,27,141);color: white;background-repeat: no-repeat;background-size: 150px;border: 1px solid black;";
	body += "padding: 5px;border-style: ridge;border-width: 4px;border-radius: 10px;border-color: RGB(196,255,14);}a:link {";
	body += "color: white;background-color: transparent;text-decoration: none;}a:visited {color: green;background-color: transparent;text-decoration: none;}a:hover {color: red;background-color:" ;
	body += "transparent;text-decoration: none;}.button {display: inline-block;border-radius: 10px;  background-color: RGB(196,255,14);  border: none;  color: RGB(19,27,141);  text-align: center;";
	body += " font-size: 25px;  padding: 10px;  width: 100px;  transition: all 0.5s;  cursor: pointer; margin: 5px;}";
	body += ".button span {  cursor: pointer;  display: inline-block;  position: relative;  transition: 0.5s;}.button span:after {  content:";
	body += "'" ;
	body += "\\";
	body += "00bb';   position: absolute;  opacity: 0;  top: 0;  right: -20px;  transition: 0.5s;}.button:hover span {  padding-right: 25px;}.button:hover span:after{  opacity: 1;  right: 0;}div {  border-style: ridge;";
	body +=" border-width: 4 px; border-radius: 10px;  border-color: RGB(196,255,14);  }table {  font-family: arial, sans-serif;  border-collapse: collapse;  width: 100%;}";
	body += "td, th {  border: 1px solid; border-color:RGB(196,255,14);  text-align: left; color:white;  padding: 8px;}tr:nth-child(even) {  background-color: RGB(19,27,141);}</style>";
	body += "</style><html><title>buy</title><link rel=\"shortcut icon\" href=\"index.png\" /><body style=\"text-align: center;background-image:url(bg.jpg)\">";
	body +=" <img src=\"index.png\" alt=\"utflix\" width=\"100px\" height=\"100px\"><h1>UTFLIX</h1><h1>BUY FILMS</h1>";	
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; \">";
	body +=" <table><tr><th>Name</th><th>Director</th><th>Year</th><th>Length</th><th>Price</th><th>Rate</th><th>Summary</th></tr>";
	for(int j = 0; j < manager->user.size(); j++)
	{
		if(manager->user[j]->get_RUP("username") == req->getSessionId())
		{
			if(manager->user_is_publisher(req->getSessionId()))
			{
				for(int k = 0; k < manager->publisher.size(); k++)
				{
					if(manager->publisher[k].return_username() == req->getSessionId())
					{
						for(int i = 0; i < manager->film.size(); i++)
						{
							if(manager->publisher[k].how_much_money() >= manager->film[i].return_PLPYI("price"))
							{
								if(!manager->check_if_bought(req->getSessionId(), manager->film[i].return_PLPYI("film_id")))
								{
									body += "<tr><td>";
									body += manager->film[i].return_NDS("name");
									body += "</td><td>";
									body += manager->film[i].return_NDS("director");
									body += "</td><td>";
									body += to_string(manager->film[i].return_PLPYI("year"));
									body += "</td><td>";
									body += to_string(manager->film[i].return_PLPYI("length"));
									body += "</td><td>";
									body += to_string(manager->film[i].return_PLPYI("price"));
									body += "</td><td>";
									body += to_string(manager->film[i].get_rate());
									body += "</td><td>";
									body += manager->film[i].return_NDS("summary");
									body += "</td> <td>";
									body += "<form action=\"/buy_film\" method=\"post\">";
									body += "<input type = \"hidden\" name=\"film_id\" value=\"";
									body += to_string(manager->film[i].return_PLPYI("film_id"));
									body += "\"><button class = \"button\" type = \"submit\" style=\" float:center;\"><span>buy</span></button></form>";
									body += "</td></tr>";
								}
							}
						}
					}
				}
			}
			else
			{
				for(int i = 0; i < manager->film.size(); i++)
				{
					if(manager->user[j]->how_much_money() >= manager->film[i].return_PLPYI("price"))
					{
						if(!manager->check_if_bought(req->getSessionId(), manager->film[i].return_PLPYI("film_id")))
						{
							body += "<tr><td>";
							body += manager->film[i].return_NDS("name");
							body += "</td><td>";
							body += manager->film[i].return_NDS("director");
							body += "</td><td>";
							body += to_string(manager->film[i].return_PLPYI("year"));
							body += "</td><td>";
							body += to_string(manager->film[i].return_PLPYI("length"));
							body += "</td><td>";
							body += to_string(manager->film[i].return_PLPYI("price"));
							body += "</td><td>";
							body += to_string(manager->film[i].get_rate());
							body += "</td><td>";
							body += manager->film[i].return_NDS("summary");
							body += "</td> <td>";
							body += "<form action=\"/buy_film\" method=\"post\">";
							body += "<input type = \"hidden\" name=\"film_id\" value=\"";
							body += to_string(manager->film[i].return_PLPYI("film_id"));
							body += "\"><button class = \"button\" type = \"submit\" style=\" float:center;\"><span>buy</span></button></form>";
							body += "</td></tr>";
						}
					}
				}
			}
		}
	}
	body += "</table></div></body></html>";
	r->setBody(body);
	return r;
}
Response *LoginHandler::callback(Request *req)
{
	Response * res = new Response;
	string username = "", password = "";
	int status = DOES_NOT_EXIST;
	int wrong = WRONG;
  	username = req->getBodyParam("username");
	password = req->getBodyParam("password");
	res = manager->login(username, password, status, wrong);
	if(status == DOES_NOT_EXIST || wrong == WRONG)
		res = Response::redirect("/login_wrong");
	else
	{
		if(!manager->user_is_publisher(username))
			res = Response::redirect("/customer");
		else
			res = Response::redirect("/publisher");
	}
	res->setSessionId(username);
	return res;
}
Response* SeepublishedHandler::callback(Request *req)
{
	string body;
	Response * r = new Response;
	r->setHeader("Content-Type", "text/html");
	body +=  "<!DOCTYPE html><style>h1{text-align: center;background-color: RGB(19,27,141);color: white;background-repeat: no-repeat;background-size: 150px;border: 1px solid black;";
	body += "padding: 5px;border-style: ridge;border-width: 4px;border-radius: 10px;border-color: RGB(196,255,14);}a:link {";
	body += "color: white;background-color: transparent;text-decoration: none;}a:visited {color: green;background-color: transparent;text-decoration: none;}a:hover {color: red;background-color:" ;
	body += "transparent;text-decoration: none;}.button {display: inline-block;border-radius: 10px;  background-color: RGB(196,255,14);  border: none;  color: RGB(19,27,141);  text-align: center;";
	body += " font-size: 25px;  padding: 10px;  width: 150px;  transition: all 0.5s;  cursor: pointer; margin: 5px;}";
	body += ".button span {  cursor: pointer;  display: inline-block;  position: relative;  transition: 0.5s;}.button span:after {  content:";
	body += "'" ;
	body += "\\";
	body += "00bb';   position: absolute;  opacity: 0;  top: 0;  right: -20px;  transition: 0.5s;}.button:hover span {  padding-right: 25px;}.button:hover span:after{  opacity: 1;  right: 0;}div {  border-style: ridge;";
	body +=" border-width: 4 px; border-radius: 10px;  border-color: RGB(196,255,14);  }table {  font-family: arial, sans-serif;  border-collapse: collapse;  width: 100%;}";
	body += "td, th {  border: 1px solid; border-color:RGB(196,255,14);  text-align: left; color:white;  padding: 8px;}tr:nth-child(even) {  background-color: RGB(19,27,141);}</style>";
	body += "</style><html><title>Published</title><link rel=\"shortcut icon\" href=\"index.png\" /><body style=\"text-align: center;background-image:url(bg.jpg)\">";
	body +=" <img src=\"index.png\" alt=\"utflix\" width=\"100px\" height=\"100px\"><h1>UTFLIX</h1><h1>PUBLISHED FILMS</h1>";
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 250px; border-radius: 3px; margin: auto; margin-bottom: 10px; \">";
	body += "<p style = \"font-size:30px; text-align:center;\">SEARCH</p>";
	body += "<form action = \"/filter\" method = \"post\">";
	body += "<input name=\"filter\" type=\"text\" placeholder=\"Username\" style=\"display:block; margin: auto; margin-bottom: 10px; padding: 5px; width: 94%;\"/>";
	body += "<button class=\"button\"><span>search</span></button></div></form>";	
	body += "<div style=\"background-color: RGB(19,27,141); padding: 1%; max-width: 1500px; border-radius: 3px; margin: auto; \">";
	body +=" <table><tr><th>Name</th><th>Director</th><th>Year</th><th>Length</th><th>Price</th><th>Rate</th><th>Summary</th></tr>";
	for(int i = 0; i < manager->publisher.size(); i++)
	{
		if(manager->publisher[i].return_username() == req->getSessionId())
		{
			for(int j = 0; j < manager->publisher[i].films_published.size(); j++)
			{
				body += "<tr><td>";
				body += manager->publisher[i].films_published[j].return_NDS("name");
				body += "</td><td>";
				body += manager->publisher[i].films_published[j].return_NDS("director");
				body += "</td><td>";
				body += to_string(manager->publisher[i].films_published[j].return_PLPYI("year"));
				body += "</td><td>";
				body += to_string(manager->publisher[i].films_published[j].return_PLPYI("length"));
				body += "</td><td>";
				body += to_string(manager->publisher[i].films_published[j].return_PLPYI("price"));
				body += "</td><td>";
				body += to_string(manager->publisher[i].films_published[j].get_rate());
				body += "</td><td>";
				body += manager->publisher[i].films_published[j].return_NDS("summary");
				body += "</td><td>";
				body += "<form action=\"/delete_film\" method=\"post\">";
				body += "<input type = \"hidden\" name=\"film_id\" value=\"";
				body += to_string(manager->publisher[i].films_published[j].return_PLPYI("film_id"));
				body += "\"><button class = \"button\" type = \"submit\" style=\" float:center;\"><span>delete</span></button></form>";
				body += "</td></tr>";
			}
			break;
		}
	}
	body += "</table></div></body></html>";
	r->setBody(body);
	return r;
}
Response* DeletefilmHandler::callback(Request *req)
{
	string film_id = req->getBodyParam("film_id");
	manager->delete_films(req->getSessionId(), stoi(film_id));
	Response * r = new Response;
	r = Response::redirect("/publisher");
	return r;
}
Response *SignupHandler::callback(Request *req) 
{
	Response *res = new Response;
	int status = EXISTS;
	string username = "", email = "", password = "", is_publisher;
  	username = req->getBodyParam("username");
  	password = req->getBodyParam("password");
  	email = req->getBodyParam("email");
  	string age = req->getBodyParam("age");
  	is_publisher = req->getBodyParam("publisher");
  	int agee = stoi(age);
  	res = manager->signup(username, password, email, agee, is_publisher, status);
  	if(status == EXISTS)
  		res = Response::redirect("/signup_existed");
  	else
  	{
  		if(is_publisher == "on")
  			res = Response::redirect("/publisher");
  		else
  			res = Response::redirect("/customer");
  	}
  		res->setSessionId(username);
  	return res;
}
Response *PostfilmHandler::callback(Request *req) 
{
	Response * res = new Response();
	string name = req->getBodyParam("name");
	string director = req->getBodyParam("director");
	string summary = req->getBodyParam("summary");
	string year = req->getBodyParam("year");
	string length = req->getBodyParam("length");
	string price = req->getBodyParam("price");
	manager->add_film(req->getSessionId(), name, director, summary, stoi(year), stoi(length), stoi(price));
	res = Response::redirect("/publisher");
	return res;
}
Response *SendmoneyHandler::callback(Request *req) 
{
	string amount = req->getBodyParam("amount");
	manager->post_money(stoi(amount), req->getSessionId());
	string body;
	Response * r = new Response;
	if(manager->user_is_publisher(req->getSessionId()))
		r = Response::redirect("/publisher");
	else 
		r = Response::redirect("/customer");
	return r;
}