#include<iostream>
#include<cstdlib>
#include"tcpclient.h"
#include<signal.h>
#include"public.h"
#include<json/json.h>
#include<sys/socket.h>
using namespace std;

int _fd = -1;
string _name;

void myexit(int sig)
{
    if(_fd == -1 || (_name.size() == 0))
    {
        cout << "Bye" << endl;
        exit(1);
    }

    Json::Value val;
    val["type"] = MSG_TYPE_EXIT;
    val["name"] = _name;
    send(_fd,val.toStyledString().c_str(),val.toStyledString().size(),0);
    cout << "Bye" << endl;
    exit(1);
}

int main(int argc, char **argv)
{
    signal(SIGINT,myexit);
	if(argc < 3)
	{
		cerr << "arg is not enough! (ip,port)" << endl;
        exit(1);
	}

	char *ip = argv[1];
	int port = atoi(argv[2]);

    int i = 0;
    for(; ip[i] != 0; ++i)
    {
        cout << ip[i];
    }
    cout << endl;
    cout << port << endl;

	tcpclient cli(ip, port);

	cli.run();

    return 0;
}
