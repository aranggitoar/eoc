build/cortex_a53/input.o: src/cortex_a53/input.c src/cortex_a53/input.h
	gcc -c src/cortex_a53/input.c -o build/cortex_a53/input.o

build/cortex_a53/register.o: src/cortex_a53/register.c src/cortex_a53/register.h
	gcc -c src/cortex_a53/register.c -o build/cortex_a53/register.o

rc: src/main.c build/cortex_a53/register.o build/cortex_a53/input.o
	gcc build/cortex_a53/input.o build/cortex_a53/register.o src/main.c -o build/main && build/main


build/8051ah/memory.o: src/8051ah/memory.c src/8051ah/memory.h
	gcc -c src/8051ah/memory.c -o build/8051ah/memory.o

build/8051ah/instruction.o: src/8051ah/instruction.c src/8051ah/instruction.h
	gcc -c src/8051ah/instruction.c -o build/8051ah/instruction.o

build/8051ah/8051ah.o: src/8051ah/8051ah.c src/8051ah/8051ah.h
	gcc -c src/8051ah/8051ah.c -o build/8051ah/8051ah.o

r8: src/main.c build/8051ah/8051ah.o build/8051ah/instruction.o build/8051ah/memory.o
	gcc build/8051ah/memory.o build/8051ah/instruction.o build/8051ah/8051ah.o src/main.c -o build/main && build/main

build/test/test_utils.o: test/test_utils.c test/test_utils.h
	gcc -c test/test_utils.c -o build/test/test_utils.o

test_r8_ins: test/8051ah/test_instruction.c build/test/test_utils.o build/8051ah/8051ah.o build/8051ah/instruction.o build/8051ah/memory.o
	gcc build/test/test_utils.o build/8051ah/memory.o build/8051ah/instruction.o build/8051ah/8051ah.o test/8051ah/test_instruction.c -o build/test/test_r8_instructions && build/test/test_r8_instructions


clean:
	rm -rf build/*
