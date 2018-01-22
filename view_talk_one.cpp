#include <iostream>
#include "view_talk_one.h"
#include <mysql/mysql.h>
using namespace std;

view_talk_one::view_talk_one(void *mpcon)
{
    _mpcon = (MYSQL *)mpcon;
}
