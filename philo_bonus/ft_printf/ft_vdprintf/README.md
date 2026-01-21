# <p align="center"> ft_dprintf - File Descriptor Printf </p>

**42 Project | Core Printf Implementation**  
**Objective:** Implement a file descriptor-aware version of `printf` that serves as the core implementation for `ft_printf`.

---

## Overview

**ft_dprintf** is the core implementation of a custom printf library. Unlike standard `printf` which only writes to stdout, `ft_dprintf` can write to any file descriptor, making it more flexible and reusable. This implementation serves as the foundation for `ft_printf`.

**Development Context:** This implementation was created later when working on `minishell`, where I needed to print error messages to `stderr` instead of `stdout`. The original `printf` implementation already had `vprintf` (variadic version), which helped me understand the importance of modular architecture when creating `dprintf`. This modular approach allows code reuse between `printf` and `dprintf` while maintaining clean separation of concerns.

---

## Skills Demonstrated

- **File Descriptor I/O:** Writing to arbitrary file descriptors using `write()`
- **Variadic Functions:** Handling variable argument lists
- **Format String Parsing:** Complex parsing of flags, width, precision, specifiers
- **Type Conversion:** Converting various data types to formatted strings
- **Memory Management:** Efficient buffer handling for conversions
- **Platform Compatibility:** Cross-platform NULL pointer handling

---

## Project Structure

```
ft_dprintf/
├── ft_dprintf.c      # Main dprintf and vdprintf functions
├── ft_dprintf.h      # Header with all declarations and macros
├── ft_parser.c       # Format string parsing and specifier handling
├── ft_print_types.c  # Character and string printing functions
├── ft_print_int.c    # Integer conversion and formatting
├── ft_printf_utils.c # Helper functions (atoi, strlen, etc.)
└── Makefile          # Build configuration
```

**Key Files:**
- **ft_dprintf.c** - Entry point, handles variadic arguments and calls vdprintf
- **ft_parser.c** - Parses format string, extracts flags/width/precision/specifier
- **ft_print_types.c** - Handles `%c` and `%s` specifiers
- **ft_print_int.c** - Handles all numeric specifiers (`%d`, `%i`, `%u`, `%x`, `%X`, `%p`)

---

## Function Prototypes

```c
// Main dprintf function
int ft_dprintf(int fd, const char *fmt, ...);

// Variadic version (for custom wrappers)
int ft_vdprintf(int fd, const char *fmt, va_list ap);
```

**Parameters:**
- `fd`: File descriptor to write to (e.g., `STDOUT_FILENO`, `STDERR_FILENO`, or custom file descriptor)
- `fmt`: Format string with specifiers
- `...`: Variable arguments matching format specifiers

**Returns:**
- Number of characters written
- -1 on error

---

## Supported Features

### Format Specifiers
- `%c` - Character
- `%s` - String
- `%p` - Pointer address (with platform-specific NULL handling)
- `%d` / `%i` - Signed integer
- `%u` - Unsigned integer
- `%x` - Lowercase hexadecimal
- `%X` - Uppercase hexadecimal
- `%%` - Literal percent sign

### Flags
- `-` - Left alignment
- `+` - Always show sign for numbers
- ` ` (space) - Space for positive numbers
- `0` - Zero padding
- `#` - Alternative format (0x for hex, etc.)

### Width & Precision
- Minimum field width
- Precision for numbers and strings
- Dynamic width/precision from arguments

---

## Technical Implementation

### Core Components

**1. Format Parser ([`ft_parser.c`](ft_parser.c))**
- Parses format string character by character
- Extracts flags, width, precision, and specifier
- Handles edge cases and invalid formats

**2. Type Handlers ([`ft_print_types.c`](ft_print_types.c))**
- [`ft_print_char`](ft_print_types.c#L23): Single character output
- [`ft_print_str`](ft_print_types.c#L48): String output with width/precision
- Handles NULL pointers and empty strings

**3. Integer Conversion ([`ft_print_int.c`](ft_print_int.c))**
- Converts integers to strings in various bases
- Handles signed/unsigned correctly
- Formats with flags, width, and precision
- Efficient buffer management

**4. Utilities ([`ft_printf_utils.c`](ft_printf_utils.c))**
- Helper functions for parsing and conversion
- String manipulation utilities
- Number parsing functions

---

## Platform-Specific Behavior

### NULL Pointer Handling

The `%p` specifier outputs NULL pointers differently on Linux vs macOS:

```c
#ifdef __linux__
#  define NULL_PTR_STR "(nil)"
#else
#  define NULL_PTR_STR "0x0"
#endif
```

This ensures compatibility with platform-specific printf behavior.

---

## Compilation

```bash
# Build the library
make

# Clean object files
make clean

# Clean everything including library
make fclean

# Rebuild
make re
```

The library is compiled into `libftdprintf.a`.

---

## Integration with ft_printf

This library is designed to be used by `ft_printf`. See [`../printf/ft_printf.c`](../printf/ft_printf.c) for the implementation that wraps `ft_dprintf` with `STDOUT_FILENO`.

This modular approach allows:
- Code reuse between `printf` and `dprintf`
- Easier maintenance and testing
- Consistent behavior across both functions

---

## Technical Highlights

- **Efficient I/O:** Direct use of `write()` system call for maximum control
- **Memory Safety:** Proper handling of NULL pointers and edge cases
- **Format Flexibility:** Supports all standard printf flags and modifiers
- **Platform Compatibility:** Handles platform-specific differences gracefully
- **Modular Design:** Clean separation of concerns for maintainability

---

*This project demonstrates advanced C programming including system calls, variadic functions, and modular library architecture.*
