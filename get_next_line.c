#include "get_next_line.h"

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
	int	fd;
	char		*line = NULL;

	ac = 0;
	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (fd == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
