#include <iostream>
#include "view_exit.h"
#include <mysql/mysql.h>
using namespace std;

view_exit::view_exit(void *mpcon)
{
    _mpcon = (MYSQL *)mpcon;
}
