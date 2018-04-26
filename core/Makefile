LIBS = -L/usr/local/lib -llua -levent -lpthread -ldl
LINC = -I/usr/local/include 

OBJS = main.cpp enet.cpp luas.cpp hall.cpp 
TARGET = hall

$(TARGET): $(OBJS)
	g++ $(OBJS) -o hall $(LINC) $(LIBS) 