#include <iostream>
#include "view_talk_one.h"
#include <mysql/mysql.h>
using namespace std;

view_talk_one::view_talk_one(void *mpcon)
{
    _mpcon = (MYSQL *)mpcon;
}

void view_talk_one::process(Json::Value value, int cli_fd)
{
}

void view_talk_one::responce()
{
}
