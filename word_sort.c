#include <stdlib.h>
#include <string.h>

#include "word_sort.h"

int compare_tokens_case_sensitive(const void *a, const void *b)
{
    return strcmp(*(const char **) a, *(const char **) b);
}

int compare_tokens_case_insensitive(const void *a, const void *b)
{
    return strcasecmp(*(const char **) a, *(const char **) b);
}

int compare_tokens_reverse(const void *a, const void *b)
{
    return strcmp(*(const char **) b, *(const char **) a);
}

int compare_tokens_insensitive_reverse(const void *a, const void *b)
{
    return strcasecmp(*(const char **) b, *(const char **) a);
}

/* Wrapper to get a function pointer to the compare function based on flags */
int (*get_compare_function(unsigned int flags))(const void *, const void *)
{
    if (flags & WORD_SORT_IGNORE_CASE)
    {
        return (flags & WORD_SORT_REVERSE) ? compare_tokens_insensitive_reverse
                                           : compare_tokens_case_insensitive;
    }
    else
    {
        return (flags & WORD_SORT_REVERSE) ? compare_tokens_reverse : compare_tokens_case_sensitive;
    }
}

unsigned int word_sort(const char *src, char *dst, unsigned int dst_len, unsigned int flags)
{
    const char *delimiters = " \t\n";
    char *token = NULL;
    char *ctx;
    char **token_list = NULL;
    char *src_copy = NULL;
    unsigned int token_count = 0; /* token counter */
    unsigned int capacity = 0;    /* token list capacity */
    unsigned int char_count = 0;  /* token char counter */
    unsigned int offset = 0;
    unsigned int res = 0;

    if (src == NULL || dst == NULL || dst_len == 0)
        goto error;

    src_copy = strdup(src); /* Make src non-const. */
    if (!src_copy)
        goto error;

    /* Tokenize src buffer */
    token = strtok_r(src_copy, delimiters, &ctx);
    while (token)
    {
        if (token_count >= capacity)
        {
            /* Double the buffer capacity. */
            capacity = (capacity == 0) ? MIN_CAPACITY : capacity * 2;
            token_list = (char **) realloc(token_list, capacity * sizeof(char *));
            if (!token_list)
                goto error;
        }
        token_list[token_count++] = strdup(token);
        char_count += strlen(token) + 1;
        token = strtok_r(NULL, delimiters, &ctx);
    }

    int (*compare_function)(const void *, const void *) = get_compare_function(flags);
    qsort(token_list, token_count, sizeof(char *), compare_function);

    /* If there is insuffcient space in dst then the function returns 0 */
    if (char_count > dst_len)
        goto error;

    for (unsigned int i = 0; i < token_count; i++)
    {
        strcpy(dst + offset, token_list[i]);
        offset += strlen(token_list[i]);
        if (i < token_count - 1)
            dst[offset++] = ' ';
    }
    dst[offset++] = '\0';
    res = char_count;

error:
    if (src_copy)
        free(src_copy);

    for (unsigned int i = 0; i < token_count; i++)
    {
        if (token_list[i])
            free(token_list[i]);
    }
    if (token_list)
        free(token_list);

    return res;
}
