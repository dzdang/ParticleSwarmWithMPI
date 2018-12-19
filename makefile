SHELL = /bin/sh

CXX = g++

#compiler flags:
CFLAGS = -std=c++11 -g -Wall
# SRC_DIR = ./src/
# INCLUDE_DIR = ./include/
SRC_DIR = ./
INCLUDE_DIR = ./

objects = particle.o swarm.o main.o

executable_name = pso

default: neural_net


# all: graph.o neural_net.o  main.o
# 	$(CXX) $(CFLAGS) -o all graph.o neural_net.o main.o 

all: $(objects)
	$(CXX) $(CFLAGS) -o all $(objects)
	mkdir -p bin
	mv all bin/$(executable_name)

particle.o: $(SRC_DIR)particle.cpp $(INCLUDE_DIR)particle.h
	$(CXX) $(CFLAGS) -c $(SRC_DIR)particle.cpp

swarm.o: $(SRC_DIR)swarm.cpp $(INCLUDE_DIR)swarm.h
	$(CXX) $(CFLAGS) -c $(SRC_DIR)swarm.cpp

main.o: $(SRC_DIR)main.cpp
	$(CXX) $(CFLAGS) -c $(SRC_DIR)main.cpp


clean:
	rm bin/$(executable_name) $(objects) 
