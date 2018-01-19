#pragma once
#ifndef VIEW_LOGIN
#define VIEW_LOGIN

#include "view.h"
#include <string>
using namespace std;

class view_login() : public view
{
public:
	view_login();
	~view_login(){}
	void process(Json::Value value, int cli_fd);
	void responce();
private:
	string _message;
	int _cli_fd;
	bool _flag;
};

#endif // !VIEW_LOGIN
