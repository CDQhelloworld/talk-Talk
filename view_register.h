#pragma once
#ifndef VIEW_REGISTER_H
#define VIEW_REGISTER_H

#include "view.h"
#include <mysql/mysql.h>

class view_register: public view
{
public:
	view_register(MYSQL *mpcon);
	~view_register(){}
	void process(Json::Value val, int cli_fd);
	void responce();
private:
	string _message;
	int _cli_fd;
	bool _flag;
};

#endif // !VIEW_REGISTER_H
