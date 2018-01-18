#pragma once
#ifndef MPTHREAD_H
#define MPTHREAD_H

#include<map>
#include<iostream>
using namespace std;

class mpthread
{
public:
	mpthread(int sock_1);
	~mpthread();

private:
	int sock_1;//sockpair1
	struct event_base *_base;
	map<int, struct event*> _map;
};

#endif