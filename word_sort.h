#ifndef WORD_SORT_H
#define WORD_SORT_H

#define WORD_SORT_REVERSE 0x1
#define WORD_SORT_IGNORE_CASE 0x2

#define MIN_CAPACITY 5 /* FIXME: maybe this is not the ideal size */

unsigned int word_sort(const char *src, char *dst, unsigned int dst_len, unsigned int flags);

#endif