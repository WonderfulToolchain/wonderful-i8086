/**
 * wonderful-i8086 libc
 *
 * To the extent possible under law, the person who associated CC0 with
 * wonderful-i8086 libc has waived all copyright and related or neighboring rights
 * to wonderful-i8086 libc.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#pragma once
#include <stddef.h>

void __far* _fmemchr(const void __far* s, int c, size_t n);
void* _nmemchr(const void* s, int c, size_t n);
int _fmemcmp(const void __far* s1, const void __far* s2, size_t n);
int _nmemcmp(const void* s1, const void* s2, size_t n);
void __far* _fmemcpy(void __far* restrict s1, const void __far* restrict s2, size_t n);
void* _nmemcpy(void* restrict s1, const void* restrict s2, size_t n);
void __far* _fmemmove(void __far* s1, const void __far* s2, size_t n);
void* _nmemmove(void* s1, const void* s2, size_t n);
void __far* _fmemset(void __far* s, int c, size_t n);
void* _nmemset(void* s, int c, size_t n);

#ifdef __STRICT_ANSI__
void* memchr(const void* s, int c, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);
void* memcpy(void* restrict s1, const void* restrict s2, size_t n);
void* memmove(void* s1, const void* s2, size_t n);
void* memset(void*s, int c, size_t n);
#else
// TODO: Can we use macros to automatically select between near and far variants for performance?
#define memchr _fmemchr
#define memcmp _fmemcmp
#define memcpy _fmemcpy
#define memmove _fmemmove
#define memset _fmemset
#endif

char __far* strcat(char __far* s1, const char __far* s2);
char __far* strchr(const char __far* s, int c);
int strcmp(const char __far* s1, const char __far* s2);
char __far* strcpy(char __far* s1, const char __far* s2);
size_t strcspn(const char __far* s1, const char __far* s2);
size_t strlen(const char __far* s);
char __far* strncat(char __far* s1, const char __far* s2, size_t n);
int strncmp(const char __far* s1, const char __far* s2, size_t n);
char __far* strncpy(char __far* s1, const char __far* s2, size_t n);
char __far* strpbrk(const char __far* s1, const char __far* s2);
char __far* strrchr(const char __far* s, int c);
size_t strspn(const char __far* s1, const char __far* s2);
char __far* strstr(const char __far* s1, const char __far* s2);