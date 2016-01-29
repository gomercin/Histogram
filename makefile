CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp ErrorLoggerCls.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=histogram
TEST_EXEC=histogram_test
TEST_SOURCES=TestMain.cpp ErrorLoggerCls.cpp
TEST_OBJECTS=$(TEST_SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	
test: $(TEST_SOURCES) $(TEST_EXEC)
	
$(TEST_EXEC): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS) -o $@
	
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(TEST_EXEC) $(TEST_OBJECTS)