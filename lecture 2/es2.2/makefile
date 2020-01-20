
make: main.o random.o 
	g++ main.o random.o  -o main.x 

main.o: main.cpp  main.h random.h 
	g++ -c main.cpp  



clean: rm *.o
  
random.o:  random.cpp random.h 
	g++ -c random.cpp


