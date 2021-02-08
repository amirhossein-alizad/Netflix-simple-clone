#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <string>
#include <iostream>
#include <string>
#define DOES_NOT_EXIST 0
#define WRONG 0
#define RIGHT 1
Response* set_login_page(std::string username);
class LoginHandler : public RequestHandler {
public:
	LoginHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};

class SignupHandler : public RequestHandler {
public:
	SignupHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class PostfilmHandler : public RequestHandler {
public:
	PostfilmHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class SeepublishedHandler : public RequestHandler {
public:
	SeepublishedHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class SeeboughtHandler : public RequestHandler {
public:
	SeeboughtHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class SendmoneyHandler : public RequestHandler {
public:
	SendmoneyHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class DeletefilmHandler : public RequestHandler {
public:
	DeletefilmHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class BuypageHandler : public RequestHandler {
public:
	BuypageHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class BuyfilmHandler : public RequestHandler {
public:
	BuyfilmHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class SeefilmsHandler : public RequestHandler {
public:
	SeefilmsHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class SeedetailHandler : public RequestHandler {
public:
	SeedetailHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class LogoutHandler : public RequestHandler {
public:
	LogoutHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class RateHandler : public RequestHandler {
public:
	RateHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class FilterHandler : public RequestHandler {
public:
	FilterHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
class CommentHandler : public RequestHandler {
public:
	CommentHandler(Manager * _manager):
	manager(_manager){}
  Response *callback(Request *);
private:
	Manager * manager;
};
#endif
