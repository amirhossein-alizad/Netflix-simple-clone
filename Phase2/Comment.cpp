#include "Comment.h"
void Comment::show_reply()
{
	for(int i = 0; i < reply.size(); i++)
		std::cout<<id<<"."<<i + 1<<". "<<reply[i]<<std::endl;
}