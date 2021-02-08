CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(BUILD_DIR)/Manager.o: examples/Manager.cpp examples/Manager.h utils/response.hpp
	 $(CC) $(CF) -c examples/Manager.cpp -o $(BUILD_DIR)/Manager.o

$(BUILD_DIR)/Comment.o: examples/Comment.cpp examples/Comment.h
	$(CC) $(CF) -c examples/Comment.cpp -o $(BUILD_DIR)/Comment.o

$(BUILD_DIR)/Film.o: examples/Film.h examples/Film.cpp
	$(CC) $(CF) -c examples/Film.cpp -o $(BUILD_DIR)/Film.o

$(BUILD_DIR)/Customer.o: examples/Customer.h examples/Customer.cpp examples/User.h
	$(CC) $(CF) -c examples/Customer.cpp -o $(BUILD_DIR)/Customer.o

$(BUILD_DIR)/Publisher.o: examples/Publisher.h examples/Publisher.cpp examples/User.h examples/Film.h examples/Customer.h
	$(CC) $(CF) -c examples/Publisher.cpp -o $(BUILD_DIR)/Publisher.o

$(BUILD_DIR)/User.o: examples/User.h examples/User.cpp examples/Film.h examples/Exception.h
	$(CC) $(CF) -c examples/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Admin.o: examples/User.h examples/Admin.h examples/Admin.cpp
	$(CC) $(CF) -c examples/Admin.cpp -o $(BUILD_DIR)/Admin.o

$(BUILD_DIR)/Exception.o: examples/Exception.h examples/Exception.cpp
	$(CC) $(CF) -c examples/Exception.cpp -o $(BUILD_DIR)/Exception.o

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp examples/Manager.h utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/Manager.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Film.o $(BUILD_DIR)/Customer.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Admin.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Manager.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Film.o $(BUILD_DIR)/Customer.o $(BUILD_DIR)/Publisher.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Admin.o $(BUILD_DIR)/Exception.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
