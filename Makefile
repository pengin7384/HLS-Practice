CXX		= g++ -std=c++11
SRCS	= $(wildcard *.cpp)
OBJS 	= $(SRCS:.cpp=.o)
TARGET	= server
LIBS	= -pthread

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(SRCS) $(LIBS)

clean :
	rm -f $(TARGET)
	rm -f *.o
