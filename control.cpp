#include <iostream>
#include "control.h"
#include "public.h"
#include <json/json.h>
#include "view_login.h"
#include "view_exit.h"
#include "view_register.h"
#include "view_talk_one.h"
#include <errno.h>
#include <mysql/mysql.h>
using namespace std;

pthread_mutex_t mutex;

Control::control(char *ip)
{
	MYSQL *mpcon = mysql_init((MYSQL *)0);
	if(!mysql_real_connect(mpcon, ip, "root", "970808", NULL, 3306, NULL, 0))
	{
		cerr << "sql connect fail;errno:" << errno << endl;
		return;
	}

	_map.insert(make_pair(MSG_TYPE_REGISTER, new view_register(mpcon, ip)));
	_map.insert(make_pair(MSG_TYPE_LOGIN, new view_login(mpcon, ip)));
	_map.insert(make_pair(MSG_TYPE_EXIT, new view_exit(mpcon, ip)));
	_map.insert(make_pair(MSG_TYPE_TALK_ONE, new view_talk_one(mpcon, ip)));
}

/*
Control::~control()
{
	for(int i = 1; i <= _map.size(); ++i)
	{
		delete (*_map[i].second);
	}
    delete _redis;
}
*/

void Control::handle(char *buff, int cli_fd)
{
	Json::Value root;
	Json::Reader read;

	if(-1 == read.parse(buff, root))
	{
		cerr << "Json read error:" << errno << endl;
	}

	_map[root["type"].asInt()]->process(root, cli_fd);
	_map[root["type"].asInt()]->responce();
}
