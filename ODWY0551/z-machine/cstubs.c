/*
! This file contains only those (pieces of) standard C library functions
! which are required in order to build "advent.c" for the Z-machine, and
! are not more easily written in Inform. These functions are:
!
!     void memset(dest, v, n)
!     void puts(buf)
!     void printf(fmt, ...)
!     void strcpy(dest, src)
!     int strlen(s)
!     int strncmp(a, b, n)
!
! The following functions are defined in Inform, in the file stubs.inf:
!
!     void fgets(buf, size, stdin)
!     void putc(ch, stdout)
!     void exit(0)
*/

#include <stdarg.h>  /* va_list */
#include <stdio.h>   /* puts, printf */
#include <string.h>  /* strcpy, strlen, strncmp, memset */

/* These should have unique values, but that's about it. */
FILE *stdin = (FILE *)&stdin;
FILE *stdout = (FILE *)&stdout;

void puts(const char *s)
{
    while (*s) {
        putc(*s, stdout);
        ++s;
    }
    putc('\n', stdout);
}

void strcpy(char *dst, const char *src)
{
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

int strlen(const char *s)
{
    const char *end = s;
    while (*end != '\0') ++end;
    return (end - s);
}

int strncmp(const char *a, const char *b, int n)
{
    for (int i=0; i < n; ++i) {
        unsigned char ca = *a++, cb = *b++;
        if (ca != cb) return (ca < cb) ? -1 : (ca > cb);
        if (ca == '\0') return 0;
    }
    return 0;
}

void memset(void *vdest, int v, int n)
{
    unsigned char *dest = vdest;
    while (n > 0) {
        --n;
        *dest++ = v;
    }
}

void _print_int(int i) = "\t@print_num r0;\n";

void printf(const char *format, ...)
{
    char c;
    va_list ap;
    va_start(ap, format);
    while (c = *format++) {
        if (c == '%') {
            switch (c = *format++) {
                case 'd': {
                    int i = va_arg(ap, int);
                    _print_int(i);
                    break;
                }
                case 's': {
                    char *s = va_arg(ap, char*);
                    while (c = *s++)
                        putc(c, stdout);
                    break;
                }
                default: {
                    putc(c, stdout);
                    break;
                }
            }
        } else {
            putc(c, stdout);
        }
    }
    va_end(ap);
}
