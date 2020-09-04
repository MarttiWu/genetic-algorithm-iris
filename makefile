CC = g++ -Wall -std=c++11 
TARGET1 = main
TARGET2 = execute
TARGET3 = GA
TARGET4 = GetData

all: $(TARGET1).cpp $(TARGET2).cpp $(TARGET3).cpp $(TARGET4).cpp 
	$(CC) -c $(TARGET1).cpp $(TARGET2).cpp $(TARGET3).cpp  $(TARGET4).cpp
	$(CC) -o $(TARGET1) $(TARGET1).o $(TARGET2).o $(TARGET3).o $(TARGET4).o
	

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3) $(TARGET4)
	rm -f $(TARGET1).o $(TARGET2).o $(TARGET3).o $(TARGET4).o