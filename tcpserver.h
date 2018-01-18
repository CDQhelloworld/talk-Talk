#pragma once
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<vector>
#include<map>
using namespace std;

typedef class Tcpserver
{
	public:
		Tcpserver(char *ip,unsigned short port,int pth_num);
		~Tcpserver(){}
		void run();
		void create_socket_pair();
		void create_pth(int pth_num);

	private:
		struct event_base* _base;//libevent
		int _listen_fd;//listenfd
		int _pth_num;//线程个数
		map<unsigned,unsigned> _pth_num_map;//线程监听数量的map表
        typedef struct myPair
        {
            int sockfd[2];
            //myPair(int fd[2]):sockfd[0](fd[0]),sockfd[1](fd[1]){}
            myPair(int fd[2])
            {
                sockfd[0] = fd[0];
                sockfd[1] = fd[1];
            }
        }pair,*pPair;
        vector<myPair> _socket_pair_base;
}tcpsever,*pTcpsever;
#endif // !TCPSERVER_H
