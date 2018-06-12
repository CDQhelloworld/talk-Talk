server_main : main.o tcpserver.o mpthread.o control.o view_login.o view_register.o view_exit.o view_talk_one.o
	g++ -o server_main main.o tcpserver.o mpthread.o control.o view_login.o view_register.o view_exit.o view_talk_one.o -levent -ljson -lpthread -lmysqlclient -lhiredis -g

main.o : main.cpp
	g++ -c main.cpp -g 
tcpserver.o : tcpserver.cpp
	g++ -c tcpserver.cpp -levent -g
mpthread.o : mpthread.cpp
	g++ -c mpthread.cpp -levent -g 
control.o : control.cpp view_login.cpp view_exit.cpp view_talk_one.cpp view_register.cpp
	g++ -c control.cpp view_login.cpp view_exit.cpp view_talk_one.cpp view_register.cpp -lpthread -lhiredis -g
view_login.o : view_login.cpp
	g++ -c view_login.cpp -lmysqlclient -lpthread -lhiredis -g
view_register.o : view_register.cpp
	g++ -c view_register.cpp -lmysqlclient -lpthread -lhiredis -g
view_exit.o : view_exit.cpp 
	g++ -c view_exit.cpp -lmysqlclient -lpthread -lhiredis -g
view_talk_one.o : view_talk_one.cpp 
	g++ -c view_talk_one.cpp -lmysqlclient -lpthread -lhiredis -g

<<<<<<< HEAD
clean :
	rm server_main *.o
=======
clean_obj:
	rm -f *.o
clean:
	rm -f *.o client_main
>>>>>>> origin/client1.0
