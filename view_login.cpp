#include"view_login.h"
#include"view.h"
#include<iostream>
#include<mysql/mysql.h>
#include<string>
#include<string.h>
#include<json/json.h>
using namespace std;

view_login::view_login(MYSQL *mpcon)
{
	_mpcon = mpcon;
}

void view_login::process(Json::Value val, int cli_fd)
{
	_cli_fd = cli_fd;
	
	MYSQL *mpcon = this->mpcon;
	MYSQL_RES *mp_res;
	MYSQL_ROW mp_row;

	//访问usr表
	if(mysql_select_db(mpcon, "user"))
	{
		cerr << "select fail：errno：" << errno << endl;
		return 0;
	}


	/*char cmd[64] = "SELECT * FORM USER WHERE NAME='";
	strcat((cmd + strlen(cmd) - 2), val["name"].asString());
	strcat(cmd + strlen(cmd) - 2), "'\0");*/

	string cmd = "SELECT * FORM user WHERE NAME=''";
	cmd.insert(cmd.length - 2, val["name"].asString());


	if(mysql_real_query(mpcon, cmd, strlen(cmd)))
	{
		cerr << "0 query fail;errno:" << errno << endl;
		return 0;
	}

	mp_res = mysql_store_result(mpcon);
	mp_row = mysql_fetch_row(mp_res);
	if(strcmp(val["pw"], row[2]) != 0)
	{
		//密码比对不上
		_flag = false;
		return;
	}

	//访问offline
	if(mysql_select_db(mpcon, "offline"))
	{
		cerr << "select fail：errno：" << errno << endl;
		return 0;
	}

	cmd = "SELECT * FORM offline WHERE NAME=''";
	cmd.insert(cmd.length - 2, val["name"].asString());

	mp_res = mysql_store_result(mpcon);
	mp_row = mysql_fetch_row(mp_res);
	_message = mp_row[2];

	cmd = "DELETE FORM offline WHERE NAME=''";
	cmd.insert(cmd.length - 2, val["name"].asString());
	mp_res = mysql_store_result(mpcon);

	//访问online
	if(mysql_select_db(mpcon, "online"))
	{
		cerr << "select fail：errno：" << errno << endl;
		return;
	}

	cmd = "SELECT * FORM online WHERE NAME=''";
	cmd.insert(cmd.length - 2, val["name"].asString());

	mp_res = mysql_store_result(mpcon);
	mp_row = mysql_fetch_row(mp_res);
	if(strcmp(val["name"], mp_row[2]) != 0)
	{
		flag = false;
		return;
	}

	cmd = "INSERT INTO online VALUES('','')";
	cmd.insert(cmd.length - 3, val["name"].asString());
	char buff[sizeof(int)] = {0};
	cmd.insert(cmd.length - 3, itoa(cli_fd, buff, 10));
	
	mp_res = mysql_store_result(mpcon);
}

void view_login::responce()
{
	if(flag)
	{
		//登陆成功
		char buff[1024] = "登陆成功！";
		if(_message.length != 0)
		{
			strcat(buff, "[");
			strcat(buff, _message);
			strcat(buff, "]");
		}
		send(_cli_fd, buff, strlen(buff), 0);
	}
	else
	{
		//登陆失败
		char buff[] = "登陆失败，输入密码错误或账号在异地登陆";
		send(_cli_fd, buff, strlen(buff), 0);
	}
	//send(string     _cli_fd);
}
 
