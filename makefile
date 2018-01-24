cli_main : main.o tcpclient.o
	gcc -o cli_main main.o tcpclient.o -ljson

main.o : main.cpp tcpclient.cpp
	gcc -c main.cpp tcpclient.cpp -ljson
tcpclient.o : tcpclient.cpp
	gcc -c tcpclient.cpp -ljson

clean :
	rm -f *.o cli_main
