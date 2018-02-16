#pragma once
#ifndef VIEW_EXIT_H
#define VIEW_EXIT_H

#include "view.h"
#include <string>
#include <mysql/mysql.h>
using namespace std;

class view_exit: public view
{
public:
	view_exit(void *mpcon);
	~view_exit(){};
	void process(Json::Value value, int cli_fd);
	void responce();
private:
	string _message;
	int _cli_fd;
	bool _flag;
    MYSQL *_mpcon;
};

#endif // !VIEW_EXIT_H
