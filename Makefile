# Prepare the dev env by getting compile_commands.json from bear by
# running something like `bear -- make br8051ah`.
CC = clang
# CFLAGS = -Wall -Wno-unknown-pragmas -Wextra -Wno-pragmas -O2 -ftree-vectorize -I./src/
CFLAGS = -fsanitize=address -pg -Wall -Wno-unknown-pragmas -Wextra -Wno-pragmas -pedantic -O2 -ftree-vectorize -I./src/
# '-pedantic' gives "binary constants are a C2X feature or GCC extension",
# will be use later when binary constants are changed to hex
# '-pg' for generating gmon.out for gprof
# '-fsanitize=address' for detecting memory errors, valgrind alternative

# Build shared components
SRC_SH = src/shared/compiler
SRC_SH2 = src/shared/rtos
BUILD_SH = build/shared/compiler
BUILD_SH2 = build/shared/rtos
OBJ = $(BUILD_SH2)/scheduler.o

$(BUILD_SH2)/scheduler.o: $(SRC_SH2)/scheduler.c $(SRC_SH2)/scheduler.h
	$(CC) $(CFLAGS) -c $(SRC_SH2)/scheduler.c -o $(BUILD_SH2)/scheduler.o


# Build Cortex A-53
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


# Build 8051AH
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
	mkdir -p build/shared
	mkdir -p build/cortex_a53
	mkdir -p build/8051ah
	mkdir -p build/test/cortex_a53
	mkdir -p build/test/8051ah

gprof:
	gprof build/main
