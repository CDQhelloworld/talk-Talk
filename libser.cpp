//�������˳���
#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<event.h>
#include<errno.h>
using namespace std;
//�ͻ����׽��ֻص�����
void cli_cb(int fd,short event,void *arg)
{
	struct event_base*lib_base = (struct event_base*)arg;

	char buff[100] = {0};
	if(0< recv(fd,buff,99,0))
	{
		cout<<buff<<endl;
		if(-1 == send(fd,"ok",3,0))
		{
			cerr<<"send fail;errno:"<<errno<<endl;
			return;
		}
	}
	else
	{
		close(fd);
		//event_free(struct event *);
	}
}

//�����׽��ֻص�����
void listen_cb(int fd,short event,void* arg)
{
	struct event_base* lib_base = (struct event_base*)arg;

	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	int cli_fd = accept(fd,(struct sockaddr*)&caddr,&len);
	if(-1 == cli_fd)
	{
		cerr<<"accept fail;errno:"<<errno<<endl;
		return;
	}

	//��clifd���뵽�¼��б�
	struct event* cli_event = event_new(lib_base,cli_fd,EV_READ|EV_PERSIST,cli_cb,lib_base);
	if(NULL == cli_event)
	{
		cerr<<"cli event creat fail;errno:"<<errno<<endl;
		return;
	}

	event_add(cli_event,NULL);
}

int main()
{
//��ʼ��libevent
	struct event_base *lib_base = event_base_new();

	int fd = socket(AF_INET,SOCK_STREAM,0);
	if(-1 == fd)
	{
		cerr<<"fd creat fail;errno:"<<errno<<endl;
		return 0;
	}	

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(6000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(-1 == bind(fd,(struct sockaddr*)&saddr,sizeof(saddr)))
	{
		cerr<<"bind fail;errno:"<<errno<<endl;
		return 0;
	}	

	if(-1 == listen(fd,20))
	{
		cerr<<"listen fail;errno:"<<errno<<endl;
		return 0;
	}

	//�������׽���    ��ӵ�libevent
	//�����¼�
	struct event* listen_event = event_new(lib_base,fd,EV_READ|EV_PERSIST,listen_cb,lib_base);
	if(NULL == listen_event)
	{
		cerr<<"event new fail;errno:"<<errno<<endl;
		return 0;
	}

	//���¼���ӵ��¼��б�
	event_add(listen_event,NULL);
	
	//ѭ������
	event_base_dispatch(lib_base);   //while(1){ epoll_wait();}
return 0;
}
