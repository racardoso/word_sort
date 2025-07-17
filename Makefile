CC = gcc
CFLAGS = -Wall -Wextra -g -I./
TEST_LIBS = -lcheck -lm -pthread
SRC_DIR = .
TEST_DIR = tests
BUILD_DIR = build

# Create a build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/word_sort.o: $(SRC_DIR)/word_sort.c $(SRC_DIR)/word_sort.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_word_sort.o: $(TEST_DIR)/test_word_sort.c $(SRC_DIR)/word_sort.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test_word_sort: $(BUILD_DIR)/word_sort.o $(BUILD_DIR)/test_word_sort.o
	$(CC) $(CFLAGS) $^ -o $@ $(TEST_LIBS)

test: $(BUILD_DIR)/test_word_sort
	$(BUILD_DIR)/test_word_sort

clean:
	rm -rf $(BUILD_DIR)