#ifndef COMMENT_H
#define COMMENT_H 
#include <string>
#include <iostream>
#include <vector>
class Comment
{
public:
	Comment(std::string _comment_itself, int _id, std::string _commenter)
	: comment_itself(_comment_itself), id(_id), commenter(_commenter){}
	void set_reply(std::string _reply){ reply.push_back(_reply); }
	std::string show_comment(){ return comment_itself; }
private:
	std::string comment_itself;
	std::vector<std::string> reply;
	std::string commenter;
	int id;
};
#endif