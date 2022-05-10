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

void __far* memchr(const void __far* s, int c, size_t n);
int memcmp(const void __far* s1, const void __far* s2, size_t n);
void __far* memcpy(void __far* restrict s1, const void __far* restrict s2, size_t n);
void __far* memmove(void __far* s1, const void __far* s2, size_t n);
void __far* memset(void __far* s, int c, size_t n);

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
