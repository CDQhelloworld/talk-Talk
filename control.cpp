#include <iostream>
#include "control.h"
#include "public.h"
#include <json/json.h>
#include "view_login.h"
#include "view_exit.h"
#include "view_register.h"
#include "view_talk_one.h"
#include <errno.h>
using namespace std;

Control::control()
{
	_map.insert(make_pair(MSG_TYPE_REGISTER, new view_register()));
	_map.insert(make_pair(MSG_TYPE_LOGIN, new view_login()));
	_map.insert(make_pair(MSG_TYPE_EXIT, new view_exit()));
	_map.insert(make_pair(MSG_TYPE_TALK_ONE, new view_talk_one()));

	//一次连接，终身受益
	mpcon = mysql_init((MYSQL *)0);
	//连接mysql            数据库指针  ip  数据库名    密码       端口号
	if(!mysql_real_connect(mpcon, "127.0.0.1", "root", "970808", NULL, 3306, NULL, 0))
	{
		cerr << "sql connect fail;errno:" << errno << endl;
		return 0;
	}
}

Control::~control()
{
	for(int i = 1; i <= _map.size(); ++i)
	{
		delete _map[i].second;
	}
}

void Control::handle(char *buff, int cli_fd)
{
	Json::Value root;
	Json::Reader read;

	if(-1 == read.parse(buff, root))
	{
		cerr << "Json read error:" << errno << endl;
	}

	_map[root["type"].asInt()]->process(root, cli_fd， MYSQL *mpcon);
	_map[root["type"].asInt()]->responce();
}
