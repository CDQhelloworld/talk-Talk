#include <iostream>
#include <mysql/mysql.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main()
{
    srand(time(0));
    MYSQL *mpcon = mysql_init((MYSQL *)0);
    MYSQL_RES *mp_res;
    MYSQL_ROW mp_row;

    if(!mysql_real_connect(mpcon,"127.0.0.1","root","970808",NULL,3306,NULL,0))
    {
        cout<<"sql connect fail; errno:"<<errno<<endl;
        return 0;
    }
    if(mysql_select_db(mpcon,"talk"))
    {
        cout<<"select fail; errno:"<<errno<<endl;
        return 0;
    }

    int name_pw;
    int i = 0;
    for(; i<100000; ++i)
    {
        string cmd = "INSERT INTO user VALUES('','');";
        name_pw = rand() % 1000;
        char buff[sizeof(int)] = {0};
        sprintf(buff, "%d", name_pw);
        cmd.insert(cmd.size()-6, buff);
        cmd.insert(cmd.size()-3, buff);
        if(mysql_real_query(mpcon, cmd.c_str(), cmd.size()))
        {
            cout<<"0 query fail; errno:"<<errno<<endl;
        }
    }
}
