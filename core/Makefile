LIBS = -L/usr/local/lib -llua -levent -lpthread -lhiredis -ldl
LINC = -I/usr/local/include 

OBJS = main.cpp enet.cpp luas.cpp hall.cpp hredis.cpp
TARGET = hall

$(TARGET): $(OBJS)
	g++ $(OBJS) -o $(TARGET) $(LINC) $(LIBS) 