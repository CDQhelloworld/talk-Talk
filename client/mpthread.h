#pragma once
#ifndef MPTHREAD_H
#define MPTHREAD_H

typedef class Mpthread
{
    public:
        Mpthread(int sockfd);
        ~Mpthread();
    private:
        int _sockfd;
}mpthread,*pMpthread;

#endif
