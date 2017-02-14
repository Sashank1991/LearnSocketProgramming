CC = gcc
CXX = g++
CFLAGS = -O1
CXXFLAGS = -std=c++0x -O1 -Wall
PROB1 = 34_HW2_Q1_1
PROB2 = 34_HW2_Q1_2
PROB3 = 34_HW2_Q1_3
PROB4 = 34_HW2_Q1_4
PROB5 = 34_HW2_Q2
PROB6 = 34_HW2_Client
TARGET = $(PROB1) $(PROB2) $(PROB3) $(PROB4) $(PROB5) $(PROB6)

RM = rm -rf

.PHONY: all pre clean all clean

all: $(TARGET)

34_HW2_Q1_1: 34_HW2_Q1_1.c
	$(CC) $< -o $@

34_HW2_Q1_2: 34_HW2_Q1_2.c
	$(CC)  $< -o $@

34_HW2_Q1_3: 34_HW2_Q1_3.c
	$(CC) $< -o $@

34_HW2_Q1_4: 34_HW2_Q1_4.c
	$(CC) -pthread  $< -o $@

34_HW2_Q2: 34_HW2_Q2.c
	$(CC) $< -o $@

34_HW2_Client: 34_HW2_Client.c
	$(CC) $< -o $@

cleanall:
	$(RM) $(TARGET)
	
clean:
	$(RM) $(TARGET)
