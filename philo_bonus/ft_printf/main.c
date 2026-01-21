#include <stdio.h> // printf - remove
#include "ft_printf.h"

int	main(void)
{
	int	result;

	char *null_str = NULL;
	// result	= ft_printf("Hello, World!%5c %-10.5s %.2s %s '%s' %s\n", 'A', "1234", "Hello", "Hello", "", null_str);
	// printf(" ft_printf: %d\n", result);
	// result =    printf("Hello, World!%5c %-10.5s %.2s %s '%s' %s\n", 'A', "1234", "Hello", "Hello", "", null_str);
	// printf("std_printf: %d\n\n", result);

	result	= ft_printf("%p", null_str);
	printf(" ft_printf: %d\n", result);
	result =    printf("%p", null_str);
	printf("std_printf: %d\n\n", result);

	// result = ft_printf("%+d %i %u\n", +123, -123, -123);
	// printf(" ft_printf: %d\n\n", result);
	// result = 	printf("%+d %i %u\n", +123, -123, -123);
	// printf("std_printf: %d\n\n", result);

	// char *s	= "STR";
	// long h	= 0x9e407d4e;
	// long h2 = 0x10dc4ff0e;
	// int sh	= 0xe;
	// int i	= 0x10;
	// result = ft_printf("%p %x %X %#x '%0 +i' %%\n", s, h, h2, sh, i);
	// printf("%d\n", result);
	// result = printf("%p %lx %lX %#x '%0+i' %%\n", s, h, h2, sh, i);
	// printf("%d\n\n", result);

	// result = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%%c%%",
	// 				'A', " 42 ", 42, 42, 42, 42, 42, 'B', "-42 ", -42, -42, -42, -42, 42, 'C', "0", 0, 0, 0, 0, 42, 0);
	// printf("\n%d\n", result);
	// result = printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%%c%%",
	// 				'A', " 42 ", 42, 42, 42, 42, 42, 'B', "-42 ", -42, -42, -42, -42, 42, 'C', "0", 0, 0, 0, 0, 42, 0);
	// printf("\n%d\n", result);

	// result = ft_printf("%d\n", INT_MIN);
	// printf(" ft_printf: %d\n", result);
	// result = printf("%d\n", INT_MIN);
	// printf("std_printf: %d\n\n", result);

	// result = ft_printf("%d\n", INT_MAX);
	// printf(" ft_printf: %d\n", result);
	// result = printf("%d\n", INT_MAX);
	// printf("std_printf: %d\n\n", result);

	// result = ft_printf("%.0d\n", 0);
	// printf("%d\n", result);
	// result = printf("%.0d\n", 0);
	// printf("%d\n", result);

	// result = ft_printf("%+05d %-8d %08d %8.3d %.d %#08x '%#0x' '%#0x'\n", 7, 7, 7, 7, 0, 7,42, 0);
	// printf("%d\n", result);
	// result = printf("%+05d %-8d %08d %8.3d %.d %#08x '%#0x' '%#0x'\n", 7, 7, 7, 7, 0, 7, 42, 0);
	// printf("%d\n", result);

	// !!! WARNING: prints forever (INT MAX) !!!
	// result = ft_printf("'%5.0d' %2147483647d\n", 0, 42);
	// printf(" ft_printf: %d\n", result);
	// result = printf("'%5.0d' %2147483647d", 0, 42);
	// printf("std_printf: %d\n\n", result);

	// result = ft_printf("%x\n", 42);
	// printf("%d\n", result);
	// result = printf("%x\n", 42);
	// printf("%d\n", result);

	// int n = -42;
	// unsigned int a = (unsigned int)(0u - (unsigned int)n);
	// unsigned int b = (unsigned int)(n); // wrong way to convert -ve to unsigned
	// printf("%u %u\n", a, b);
}
