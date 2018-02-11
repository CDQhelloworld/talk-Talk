#pragma once
#ifndef REDIS_H

#include<hiredis/hiredis.h>
#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string>
using namespace std;

typedef class Redis
{
    public:
        string _ip;
        Redis(){}
        ~Redis()
        {
            this->_connect = NULL;
            this->_reply = NULL;            
        }

        bool connect(string ip)
        {
            this->_connect = redisConnect(ip.c_str(), 6379);
            if(this->_connect && this->_connect->err)
            {
                cout << "redis connect fail; errno:" << this->_connect->errstr << endl;
                return false;
            }
            return true;
        }

        //获取数据
        string get(string key)
        {
            this->_reply = (redisReply *)redisCommand(this->_connect,"GET %s",key.c_str());
            if(REDIS_REPLY_NIL == this->_reply->type)//判断键值是否存在
            {
                cout << "without key=" << key << endl;
                return "Without this key-value!";
            }

            string str = this->_reply->str;
            freeReplyObject(this->_reply);
            return str;
        }

        //储存数据
        void set(string key, string value)
        {
            redisCommand(this->_connect,"SET %s %s",key.c_str(),value.c_str());
        }

        //删除key储存的值
        void del(string key)
        {
            redisCommand(this->_connect,"DEL %s",key.c_str());
        }
    private:
        redisContext *_connect;
        redisReply *_reply;
}redis,*pRedis;

#endif 
