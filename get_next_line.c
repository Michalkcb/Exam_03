#include "get_next_line.h"

int slen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}
char *sdup(char *src)
{
	int i = 0;
	char *dest = (char *)malloc(sizeof(char) * (slen(src) + 1));
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);	
}
char *gnl(int fd)
{
	static char buffer[BUFFER_SIZE];
	char line[70000];
	static int buffer_read;
	static int buffer_pos;
	int i = 0;

	if (fd < 0 || BUFFER_SIZE <=0)
		return NULL;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd,buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break;
		}
		if (line[i] == '\n')
			break;
		line[i] = buffer[buffer_pos++];
		i++;
	}
	line[i] = '\0';
	if (i == 0)
		return NULL;
	return (sdup(line));
}
int main()
{
	int fd = open("./text.html", O_RDONLY);
	char *line = gnl(fd);
	printf("%s\n", line);
	free(line);
	close(fd);
	return(0);
}