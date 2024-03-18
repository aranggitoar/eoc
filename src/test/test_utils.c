#include <test/test_utils.h>

#define HEADER_SYMBOL "--------------------------------------------------"
#define BOLD "\e[1m"
#define BOLD_RED "\e[1;91m"
#define RED "\e[0;91m"
#define BOLD_YELLOW "\e[1;93m"
#define BOLD_GREEN "\e[1;92m"
#define GREEN "\e[0;92m"
#define RESET "\e[m"

void printf_header(char *file_name, int file_name_len, bool is_top)
{
  if (is_top) printf("\n%.*s\n", 8 + file_name_len, HEADER_SYMBOL);
  else printf("\n");
  printf("---" BOLD_YELLOW " %s " RESET "---\n", file_name);
  if (!is_top) printf("%.*s\n\n", 8 + file_name_len, HEADER_SYMBOL);
  else printf("\n");
}

void assert_equal_uint8(uint8_t a, uint8_t b, const char *func_name)
{
  if (a == b) printf(BOLD_GREEN "(PASS) %s\n" RESET, func_name);
  else printf(BOLD_RED "(FAIL) %s" RESET BOLD "\n       expected: %d\n       actual: %d\n" RESET, func_name, a, b);
}

void assert_equal_uint16(uint16_t a, uint16_t b, const char *func_name)
{
  if (a == b) printf(BOLD_GREEN "(PASS) %s\n" RESET, func_name);
  else printf(BOLD_RED "(FAIL) %s" RESET BOLD "\n       expected: %d\n       actual: %d\n" RESET, func_name, a, b);
}
