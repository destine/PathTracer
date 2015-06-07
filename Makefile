CC = g++

CFLAGS = -c -O2 -pthread -std=c++0x
LFLAGS = -O2 -pthread -std=c++0x

TARGET = build/as2

SRCS  := $(wildcard src/*.cpp) LodePNG/lodepng.cpp
OBJS  := $(SRCS:.cpp=.o)

RM = /bin/rm -rf

all: $(TARGET)

$(TARGET): $(OBJS) main.cpp
	$(CC) $(LFLAGS) $(OBJS) main.cpp -o $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

check:
	@$(CC) $(LFLAGS) $(OBJS) ./test/main.cpp -o ./test/test
	@echo "\n...test begin...\n"
	@./test/test input.txt
	@rm -f test/test
	@echo "...test end...\n"

clean: 
	$(RM) $(OBJS) $(TARGET) build/output.png
