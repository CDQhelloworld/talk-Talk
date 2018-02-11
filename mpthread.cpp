#include "mpthread.h"
#include <iostream>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
using namespace std;

static void Menu()
{
    cout<<"-----------------------------------"<<endl;
    cout<<"|            1.register           |"<<endl;
    cout<<"|            2.login              |"<<endl;
    cout<<"|            3.talk_one           |"<<endl;
    cout<<"|            4.exit               |"<<endl;
    cout<<"|            5.clear cache        |"<<endl;
    cout<<"-----------------------------------"<<endl;
}

static void *pth_fun(void *arg)
{
    int sockfd = (int)arg;
    char buff[1024];
    while(1)
    {
        memset(buff,0,sizeof(buff)/sizeof(buff[0]));
        if((recv(sockfd,buff,sizeof(buff)/sizeof(buff[0]),0)) > 0)
        {
            cout<<buff<<endl;
            if(strcmp(buff, "退出成功") == 0)
            {
                close(sockfd);
                exit(1);
            }
            Menu();
            cout<<"Input cmd"<<endl;
        }
    }
}

Mpthread::Mpthread(int sockfd)
{
    pthread_t id;

    if(pthread_create(&id,NULL,pth_fun,(void *)sockfd) != 0)
    {
        cerr<<"pthread_create fail; errno:"<<errno<<endl;
        return;
    }
}

Mpthread::~Mpthread()
{
}
