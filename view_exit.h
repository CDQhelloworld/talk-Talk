#pragma once
#ifndef VIEW_EXIT_H
#ifndef VIEW_EXIT_H

#include "view.h"
#include <string>

class view_exit: public view
{
public:
	view_exit();
	~view_exit(){};
	void process(Json::Value value, int cli_fd);
	void responce();
private:
	string _message;
	int _cli_fd;
	bool _flag;
};

#endif // !VIEW_EXIT_H