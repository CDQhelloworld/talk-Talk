#include<iostream>
#include<errno.h>
#include<cstdlib>
#include"tcpserver.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<event.h>
#include<unistd.h>
#include<functional>
#include<algorithm>
#include<signal.h>
using namespace std;

int main(int argc,char **argv)
{
    signal(SIGPIPE,SIG_IGN);
    signal(SIGINT,SIG_IGN);

	if(argc < 4)
	{
        cout<<"ip,port,pth_num!!!"<<endl;
		cerr<<"arg not enough;errno:"<<errno<<endl;
		return 0;
	}

	//解析参数   ip   port   pth_num
	char *ip = argv[1];
    int port = atoi(argv[2]);
    int pth_num = atoi(argv[3]);
    
    cout<<"ip=";
    while(*ip != 0)
    {
        cout<<*ip;
        ip++;
    }
    cout<<endl;
    cout<<"port="<<port<<endl;
    cout<<"pth_num="<<pth_num<<endl;

	//构造服务器对象
	Tcpserver ser(argv[1],port,pth_num);

	//运行服务器
	ser.run();

	return 0;
}
