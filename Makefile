TRG_DIR = ./bin
SRC_DIR = ./src
LIB_DIR = ../../vendor
INC_DIR = ../../includes
TRG_PKG = ./package/git-list/usr/bin/git-list
TRG_PTH = ../../build/debian/arm64/bin/git-list

#
# BUILD_MODE
# 
# Available options are DEBUG, RELEASE
#
BUILD_MODE = DEBUG 


# check to see if we are pointing to correct location
$(info )
$(info  -- Paths -- )
$(info )
$(info TRG_DIR: $(TRG_DIR))
$(info SRC_DIR: $(SRC_DIR))
$(info LIB_DIR: $(LIB_DIR))
$(info INC_DIR: $(INC_DIR))

CXX = g++
CXXFLAGS = -Wall -std=c++20

TARGET = $(TRG_DIR)/git-list

# Src files
SRC = $(SRC_DIR)/git-list.cpp 

SRC += $(INC_DIR)/io/io.cpp
SRC += $(INC_DIR)/gr/gr-cli-options.cpp
SRC += $(INC_DIR)/gr/git-repo-state.cpp


LIBS = -lgit2

#
# Includes
#
CXXFLAGS += -I$(LIB_DIR)/benhoyt/inih
CXXFLAGS += -I$(INC_DIR)/gr
CXXFLAGS += -I$(INC_DIR)/io

#
# Build Mode
#
CXXFLAGS += -D$(BUILD_MODE)


all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)
	cp $(TARGET) $(TRG_PKG)
	cp $(TARGET) $(TRG_PTH)
	dpkg-deb --build ./package/git-list/
	@echo ""
	@echo Build complete "git-list" \;\)
	@echo ""
clean:
	rm -f $(TARGET) $(OBJS) $(TRG_PKG)
	rm -f ./package/git-list.deb