
make: main.o random.o econoph.o
	g++ main.o random.o econoph.o -o main.x 

main.o: main.cpp  random.h econoph.h
	g++ -c main.cpp  



clean: rm *.o
  
random.o:  random.cpp random.h 
	g++ -c random.cpp

econoph.o: econoph.cpp econoph.h random.h
	g++ -c econoph.cpp

