# <p align="center"> ft_printf - Custom Printf Implementation </p>

**42 Project | Variadic Functions & Format Parsing**  
**Objective:** Recreate the `printf` function from the C standard library, handling format specifiers, flags, width, precision, and various data types.

---

## Overview

**ft_printf** is a modular implementation of the `printf` function, built on top of `ft_dprintf` (a file descriptor-aware version). This project demonstrates variadic functions, format string parsing, type conversion, and output formatting.

---

## Skills Demonstrated

- **Variadic Functions:** Using `va_list`, `va_start`, `va_arg`, `va_end`
- **Format Parsing:** Complex string parsing and flag interpretation
- **Type Conversion:** Converting various data types to strings
- **Number Formatting:** Handling bases (decimal, hex, octal), precision, width
- **Platform Compatibility:** Cross-platform NULL pointer handling (Linux vs macOS)
- **Modular Design:** Building `printf` on top of `dprintf` for code reuse

---

## Project Structure

```
ft_printf/
├── ft_printf.c              # Main printf wrapper function
├── ft_printf.h              # Public interface header
├── Makefile                 # Build configuration
└── ../ft_dprintf/           # Core implementation (see ft_dprintf/README.md)
    ├── ft_dprintf.c         # Main dprintf and vdprintf functions
    ├── ft_dprintf.h         # Core header with all declarations
    ├── ft_parser.c          # Format string parsing
    ├── ft_print_types.c     # Character and string printing
    ├── ft_print_int.c       # Integer conversion and formatting
    └── ft_printf_utils.c    # Helper functions
```

**Key Files:**
- **ft_printf.c** - Wrapper that calls ft_dprintf with STDOUT_FILENO
- **ft_printf.h** - Public interface for users
- See `ft_dprintf/` for core implementation details

---

## Architecture

### Modular Structure

```
ft_dprintf/          (Core implementation)
├── ft_dprintf.c     - Main dprintf function with file descriptor support
├── ft_parser.c      - Format string parsing and specifier handling
├── ft_print_types.c - Character and string printing
├── ft_print_int.c   - Integer conversion and formatting
└── ft_dprintf.h     - Header with all declarations

ft_printf/           (Wrapper)
├── ft_printf.c      - printf wrapper (calls dprintf with STDOUT_FILENO)
└── ft_printf.h      - Public interface
```

**Design Philosophy:**
- `ft_dprintf` provides the core functionality with file descriptor support
- `ft_printf` is a thin wrapper that calls `ft_dprintf` with `STDOUT_FILENO`
- This modular approach allows code reuse and easier maintenance

---

## Supported Format Specifiers

| Specifier | Description | Example |
|-----------|-------------|---------|
| `%c` | Character | `ft_printf("%c", 'A')` → `A` |
| `%s` | String | `ft_printf("%s", "hello")` → `hello` |
| `%p` | Pointer address | `ft_printf("%p", ptr)` → `0x7fff5fbff6ac` |
| `%d` / `%i` | Signed integer | `ft_printf("%d", 42)` → `42` |
| `%u` | Unsigned integer | `ft_printf("%u", 42)` → `42` |
| `%x` | Lowercase hex | `ft_printf("%x", 255)` → `ff` |
| `%X` | Uppercase hex | `ft_printf("%X", 255)` → `FF` |
| `%%` | Literal percent | `ft_printf("%%")` → `%` |

---

## Supported Flags

| Flag | Description | Example |
|------|-------------|---------|
| `-` | Left-align | `ft_printf("%-10s", "hi")` → `hi        ` |
| `+` | Always show sign | `ft_printf("%+d", 42)` → `+42` |
| ` ` | Space for positive | `ft_printf("% d", 42)` → ` 42` |
| `0` | Zero padding | `ft_printf("%05d", 42)` → `00042` |
| `#` | Alternative format | `ft_printf("%#x", 42)` → `0x2a` |

---

## Width & Precision

- **Width:** Minimum field width (padded with spaces or zeros)
  - `ft_printf("%10d", 42)` → `        42`
  
- **Precision:** For integers, minimum number of digits; for strings, maximum characters
  - `ft_printf("%.5d", 42)` → `00042`
  - `ft_printf("%.3s", "hello")` → `hel`

---

## Platform-Specific Handling

### NULL Pointer Output

The `%p` specifier handles NULL pointers differently on Linux vs macOS:

```c
#ifdef __linux__
#  define NULL_PTR_STR "(nil)"
#else
#  define NULL_PTR_STR "0x0"
#endif
```

- **Linux:** `(nil)`
- **macOS:** `0x0`

This ensures compatibility with both platforms' printf behavior.

---

## Function Prototypes

```c
// Standard printf (writes to stdout)
int ft_printf(const char *fmt, ...);

// dprintf (writes to specified file descriptor)
int ft_dprintf(int fd, const char *fmt, ...);

// vdprintf (variadic version for custom wrappers)
int ft_vdprintf(int fd, const char *fmt, va_list ap);
```

---

## Compilation & Usage

```bash
# Build the library
cd ft_dprintf && make
cd ../ft_printf && make

# Link with your program
gcc your_program.c -L./ft_printf -lftprintf -o your_program
```

**Example Usage:**
See [`main.c`](main.c) for example usage demonstrating various format specifiers and test cases.

---

## Technical Highlights

### Format Parsing
- Parses complex format strings with flags, width, precision, and specifiers
- Handles edge cases: multiple flags, invalid specifiers, missing arguments

### Type Conversion
- Converts integers to strings in various bases (10, 16, 8)
- Handles signed/unsigned integers correctly
- Formats pointers as hexadecimal addresses

### Memory Management
- Efficient buffer management for number conversion
- No memory leaks in normal operation
- Handles large numbers and edge cases

### Error Handling
- Returns -1 on write errors
- Handles NULL pointers gracefully
- Validates format string syntax

---

## Testing

The project has been tested with:
- **[printfTester](https://github.com/Tripouille/printfTester)** - Comprehensive test suite for all specifiers and flags
- Custom test cases for edge cases and platform-specific behavior
- Integration with minishell project for real-world usage

---

*This project demonstrates advanced C programming skills including variadic functions, complex parsing, and modular library design.*
