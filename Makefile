AKiendrebeogo_Pr2: mytest.o swarm.o
	g++ mytest.o swarm.o -o AKiendrebeogo_Pr2

mytest.o: mytest.cpp swarm.h
	g++ -c mytest.cpp

graph.o: graph.cpp swarm.h
	g++ -c graph.cpp

clean:
	rm *.o AKiendrebeogo_Pr2
