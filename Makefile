SRC_DIR = ./src
LIB_DIR = ../../vendor
INC_DIR = ../../includes

CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = ./bin/git-list

# Src files
SRC = $(SRC_DIR)/git-list.cpp 
SRC += $(INC_DIR)/io/io.cpp
SRC += $(INC_DIR)/gr/gr-lib.cpp
SRC += $(INC_DIR)/gr/git-branch_meta.cpp


LIBS = -lgit2

CXXFLAGS += -I$(LIB_DIR)/benhoyt/ini/inih
CXXFLAGS += -I$(INC_DIR)/gr
CXXFLAGS += -I$(INC_DIR)/io

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)


clean:
	rm -f $(TARGET) $(OBJS)