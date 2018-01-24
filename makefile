cli_main : main.o tcpclient.o
	g++ -o cli_main main.o tcpclient.o -ljson -g

main.o : main.cpp tcpclient.cpp
	g++ -c main.cpp tcpclient.cpp -ljson -g 
tcpclient.o : tcpclient.cpp
	g++ -c tcpclient.cpp -ljson -g

clean :
	rm -f *.o cli_main
