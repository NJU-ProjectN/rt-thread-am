#include <klib.h>
#include <rtthread.h>

__attribute__((weak)) char *strchr(const char *s, int c) {
  assert(0);
}

__attribute__((weak)) char *strrchr(const char *s, int c) {
  assert(0);
}

__attribute__((weak)) char *strstr(const char *haystack, const char *needle) {
  return rt_strstr(haystack, needle);
}

__attribute__((weak)) long strtol(const char *restrict nptr, char **restrict endptr, int base) {
  assert(0);
}

__attribute__((weak)) char *strncat(char *restrict dst, const char *restrict src, size_t sz) {
  assert(0);
}
