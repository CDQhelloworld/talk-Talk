#pragma once
#ifndef MPTHREAD_H
#define MPTHREAD_H

#include<map>

typedef class MPthread
{
	public:
		mpthread(int sock_1);
		~mpthread();

	private:
		int _sock_1;///socketpair1
		struct event_base* _base;//libevent
		map<int,struct event*> _event_map;//保存事件的map
		friend void *pth_run(void *arg);
		friend void sock_1_cb(int fd, short event, void *arg);
}Mpthread,*Pmpthread;



#endif 
