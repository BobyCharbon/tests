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

char	*strjoin(char **ptr_s1, char *s2);
int		get_rest(char **rest, char **line);
char *read_file(int fd, char **rest, char *line);