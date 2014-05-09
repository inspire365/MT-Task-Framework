
CC = gcc
CXX = g++
CC32 = gcc

CXXFLAGS = -Wall -D__STDC_LIMIT_MACROS -D_REENTRANT -Wl,-rpath,

COMMON_INC=../common

INCLUDE = -I$(COMMON_INC)

APP_SRC = main.cpp \
	exampletask.cpp \
	$(COMMON_INC)/simplelock.cpp \
	$(COMMON_INC)/threadif.cpp \
	$(COMMON_INC)/sem.cpp \
	$(COMMON_INC)/taskthread.cpp \
	$(COMMON_INC)/lockfreequeue.cpp \
	$(COMMON_INC)/taskqueue.cpp \
	$(COMMON_INC)/taskthreadmgr.cpp

APP_OBJ = $(APP_SRC:.cpp=.o)

.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

PROGRAM = app_task
all: app_task

app_task:  $(APP_OBJ) $@
	$(CXX) -o $@ $(LINK_CXXFLAG) $(INCLUDE) $(APP_OBJ) \
	-lpthread

clean:
	$(RM) -r $(PROGRAM) 
	rm -f *.o
	rm -f ../common/*.o

