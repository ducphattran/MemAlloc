CC = gcc
CFLAGS = -Wall -g
TARGET = test_program
SRCS = memory.c test_program.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) test_case.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) sample_test_case.o test_sample

check-%: $(TARGET)
	@echo "Running test case $*"
	@./$(TARGET) $*
	@echo "Test case $* passed"
sample: $(OBJS) sample_test_case.o
	$(CC) $(CFLAGS) -o test_sample memory.o sample_test_case.o
