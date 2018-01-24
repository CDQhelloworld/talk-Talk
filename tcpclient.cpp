#pragma execution_character_set("utf-8") 
#include<iostream>
#include<errno.h>
#include<sys/socket.h>
#include<memory>
#include<cstdlib>
#include"tcpclient.h"
#include"public.h"
#include<arpa/inet.h>
#include<string.h>
#include<memory>
#include<json/json.h>
using namespace std;

Tcpclient::Tcpclient(char *ip, int port)
{
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1)
        {
            cerr << "socket fail; errno:" << errno << endl;
        }

        _sockfd = sockfd;
        struct sockaddr_in saddr;
        memset(&(saddr), 0, sizeof(saddr));
        
        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(port);
        saddr.sin_addr.s_addr = inet_addr(ip);
        int res = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
        if(res == -1)
        {
            cerr << "connect fail! errno:" << errno << endl;
            exit(1);
        }
}

Tcpclient::~Tcpclient(){}

static void Show(const char *buff)
{
    for(int i = 0; i < strlen(buff); ++i)
    {
        cout<<buff[i];
    }
}

void Tcpclient::run()
{
    char cmd[1024];
    while(1)
    {
        memset(cmd, 0, strlen(cmd));	
        cin >> cmd;

        if(strcmp(cmd, "login"))
        {
            Json::Value val;
            val["type"] = MSG_TYPE_LOGIN;
            cout<<"Input your name:";
            char buff[1024] = {0};
            cin>>buff;
            val["name"] = buff;
            cout<<"Input your password:";
            memset(buff, 0, strlen(buff));
            cin>>buff;
            val["pw"] = buff; 
            
            send(_sockfd, val.toStyledString().c_str(), strlen(val.toStyledString().c_str()), 0);
            char recvBuff[2048];
            while(0 < (recv(_sockfd, recvBuff, sizeof(recvBuff)/sizeof(recvBuff[0]), 0)))
            {
                Show(recvBuff);
            }

        }
        else if(strcmp(cmd, "rigister"))
        {
            Json::Value val;
            val["type"] = MSG_TYPE_REGISTER;
            cout<<"Input your name:";
            char buff[1024] = {0};
            cin>>buff;
            val["name"] = buff;
            cout<<"Input your password:";
            memset(buff, 0, strlen(buff));
            cin>>buff;
            val["pw"] = buff; 

            send(_sockfd, val.toStyledString().c_str(), strlen(val.toStyledString().c_str()), 0);
            char recvBuff[2048];
            while(0 < (recv(_sockfd, recvBuff, sizeof(recvBuff)/sizeof(recvBuff[0]), 0)))
            {
                Show(recvBuff);
            }
        }
    }
}
