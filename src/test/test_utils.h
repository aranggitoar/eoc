#ifndef TEST_UTILS_H_INCLUDED
#define TEST_UTILS_H_INCLUDED

#include <std.h>

void printf_header(char *file_name, int file_name_len, bool is_top);

void assert_equal_uint8(uint8_t a, uint8_t b, const char *func_name);
void assert_equal_uint16(uint16_t a, uint16_t b, const char *func_name);

#endif /* TEST_UTILS_H_INCLUDED */
