#include<iostream>
#include<errno.h>
#include<cassert>
#include<map>
#include"tcpserver.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<cstdlib>
#include<unistd.h>
#include<event.h>
#include<memory.h>
using namespace std;

Tcpsever::Tcpsever(char *ip,unsigned short port,int pth_num):_pth_num(pth_num)
{
	//创建服务器
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
    assert(-1 != sockfd);

    struct sockaddr_in saddr;
    memset(&(saddr),0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = inet_addr(ip);

    int res = bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
    assert(-1 != res);

    listen(sockfd,5);


	_listen_fd = sockfd;

	//初始化libevent
	_base = event_init();
}

void Tcpsever::run()
{
	//创建socketpair
	create_socket_pair();

	//启动线程
//	create_pth();

	//将监听套接子libevent
	

	//循环监听
}



void sock_0_cb(int fd,short event,void* arg)
{
	//强转参数
    map<int,int> *p_pth_num_map = (map<int,int> *)arg;	

	//recv   当前对应线程的监听量num
    unsigned num = -1;
    recv(fd,&num,sizeof(unsigned),0);

	//更新到map表
	(*p_pth_num_map)[fd] = num;
}

void Tcpsever::create_socket_pair()
{
	//申请
	for(int i = 0; i < _pth_num;i++)
	{
		//socketpair(int [2])
        int sock_child[2] = {0};
        if(-1 == socketpair(AF_UNIX,SOCK_STREAM,0,sock_child))
        {
            cerr<<"creat_socket_pair::socketpair error:"<<errno<<endl;
            exit(0);
        }

		//_socket_pair_base.push_back()
        _socket_pair_base.push_back(pair(sock_child));

		//_pth_num_map.push_back(make_pair(socketpair0,0))
        _pth_num_map.insert(make_pair(sock_child[0],0));

		//将socketpair0端加入到libevent
		struct event* ev_sock_child = event_new(_base,sock_child[0],EV_READ|EV_PERSIST,sock_0_cb,&_pth_num_map);
		event_add(ev_sock_child,NULL);

		//启动循环监听  event_dispatch();
        event_base_dispatch(_base);
	}
}
