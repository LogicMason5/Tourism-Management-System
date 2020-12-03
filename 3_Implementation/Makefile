# Name of the project
PROJECT_NAME = Tourism_Management_system

# Output directory
BUILD = build

# All source code files
SRC = main.c\
src/Tourism_management_system.c\

# All test source files
TEST_SRC = src/Tourism_mangement_system.c\
test/test_Tourism_management_system.c

TEST_OUTPUT = $(BUILD)/Test_$(PROJECT_NAME).out

# All include folders with header files
INC	= -Iinc

PROJECT_OUTPUT = $(BUILD)/$(PROJECT_NAME).out

# Document files
DOCUMENTATION_OUTPUT = documentation/html

# Default target built
$(PROJECT_NAME):all

# Run the target even if the matching name exists
.PHONY: run clean test  doc all

all: $(SRC) $(BUILD)
	gcc $(SRC) $(INC) -o $(final).out -lm

# Call `make run` to run the application
run:$(PROJECT_NAME)
	./$(final).out

# Document the code using Doxygen
doc:
	make -C ./documentation

# Build and run the unit tests
test:$(BUILD)
	gcc $(TEST_SRC) $(INC) -o $(TEST_OUTPUT) -lcunit -lm
	./$(TEST_OUTPUT)

# Remove all the built files, invoke by `make clean`
clean:
	rm -rf $(BUILD) $(DOCUMENTATION_OUTPUT)

# Create new build folder if not present
$(BUILD):
	mkdir build

