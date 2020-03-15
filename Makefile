CPP=g++
CFLAGS=-g -Wall
LDFLAGS=
RM=rm -rf

SRCS=$(wildcard *.cpp)
HDRS=$(wildcard *.h)
OBJS=$(SRCS:.cpp=.o)
EXEC=SLIDER_PUZZLE

default: $(EXEC)

$(EXEC): $(OBJS) $(HDRS)
	$(CPP) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.cpp $(HDRS)
	$(CPP) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) $(EXEC)

