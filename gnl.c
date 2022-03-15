#include <stdio.h>
#include <fcntl.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#	define BUFFER_SIZE 10
#endif
#define STOP		0
#define CONTINUE	1

char	*strjoin(char **ptr_s1, char *s2)
{
	char	*new_string;
	size_t	len_s1;

	if (s2 == NULL)
		new_string = *ptr_s1;
	else if (*ptr_s1 == NULL)
		new_string = strdup(s2);
	else
	{
		len_s1 = strlen(*ptr_s1);
		new_string = (char *)malloc(sizeof(char) * (len_s1 + strlen(s2) + 1));
		if (new_string != NULL)
		{
			strcpy(new_string, *ptr_s1);
			strcpy(new_string + len_s1, s2);
			free(*ptr_s1);
			*ptr_s1 = NULL;
		}
	}
	return new_string;
}

int		get_rest(char **rest, char **line)
{
	char	*ptr_newline;
	char	*keep_rest;

	*line = NULL;
	if (*rest != NULL)
	{
		keep_rest = *rest;
		ptr_newline = strchr(*rest, '\n');
		if (ptr_newline != NULL)
		{
			(*rest)[(size_t)(ptr_newline - *rest)] = '\0';
			*line = strdup(*rest);
			*rest = strdup(ptr_newline + 1);
			free(keep_rest);
			return STOP;
		}
		*line = strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	return CONTINUE;
}

char *read_file(int fd, char **rest, char *line)
{
	char buffer[BUFFER_SIZE + 1];
	int read_bytes;
	char	*ptr_newline;

	while ((read_bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_bytes] = '\0';
		ptr_newline = strchr(buffer, '\n');
		if (ptr_newline != NULL)
		{
			buffer[(size_t)(ptr_newline - buffer)] = '\0';
			*rest = strdup(ptr_newline + 1);
		}
		line = strjoin(&line, buffer);
		if (*rest != NULL)
			break ;
	}
	return line;
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*line;

	if (get_rest(&rest, &line) == STOP)
		return line;
	return read_file(fd, &rest, line);
}


int main(int ac, char **av)
{
	const int	fd;
	char		*line = NULL;

	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (fd == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
