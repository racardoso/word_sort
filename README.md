# Word Sort

This project was part of a technical interview challenge I completed some time ago. Unfortunately, I didn't pass that interview.  
The task was to implement a function in pure C that sorts words in a buffer (see `word_sort.txt` for details).

```
EXAMPLES
        src                       flags                             dst             return value
        ========================================================================================
        "The   \t\n cat  sat"     0                                 "The cat sat"   12 
        "The   \t\n cat  sat"     WORD_SORT_IGNORE_CASE             "cat sat The"   12
        "The   \t\n cat  sat"     WORD_SORT_REVERSE                 "sat cat The"   12
```

I've never received any feedback on why this was a 👎. I'm just leaving it here out of curiosity (this is not production code). Feel free to do whatever you want with it.

## Running Tests

This project uses **libcheck** for unit testing.

To run the tests, execute:

```bash
make test
```

## Usage Example

```c
#include "word_sort.h"

#include <stdio.h>

int main (void) {
    const char *src = "The   \t\n cat  sat";
    char dst[100];
    unsigned int ret = 0;

    ret = word_sort(src, dst, sizeof(dst), WORD_SORT_REVERSE);
    printf("%s\n", dst);

    return ret;
}
```

```bash
 gcc -Wall -Wextra -O3 -c word_sort.c -o word_sort.o
 gcc -Wall -Wextra -O3 word_sort.o main.c -o main
 ```

## Notice

I won’t disclose the company name, sorry.  
