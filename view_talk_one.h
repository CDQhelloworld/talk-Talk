#pragma once
#ifndef VIEW_TALK_ONE_H
#define VIEW_TALK_ONE_H

#include "view.h"
#include <mysql/mysql.h>
#include <string>

class view_talk_one: public view
{
public:
	view_talk_one();
	~view_talk_one(){};
	void process(Json::Value value, int cli_fd);
	void responce();
private:
	string _message;
	int _cli_fd;
	bool _flag;
    MYSQL *_mpcon;
};

#endif // !VIEW_TALK_ONE_H
