/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:09:46 by bchafi            #+#    #+#             */
/*   Updated: 2024/12/08 02:51:40 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_unsigned(unsigned int num)
{
	int	count;

	count = 0;
	if (num > 9)
		count += ft_unsigned(num / 10);
	ft_putchr((num % 10) + '0');
	return (count + 1);
}

static int	ft_ayero(const char *format, va_list args)
{
	int	count;

	count = 0;
	if (*format == 'c')
		count += ft_putchr(va_arg(args, int));
	else if (*format == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (*format == 'd' || *format == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (*format == 'x' || *format == 'X')
		count += ft_hexadecimal(va_arg(args, unsigned int), *format);
	else if (*format == 'u')
		count += ft_unsigned(va_arg(args, unsigned int));
	else if (*format == 'p')
	{
		count += ft_putstr("0x");
		count += ft_hexa_address(va_arg(args, unsigned long));
	}
	else if (*format == '%')
		count += ft_putchr(*format);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	if (write(1, 0, 0) < 0)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				break ;
			count += ft_ayero(format, args);
		}
		else
			count += ft_putchr(*format);
		format++;
	}
	va_end(args);
	return (count);
}

// #include <libc.h>
// int main() {
// //     // close(1);
//     // int fd = 43;
//     int a = 10;
//     int *ptr1 = &a;

//     printf("Pointer 1: %p\n", ptr1); // Prints address of a
//     printf("Pointer 2: %p\n", ptr1); // Prints address of b
//     printf("0x%p-\n", (void *)ULONG_MAX);
//     ft_printf("0x%p-\n", (void *)ULONG_MAX);
// //     // ft_printf("%d\n%d\n%c\n", -2, fd, 'f');
// //     // // printf("%d", printf("%d\n", -2147483647));
//     // ft_printf("\n%d\n", ft_printf("%u", 13));
//     // printf("\n%d\n", printf("%u", -13));
//     // ft_printf("\n%d", ft_printf("%u", -13));
    
// //     // printf("%d\n", printf("%d\n", 1));
// //     // ft_printf("%d\n", 555);
// //     // ft_printf("%X\n", 555);
// //     // ft_printf("%p\n", 44);
// //     // printf("%");
// //     // ft_printf("You are %d years old.\n", 20);
// //     // printf("You are %d years old.\n", 20);
// //     // ft_printf(NULL, NULL);
// //     // printf(NULL, NULL);
// //     // ft_printf("Percent sign: %%\n");
// //     // // // ??? fix this slice
// //     // ft_printf("Invalid specifier: %q\n");
// //     // // printf("Invalid specifier: %q\n");
// //     // ft_printf("Large number: %%");
// //     // ft_printf("Large number: %%%%%%%d", 42);
// //     // printf("Large number: %%%%%%%d", 42);
// //     // ft_printf("Char: %c\n", 'A');
// //     // ft_printf("my Hexadecimal (lowercase): %x\n", 102);
// //     // printf("Hexadecimal (lowercase): %x\n", 102); 
// //     // ft_printf("my Hexadecimal (uppercase): %X\n", 255);  
// //     // printf("Hexadecimal (lowercase): %X\n", 255);   
// //     // ft_printf("Hexadecimal of zero: %x\n", 0);      
// //     // printf("Hexadecimal of zero: %x\n", 0); 
// //     // ft_printf("Hexadecimal (large number): %x\n", 4294967295U);
// //     // printf("Hexadecimal (large number): %x\n", 4294967295U);
//     return 0;   
// }