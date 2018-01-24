#include <iostream>
#include "view_exit.h"
#include <mysql/mysql.h>
using namespace std;

view_exit::view_exit(void *mpcon)
{
    _mpcon = (MYSQL *)mpcon;
}

void view_exit::process(Json::Value value, int cli_fd)
{
}

void view_exit::responce()
{
}
