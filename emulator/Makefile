# Prepare the dev env by getting compile_commands.json from bear by
# running something like `bear -- make br8051ah`.
# pedantic gives "binary constants are a C2X feature or GCC extension",
# will be use later when binary constants are changed to hex
# CFLAGS = -Wall -Wno-unknown-pragmas -Wextra -pedantic -Wno-pragmas -O2 -ftree-vectorize -I./src/
CC = gcc
CFLAGS = -Wall -Wno-unknown-pragmas -Wextra -Wno-pragmas -O2 -ftree-vectorize -I./src/
SRCT = src/test
BUILDT = build/test

SRC = src/cortex_a53
SRCT2 = src/test/cortex_a53
BUILD = build/cortex_a53
BUILDT2 = build/test/cortex_a53
OBJ = $(BUILD)/register.o $(BUILD)/input.o

$(BUILD)/input.o: $(SRC)/input.c $(SRC)/input.h
	mkdir -p build/cortex_a53
	$(CC) $(CFLAGS) -c $(SRC)/input.c -o $(BUILD)/input.o

$(BUILD)/register.o: $(SRC)/register.c $(SRC)/register.h
	$(CC) $(CFLAGS) -c $(SRC)/register.c -o $(BUILD)/register.o

brcortex_a53: src/main.c $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) src/main.c -o build/main && build/main


SRC = src/8051ah
SRCT2 = src/test/8051ah
BUILD = build/8051ah
BUILDT2 = build/test/8051ah
OBJ = $(BUILD)/memory.o $(BUILD)/instruction.o $(BUILD)/8051ah.o
OBJT = $(BUILDT)/test_utils.o $(BUILD)/memory.o $(BUILD)/instruction.o $(BUILD)/8051ah.o

$(BUILD)/memory.o: $(SRC)/memory.c $(SRC)/memory.h
	mkdir -p build/8051ah
	$(CC) $(CFLAGS) -c $(SRC)/memory.c -o $(BUILD)/memory.o

$(BUILD)/instruction.o: $(SRC)/instruction.c $(SRC)/instruction.h
	$(CC) $(CFLAGS) -c $(SRC)/instruction.c -o $(BUILD)/instruction.o

$(BUILD)/8051ah.o: $(SRC)/8051ah.c $(SRC)/8051ah.h
	$(CC) $(CFLAGS) -c $(SRC)/8051ah.c -o $(BUILD)/8051ah.o

br8051ah: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) src/main.c -o build/main && build/main

$(BUILDT)/test_utils.o: $(SRCT)/test_utils.c $(SRCT)/test_utils.h
	mkdir -p build/test/8051ah
	$(CC) $(CFLAGS) -c $(SRCT)/test_utils.c -o $(BUILDT)/test_utils.o

test_8051ah_ins: $(OBJT)
	$(CC) $(CFLAGS) $(OBJT) $(SRCT2)/test_instruction.c -o $(BUILDT2)/test_8051ah_ins && $(BUILDT2)/test_8051ah_ins


clean:
	rm -rf build/*
