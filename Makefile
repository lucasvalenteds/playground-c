COMPILER = gcc
COMPILER_FLAGS = -c -Wall

LIBRARIES = -lcheck -lsubunit -lrt -lm -lpthread

TESTS = language stdlib
TEST_FILES = $(addsuffix .c, $(addprefix test_, $(TESTS)))
TEST_DIR = $(addprefix tests/, $(TEST_FILES))

MAIN = main
MAIN_FILE = $(addsuffix .c, $(MAIN))
MAIN_OBJ = $(addsuffix .o, $(MAIN))
MAIN_BIN = $(addprefix bin_, $(MAIN))

default: compile test clean

compile:
	@$(COMPILER) $(COMPILER_FLAGS) $(MAIN_FILE) $(TEST_DIR)

test:
	@$(COMPILER) $(MAIN_OBJ) $(LIBRARIES) -o $(MAIN_BIN)
	@./$(MAIN_BIN)

clean:
	@rm $(MAIN_BIN) *.o
