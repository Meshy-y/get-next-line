*This project has been created as part of the 42 curriculum by bsarkoez.

# Get Next Line

## Description

**get_next_line** is a C function that returns one line at a time from a file descriptor:

```c
char *get_next_line(int fd);
```

Repeated calls read a file (or standard input) line by line until EOF. Each returned line includes its terminating `\n`, except possibly the last line if the file doesn't end with one. The function returns `NULL` when there is nothing left to read or when an error occurs.

The project introduces **static variables**, **file descriptors**, and **dynamic memory management**, and it works with any `BUFFER_SIZE` (1, 42, 9999, 10000000, ...).

**Bonus:** the bonus version uses a single static variable and handles several file descriptors at once. You can alternate calls between fd 3, 4, 5, and so on without losing each descriptor's reading state.

### Files

| Part      | Files                                                                            |
|-----------|----------------------------------------------------------------------------------|
| Mandatory | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`                    |
| Bonus     | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`  |

## Instructions

### Compilation

Compile with the required flags and a buffer size of your choice:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

The `-D BUFFER_SIZE=n` flag is optional. If it is omitted, a default value defined in the header is used.

For the bonus:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

### Usage example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

The caller owns each returned line and must `free()` it. To read from standard input, pass `0` as the file descriptor.

### Constraints

- Allowed external functions: `read`, `malloc`, `free`
- Forbidden: `libft`, `lseek()`, global variables

## Algorithm

The algorithm keeps leftover data between calls in a **static variable**, so nothing already read from the descriptor is lost.

1. **Static storage:** a static pointer (the "stash") holds the data that has been read from the file descriptor but not yet returned to the caller. Because it is static, it persists across calls.
2. **Read loop:** while the stash contains no `\n`, the function calls `read(fd, buffer, BUFFER_SIZE)` and appends the result to the stash. It stops as soon as a newline appears in the stash or `read` returns `0` (EOF).
3. **Extract the line:** the function copies everything from the start of the stash up to and including the first `\n` (or to the end of the stash if there is none) into a newly allocated string. This is the return value.
4. **Update the stash:** the remaining data after the returned line becomes the new stash, and the old stash is freed. If nothing remains, the stash is freed and set to `NULL`.
5. **Termination and errors:** if `read` returns `-1`, or if there is no data left at EOF, the stash is freed and the function returns `NULL`.

**Why this design:**
- It reads only as much as needed. The function stops reading as soon as a newline is found and never loads the whole file, as the subject requires.
- Reading in chunks of `BUFFER_SIZE` keeps the number of `read` calls reasonable, and the stash makes lines longer than the buffer work. A `BUFFER_SIZE` of 1 is slow but correct, and a very large one (like 10000000) works because the buffer size is independent of the line length.
- A static variable is the only way to remember leftover data between calls without global variables.

### Bonus: multiple file descriptors

The bonus keeps a **single static variable**, an array of stashes indexed by file descriptor (`static char *stash[FD_MAX];`). Each descriptor therefore has its own independent state, and calls on different descriptors can be interleaved freely. Invalid descriptors (`fd < 0` or `fd >= FD_MAX`) return `NULL`.

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- *The C Programming Language*, Kernighan & Ritchie (static storage duration, pointers)
- [GNU C Library manual: low-level input/output](https://www.gnu.org/software/libc/manual/html_node/Low_002dLevel-I_002fO.html)
- 42 Norm and the Get Next Line subject (v14.3)
- Discussions with peers during peer-learning sessions

### Use of AI

AI was used for: drafting and proofreading this README, and explaining the concept of static variables. All code was written, tested, and debugged by me.
