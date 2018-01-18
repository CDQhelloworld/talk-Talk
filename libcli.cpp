//客户端程序
#include<iostream>
#include<event.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
using namespace std;
int main()
{
	int fd = socket(AF_INET,SOCK_STREAM,0);
	if( -1 == fd)
	{
		cerr<<"fd creat fail;errno:"<<errno<<endl;
		return 0;
	}

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(-1 == connect(fd,(struct sockaddr*)&saddr,sizeof(saddr)))
	{
		cerr<<"connect fail;errno:"<<errno<<endl;
		return 0;
	}
//发送hello
	int i = 0;
	while(i < 2)
	{
		if(-1 == send(fd,"hello",6,0))
		{
			cerr<<"send fail;errno:"<<errno<<endl;
			return 0;
		}
	i++;
	}
//接收   输出 
	char buff[100] = {0};
	if(0 < recv(fd,buff,99,0))
	{
		cout<<buff<<endl;
		sleep(100);
	}
	return 0;
}

