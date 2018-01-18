#pragma once
#ifndef VIEW_LOGIN
#define VIEW_LOGIN

#include "view.h"
#include <string>
class view_login() : public view
{
public:
	void process(Json::Value value, int cli_fd);
	void responce();
private:
	string message;
	int cli_fd;
};

#endif // !VIEW_LOGIN
