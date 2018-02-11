#pragma once
#ifndef VIEW_LOGIN
#define VIEW_LOGIN

#include "view.h"
#include <string>
#include <mysql/mysql.h>
using namespace std;

class view_login : public view
{
public:
	view_login(void *mpcon);
	~view_login(){}
	void process(Json::Value val, int cli_fd);
	void responce();
private:
	string _message;
	int _cli_fd;
	bool _flag;
    MYSQL *_mpcon;
};

#endif // !VIEW_LOGIN
