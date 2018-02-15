#include <iostream>
#include "view_talk_one.h"
#include <mysql/mysql.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <json/json.h>
#include <stdlib.h>
using namespace std;

view_talk_one::view_talk_one(void *mpcon)
{
    _mpcon = (MYSQL *)mpcon;
}

void view_talk_one::process(Json::Value val, int cli_fd)
{
    _cli_fd = cli_fd;

    MYSQL *mpcon = _mpcon;
    MYSQL_RES *mp_res;
    MYSQL_ROW mp_row;

    if(mysql_select_db(mpcon, "talk"))
    {
        cerr<<"select fail; errno:"<<errno<<endl;
        return;
    }

    //查询online表，如果有则发送，如果没有则加入到离线表中
    string cmd = "SELECT * FROM online WHERE name='';";
    cmd.insert(cmd.size()-2, val["sendto"].asString().c_str());
    if(mysql_real_query(mpcon, cmd.c_str(), cmd.size()))
    {
        cerr<<"0 query fail; errno"<<errno<<endl;
        return;
    }
    
    mp_res = mysql_store_result(mpcon);
    mp_row = mysql_fetch_row(mp_res);
    if(mp_row == 0)
    {
        //加入到离线表之中
        cmd = "INSERT INTO offline VALUE('','');";
        cmd.insert(cmd.size()-6, val["sendto"].asString().c_str());
        cmd.insert(cmd.size()-3, val["message"].asString().c_str());
        if(mysql_real_query(mpcon, cmd.c_str(), cmd.size()))
        {
            cerr<<"0 query fail; errno"<<errno<<endl;
            return;
        }
        _flag = true;
    }
    else
    {
        unsigned len = val["message"].asString().size();
        send(atoi(mp_row[0]), &len, sizeof(unsigned), 0);
        if((send(atoi(mp_row[0]), val["message"].asString().c_str(), val["message"].asString().size(), 0)) < 0)
            _flag = false;
        else
            _flag = true;
    }
}

void view_talk_one::responce()
{
    if(_flag)
    {
        char buff[] = "发送成功";
        unsigned len = sizeof(buff) / sizeof(buff[0]);
        send(_cli_fd, &len, sizeof(unsigned), 0);
        send(_cli_fd, buff, strlen(buff), 0);
    }
    else
    {
        char buff[] = "发送失败，请稍后重试";
        unsigned len = sizeof(buff) / sizeof(buff[0]);
        send(_cli_fd, &len, sizeof(unsigned), 0);
        send(_cli_fd, buff, strlen(buff), 0);
    }
}
