#include "get_next_line.h"

char	*strjoin(char **ptr_s1, char *s2)
{
	char	*new_str;
	size_t	len_s1;

	if (s2 == NULL)
		new_str = *ptr_s1;
	else if (*ptr_s1 == NULL)
		new_str = strdup(s2);
	else
	{
		len_s1 = strlen(*ptr_s1);
		new_str = (char *)malloc(sizeof(char) * (len_s1 + strlen(s2) + 1));
		if (new_str != NULL)
		{
			strcpy(new_str, *ptr_s1);
			strcpy(new_str + len_s1, s2);
			free(*ptr_s1);
			*ptr_s1 = NULL;
		}
	}
	return (new_str);
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