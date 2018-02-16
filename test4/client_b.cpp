#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include"public.h"
#include<stdlib.h>
#include<json/json.h>
using namespace std;

int SockCreate()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        cerr << "sock create fail; errno:" << errno << endl;
        exit(1);
    }

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(6000);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    cout << "client fd=" << sockfd << "\tport=" << saddr.sin_port << "\tip=" << saddr.sin_addr.s_addr << endl;
    int res = connect(sockfd, (struct sockaddr*)&saddr,sizeof(saddr));
    if(res == -1)
    {
        cerr << "sockfd connect fail; errno:" << errno << endl;
        exit(1);
    }

    return sockfd;
}

bool Login(int sockfd)
{
    bool rt = false;
    Json::Value val;
    val["type"] = MSG_TYPE_LOGIN;
    val["name"] = "dcq";
    val["pw"] = "123";
    unsigned len = val.toStyledString().size();
    send(sockfd, &len, sizeof(unsigned), 0);
    send(sockfd, val.toStyledString().c_str(), val.toStyledString().size(), 0);
    rt = true;
    return rt;
}

bool Talk(int sockfd)
{
    bool rt = false;
    Json::Value val;
    val["type"] = MSG_TYPE_TALK_ONE;
    val["message"] = "b";
    //val["sendfrom"] = "dcq";
    val["sendto"] = "cdq";
    unsigned len = val.toStyledString().size();
    send(sockfd, &len, sizeof(unsigned), 0);
    send(sockfd, val.toStyledString().c_str(), val.toStyledString().size(), 0);
    rt = true;
    return rt;
}

bool Exit(int sockfd)
{
    bool rt = false;
    Json::Value val;
    val["type"] = MSG_TYPE_EXIT;
    val["name"] = "dcq";
    unsigned len = val.toStyledString().size();
    send(sockfd, &len, sizeof(unsigned), 0);
    send(sockfd, val.toStyledString().c_str(), val.toStyledString().size(), 0);
    rt = true;
    return rt;
}

void *CallBack(void *arg)
{
    int sockfd = (int)arg;
    char buff[256];
    while(1)
    {
        recv(sockfd, buff, 256, 0);
    }
}

int main()
{
    int sockfd = SockCreate();
    
    cout << "login:" << Login(sockfd) << endl;

    pthread_t id;
    if(pthread_create(&id, NULL, CallBack, (void *)sockfd) != 0)
    {
        cerr << "pthread fail;" << endl;
    }

    sleep(10);

    for(int i = 0; i < 100000; i++)
    {
        cout << "Talk:" << i << "   " << Talk(sockfd) << endl;
    }
    
    cout << "send 100000 messages ok!" << endl;

    cout << "exit?" << endl;
    getchar();
    Exit(sockfd);
    close(sockfd);
    return 0;
}
