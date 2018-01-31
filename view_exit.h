#pragma once
#ifndef VIEW_EXIT_H
#define VIEW_EXIT_H

#include "view.h"
#include <string>
#include "redis.h"
#include <mysql/mysql.h>
using namespace std;

class view_exit: public view
{
public:
	view_exit(void *mpcon, void *redis);
	~view_exit(){};
	void process(Json::Value value, int cli_fd);
	void responce();
private:
	string _message;
	int _cli_fd;
	bool _flag;
    MYSQL *_mpcon;
    pRedis _redis;
};

#endif // !VIEW_EXIT_H
