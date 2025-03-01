LIB_DIR = ../lib

CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = ../bin/git-list

# Src files
SRC = git-list.cpp 
SRC += $(LIB_DIR)/io/io.cpp
SRC += $(LIB_DIR)/gr/gr-lib.cpp
SRC += $(LIB_DIR)/gr/git-branch_meta.cpp


LIBS = -lgit2

CXXFLAGS += -I$(LIB_DIR)/ini/inih
CXXFLAGS += -I$(LIB_DIR)/gr
CXXFLAGS += -I$(LIB_DIR)/io

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)


clean:
	rm -f $(TARGET) $(OBJS)