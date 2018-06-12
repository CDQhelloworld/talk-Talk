#include<iostream>
#include<errno.h>
#include<cassert>
#include<map>
#include"tcpserver.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<pthread.h>
#include"mpthread.h"
#include<cstdlib>
#include<unistd.h>
#include<event.h>
#include<memory.h>
using namespace std;

Tcpserver::Tcpserver(char *ip,int port,int pth_num):_pth_num(pth_num),_ip(ip),_port(port)
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
    if(res == -1)
    {
        cerr<<"bind is error! errno:"<<errno<<endl;
        exit(1);
    }

    listen(sockfd,5);

    cout << "server port=" << ntohs(saddr.sin_port) << "        " << "server ip=" << inet_ntoa(saddr.sin_addr) << endl;

	_listen_fd = sockfd;

	//初始化libevent
	_base = event_init();
}

void sock_fd_cb(int fd, short event, void *arg)
{
	//拿到客户端套接字
	struct sockaddr_in caddr;
	int len = sizeof(caddr);
	int cli_fd = accept(fd, (struct sockaddr *)&caddr, (socklen_t *)&len);

    cout << "client fd="<< cli_fd <<"        port=" << ntohs(caddr.sin_port) << "       ip=" << inet_ntoa(caddr.sin_addr) << endl;

	//调查map表拿最小访问量的子线程套接字
	pTcpsever mthis = (pTcpsever)arg;
	typedef map<unsigned, unsigned>::iterator iterator;
	iterator ser_mapit = mthis->_pth_num_map.begin();
	int minIndex = (*ser_mapit).first;
	int min = (*ser_mapit).second;
	++ser_mapit;  //少比较一次
	for(;ser_mapit != mthis->_pth_num_map.end(); ++ser_mapit)
	{
		if((*ser_mapit).second < min)
		{
			minIndex = (*ser_mapit).first;
			min = (*ser_mapit).second;
		}
	}

	//给子线程发送
	if(-1 == (send(minIndex, (char *)&cli_fd, sizeof(int), 0)))
	{
		cerr << "send cli_fd to pthread error:" << errno << endl;
	}
}

void Tcpserver::run()
{
	//创建socketpair
	create_socket_pair();

	//启动线程
	create_pth(_pth_num, _ip);

	//将监听套接子libevent
	struct event *ev_socketfd = event_new(_base, _listen_fd, EV_READ|EV_PERSIST, sock_fd_cb, this);
    event_add(ev_socketfd,NULL);

	//循环监听
	event_base_dispatch(_base);
}



void Tcpserver::create_pth(int pth_num, char *ip)
{
	for(int i = 0;i<pth_num;++i)
	{
	    new mpthread(((_socket_pair_base[i]).sockfd)[1], ip);
	}
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

void Tcpserver::create_socket_pair()
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
	}
}
