server_main : main.o tcpserver.o mpthread.o control.o view_login.o
	g++ -o server_main main.o tcpserver.o mpthread.o control.o view_login.o -levent -ljson -lpthread -lmysqlclient

main.o : main.cpp tcpserver.h
	g++ -c main.cpp
tcpserver.o : tcpserver.cpp tcpserver.h mpthread.h
	g++ -c tcpserver.cpp -levent
mpthread.o : mpthread.cpp mpthread.h
	g++ -c mpthread.cpp -levent
control.o : control.cpp control.h public.h view.h
	g++ -c control.cpp 
view_login.o : view_login.cpp view_login.h view.h
	g++ -c view_login.cpp

clean :
	rm server_main main.o tcpserver.o mpthread.o control.o view_login.o
