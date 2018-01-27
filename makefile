client_main : main.o tcpclient.o mpthread.o
	g++ -o client_main main.o tcpclient.o mpthread.o  -ljson -lpthread -g

main.o : main.cpp tcpclient.cpp
	g++ -c main.cpp tcpclient.cpp -ljson -lpthread -g 
tcpclient.o : tcpclient.cpp mpthread.cpp
	g++ -c tcpclient.cpp mpthread.cpp -ljson -lpthread -g
mpthread.o : mpthread.cpp
	g++ -c mpthread.cpp -lpthread -g

clean :
	rm -f *.o cli_main
