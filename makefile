server_main : main.o tcpserver.o mpthread.o control.o view_login.o view_register.o view_exit.o view_talk_one.o
	g++ -o server_main main.o tcpserver.o mpthread.o control.o view_login.o view_register.o view_exit.o view_talk_one.o -levent -ljson -lpthread -lmysqlclient

main.o : main.cpp
	g++ -c main.cpp
tcpserver.o : tcpserver.cpp
	g++ -c tcpserver.cpp -levent
mpthread.o : mpthread.cpp
	g++ -c mpthread.cpp -levent
control.o : control.cpp view_login.cpp view_exit.cpp view_talk_one.cpp view_register.cpp
	g++ -c control.cpp view_login.cpp view_exit.cpp view_talk_one.cpp view_register.cpp
view_login.o : view_login.cpp
	g++ -c view_login.cpp
view_register.o : view_register.cpp
	g++ -c view_register.cpp
view_exit.o : view_exit.cpp 
	g++ -c view_exit.cpp
view_talk_one.o : view_talk_one.cpp 
	g++ -c view_talk_one.cpp

clean :
	rm server_main main.o tcpserver.o mpthread.o control.o view_login.o
