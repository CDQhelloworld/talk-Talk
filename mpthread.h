#ifndef MPTHREAD_H
#define MPTHREAD_H
class mpthread
{
	public:
		mpthread(int sock_1);
		~mpthread();

	private:
		int _sock_1;///socketpair1
		struct event_base* _base;//libevent
		map<int,struct event*> _event_map;//保存事件的map

}Mpthread,*Pmpthread;



#endif 
