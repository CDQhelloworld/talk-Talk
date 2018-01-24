cli_main : main.o tcpclient.o
	g++ -o cli_main main.o tcpclient.o -ljson

main.o : main.cpp tcpclient.cpp
	g++ -c main.cpp tcpclient.cpp -ljson
tcpclient.o : tcpclient.cpp
	g++ -c tcpclient.cpp -ljson

clean :
	rm -f *.o cli_main
