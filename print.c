#include <unistd.h>
#include <stdarg.h>

static void putc(const char *s,int *count)
{
	if(!s)
		s = "(null)";
	while (*s)
	{
		write(1,s++,1);
		(*count)++;
	}
}
static void pnum(int n, int *count)
{
	int c;
	if(n == -2147483648)
	{
		putc("2147483648", count);
			return;
	}
	if (n < 0)
	{
		write(1,"-",1);
		(*count)++;
		n = -n;
	}
	if(n >= 10)
		pnum(n/10, count);
	c = (n % 10) +'0';
	write(1,&c,1);
	(*count)++;
}
static void phex(unsigned int n, int *count)
{
	if(n>=16)
		phex(n/16, count);
	write(1,&"0123456789abcdef"[n % 16],1);
	(*count)++;
}
int ft_print(const char *format, ...)
{
	va_list args;
	int count = 0;
	va_start(args, format);
	while (*format)
	{
		if(*format == '%' && *(format + 1))
		{
			format++;

			if (*format == 's')
				putc(va_arg(args, char *), &count);
			else if (*format == 'd')
				pnum(va_arg(args, int ), &count);
			else if(*format == 'x')
				phex(va_arg(args, unsigned int), &count);
			else
			{
				write(1, format,1);
				count++;
			}
		}
		else
		{
			write(1, format,1);
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
	int d = 999;
	int x = 255;
	ft_print("%s\n", s);
	ft_print("%d\n", d);
	ft_print("%x\n", x);
}