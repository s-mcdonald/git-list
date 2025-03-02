TRG_DIR = ./bin
SRC_DIR = ./src
LIB_DIR = ../../vendor
INC_DIR = ../../includes


# check to see if we are pointing to correct location
$(info )
$(info  -- Paths -- )
$(info )
$(info TRG_DIR: $(TRG_DIR))
$(info SRC_DIR: $(SRC_DIR))
$(info LIB_DIR: $(LIB_DIR))
$(info INC_DIR: $(INC_DIR))

CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = $(TRG_DIR)/git-list

# Src files
SRC = $(SRC_DIR)/git-list.cpp 

SRC += $(INC_DIR)/io/io.cpp
SRC += $(INC_DIR)/gr/gr-lib.cpp
SRC += $(INC_DIR)/gr/git-branch_meta.cpp


LIBS = -lgit2

CXXFLAGS += -I$(LIB_DIR)/benhoyt/inih
CXXFLAGS += -I$(INC_DIR)/gr
CXXFLAGS += -I$(INC_DIR)/io

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)