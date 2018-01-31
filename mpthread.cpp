#include<iostream>
#include"mpthread.h"
#include<pthread.h>
#include<errno.h>
#include<event.h>
#include<sys/socket.h>
#include<map>
#include"control.h"
using namespace std;

void *pth_run(void *arg);

mpthread::mpthread(int sock_1, char *ip, int port)
{
	_sock_1 = sock_1;
	
    //生成控制台
    _control = new control(ip, port);

	//启动子线程
    pthread_t id;
    if((pthread_create(&id,NULL,pth_run,this)) != 0)
    {
        cerr<<"pthread_create error:"<<errno<<endl;
        return;
    }
}

void cli_cb(int fd,short event,void* arg)
{
	Pmpthread mthis = (Pmpthread)arg;
	//recv   ->buff
	char buff[1024] = {0};
	if((recv(fd, buff, sizeof(buff)/sizeof(buff[0]), 0)) > 0)
	{
		//buff->contral 
		mthis->_control->handle(buff, fd);
	}
    else
    {
        event_del(mthis->_event_map[fd]);
        typedef map<int,struct event *>::iterator iterator;
        iterator it = mthis->_event_map.find(fd);
        mthis->_event_map.erase(it);
        close(fd);
        cout<<"client fd="<<fd<<"已断开！"<<endl;
    }
	     
}



void sock_1_cb(int fd,short event,void *arg)
{
	//强转
	Pmpthread mthis = (Pmpthread)arg;

	//recv   cli_fd
    int cli_fd;
	recv(fd,&cli_fd,sizeof(int),0);

	//将cli_fd加入libevent  -》cli_cb()
	struct event* ev_cli = event_new(mthis->_base,cli_fd,EV_READ|EV_PERSIST,cli_cb,mthis);
    event_add(ev_cli,NULL);

	//将事件加入到_event_map
    mthis->_event_map.insert(make_pair(cli_fd,ev_cli));
    
	//send(fd,      _event_map.size(),)
	int mapsize = mthis->_event_map.size();
	send(mthis->_sock_1, &mapsize, sizeof(int), 0);
}


void *pth_run(void *arg)
{
	Pmpthread mthis = (Pmpthread)arg;

	//mthis->_base = event_base_new();
	mthis->_base = event_init();
	
	//将sock_1 加入到libevnet  ->sock_1_cb(  ,mthis, )
    struct event* ev_sock_1 = event_new(mthis->_base,mthis->_sock_1,EV_READ|EV_PERSIST,sock_1_cb,mthis);
	event_add(ev_sock_1,NULL);

	event_base_dispatch(mthis->_base);
}
