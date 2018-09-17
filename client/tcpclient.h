#pragma once
#pragma execution_character_set("utf-8")
#ifndef TCPCLIENT_H
#define TCPCLIENT

#include <string>
#include "mpthread.h"
using namespace std;

typedef class Tcpclient
{
public:
	Tcpclient(char *ip, int port);
	~Tcpclient();
	void run();
private:
	string _cmd;
	int _sockfd;
    pMpthread _pth;
}tcpclient,*pTcpclient;



#endif // !TCPCLIENT_H
