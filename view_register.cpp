#include <iostream>
#include "view_register.h"
#include <string>
#include "view.h"
#include <errno.h>
using namespace std;

view_register::view_register(void *mpcon)
{
	_mpcon = (MYSQL *)mpcon;
}

void view_register::process(Json::Value val, int cli_fd)
{
	_cli_fd = cli_fd;

	MYSQL *mpcon = _mpcon;
	MYSQL_RES *mp_res;
	MYSQL_ROW mp_row;

	if(mysql_select_db(mpcon, "user"))
	{
		cerr << "select fail£ºerrno£º" << errno << endl;
		return;
	}

	string cmd = "SELECT * FROM user WHEN NAME='';";
	cmd.insert(cmd.size() - 2, val["name"].asString());

	
}

void view_register::responce()
{

}
