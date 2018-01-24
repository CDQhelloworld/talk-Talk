#include<iostream>
#include<cstdlib>
#include"tcpclient.h"
using namespace std;

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		cerr << "arg is not enough! (ip,port)" << endl;
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
