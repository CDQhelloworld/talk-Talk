#include <iostream>
#include "view_register.h"
#include <string>
using namespace std;

view_register::view_register(MYSQL *mpcon)
{
	this->mpcon = mpcon;
}

void view_register::process(Json::Value val, int cli_fd)
{
	_cli_fd = cli_fd;

	MYSQL *mpcon = this->mpcon;
	MYSQL_RES *mp_res;
	MYSQL_ROW mp_row;

	//进入user表中查找重名，如果没有则添加进user表中
	if(mysql_select_db(mpcon, "user"))
	{
		cerr << "select fail：errno：" << errno << endl;
		return 0;
	}

	string cmd = "SELECT * FROM user WHEN NAME=''";
	cmd.insert(cmd.length - 2, val["name"].asString());

	
}

void view_register::responce()
{

}