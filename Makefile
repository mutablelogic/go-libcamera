CFLAGS += -Wall -Wextra $(shell pkg-config --cflags libcamera)
LDFLAGS += $(shell pkg-config --libs libcamera)
DEBUGFLAGS =
CXX = g++
CC = gcc
BUILD_DIR = build


SRCS=$(wildcard src/*.cc)
OBJS=$(subst .cc,.o,$(SRCS))

all: mkdir $(OBJS)
	$(CC) $(DEBUGFLAGS) -c $(CCFLAGS) $(CFLAGS) -I src -o $(BUILD_DIR)/main.o cmd/test/main.c
	$(CXX) $(DEBUGFLAGS) -o $(BUILD_DIR)/test $(BUILD_DIR)/*.o $(LDFLAGS) 

%.o: %.cc
	$(CXX) $(DEBUGFLAGS) $(CCFLAGS) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

mkdir:
	@install -d ${BUILD_DIR}

clean:
	@rm -f ${BUILD_DIR}/*.o