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
#include"mpthread.h"
using namespace std;

extern int _fd;
extern string _name;

Tcpclient::Tcpclient(char *ip, int port)
{
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1)
        {
            cerr << "socket fail; errno:" << errno << endl;
        }

        _sockfd = sockfd;
        _fd = sockfd;
        struct sockaddr_in saddr;
        memset(&saddr, 0, sizeof(saddr));
        
        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(port);
        
        saddr.sin_addr.s_addr = inet_addr(ip);

        cout << "client ip=" << inet_ntoa(saddr.sin_addr) << "      " << "port=" << ntohs(saddr.sin_port) << endl;
        int res = connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
        if(res == -1)
        {
            cerr << "connect fail! errno:" << errno << endl;
            exit(1);
        }
        
        pMpthread _pth = new mpthread(sockfd);
}

Tcpclient::~Tcpclient()
{
    delete _pth;
}

static void Menu()
{
    cout<<"-----------------------------------"<<endl;
    cout<<"|            1.register           |"<<endl;
    cout<<"|            2.login              |"<<endl;
    cout<<"|            3.talk_one           |"<<endl;
    cout<<"|            4.exit               |"<<endl;
    cout<<"-----------------------------------"<<endl;
}

void Tcpclient::run()
{
    int cmd;
    Menu();
    cout <<"Input cmd" << endl;
    while(1)
    {
        cin >> cmd;

        switch(cmd)
        {
            case 2:
                {
                    if(_name.size() != 0)
                    {
                        cout << "当前已经有登录用户，请先退出" << endl;
                        break;
                    }

                    Json::Value val;
                    val["type"] = MSG_TYPE_LOGIN;
                    cout<<"Input your name:";
                    char buff[1024] = {0};
                    cin>>buff;
                    val["name"] = buff;
                    _name = buff;
                    cout<<"Input your password:";
                    memset(buff, 0, strlen(buff));
                    cin>>buff;
                    val["pw"] = buff; 
            
                    send(_sockfd, val.toStyledString().c_str(), strlen(val.toStyledString().c_str()), 0);
                    break;
                }
            case 1:
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
                    break;
                }
            case 4:
                {
                    if(_name.size() == 0)
                    {
                        cout << "当前没有登录用户，无法退出" << endl;
                        break;
                    }
                    Json::Value val;
                    val["type"] = MSG_TYPE_EXIT;
                    val["name"] = _name;
            
                    send(_sockfd, val.toStyledString().c_str(),val.toStyledString().size(), 0);
                    break;
                }
            case 3:
                {
                    if(_name.size() == 0)
                    {
                        cout << "当前没有登录用户，无法发送消息" << endl;
                        break;
                    }

                    Json::Value val;
                    val["type"] = MSG_TYPE_TALK_ONE;
                    val["sendfrom"] = _name;
                    char buff[1024] = {0};
                    string message = "[:]";
                    message.insert(1, _name.c_str());
                    cout<<"Input your message:";
                    cin>>buff;
                    message.insert(message.size()-1, buff);
                    val["message"] = message.c_str();
                cout << message <<endl;
                    memset(buff,0,strlen(buff));
                    cout<<"You want to send for:";
                    cin>>buff;
                    val["sendto"] = buff;

                    send(_sockfd, val.toStyledString().c_str(), val.toStyledString().size(), 0);
                    break;
                }
            default:break;
        }
        cin.clear();
        cin.ignore(1024,'\n');
    }
}
