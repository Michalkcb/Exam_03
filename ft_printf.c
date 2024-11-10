/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:44:05 by mbany             #+#    #+#             */
/*   Updated: 2024/11/10 15:18:24 by mbany            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

static void ft_putstr(const char *s, int *count)
{
    if (!s)
        s = "(null)";
    while (*s)
    {
        write(1, s++, 1);
        (*count)++;
    }
}

static void ft_putnbr(int n, int *count)
{
    char c;

    if (n == -2147483648)
    {
        ft_putstr("-2147483648", count);
        return;
    }
    if (n < 0)
    {
        write(1, "-", 1);
        (*count)++;
        n = -n;
    }
    if (n > 9)
        ft_putnbr(n / 10, count);
    c = (n % 10) + '0';
    write(1, &c, 1);
    (*count)++;
}

static void ft_puthex(unsigned int n, int *count)
{
    char *hex = "0123456789abcdef";

    if (n >= 16)
        ft_puthex(n / 16, count);
    write(1, &hex[n % 16], 1);
    (*count)++;
}

int ft_printf(const char *format, ...) /* You can find all this function in the manual. "man va_arg", "man 2 va_arg", "man 3 va_arg" */
{
    va_list args;
    int count = 0;

    va_start(args, format);
    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;
            if (*format == 's')
                ft_putstr(va_arg(args, char *), &count);
            else if (*format == 'd')
                ft_putnbr(va_arg(args, int), &count);
            else if (*format == 'x')
                ft_puthex(va_arg(args, unsigned int), &count);
            else
            {
                write(1, format, 1);
                count++;
            }
        }
        else
        {
            write(1, format, 1);
            count++;
        }
        format++;
    }
    va_end(args);
    return count;
}

int main()
{

	char s[] = "sdhdsh";
	ft_printf("%s\n", s);
	int d = 999;
	ft_printf("%d\n", d);
	int x = 255;
	ft_printf("%x\n", x);
}