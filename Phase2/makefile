CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c 

main.out: main.o Manager.o User.o Publisher.o Customer.o Film.o Comment.o Exception.o Admin.o 
	$(CC) main.o Manager.o User.o Publisher.o Customer.o Film.o Comment.o Exception.o Admin.o $(FLAGS) -o main.out

main.o: main.cpp Manager.h
	$(CC) $(COMPILE_FLAGS) main.cpp

Manager.o: Manager.cpp Manager.h 
	$(CC) $(COMPILE_FLAGS) Manager.cpp

Exception.o: Exception.h Exception.cpp
	$(CC) $(COMPILE_FLAGS) Exception.cpp

Comment.o: Comment.h Comment.cpp
	$(CC) $(COMPILE_FLAGS) Comment.cpp

Film.o: Film.h Film.cpp Comment.h
	$(CC) $(COMPILE_FLAGS) Film.cpp

Customer.o: Customer.h Customer.cpp User.h
	$(CC) $(COMPILE_FLAGS) Customer.cpp

Publisher.o: Publisher.h Publisher.cpp  User.h Film.h Customer.h
	$(CC) $(COMPILE_FLAGS) Publisher.cpp

User.o: User.h User.cpp Film.h Exception.h
	$(CC) $(COMPILE_FLAGS) User.cpp

Admin.o: User.h Admin.h Admin.cpp
	$(CC) $(COMPILE_FLAGS) Admin.cpp

.PHONY: clean

clean:
	rm *.o