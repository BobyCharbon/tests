/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierremoretton <pierremoretton@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:25:27 by pierremoret       #+#    #+#             */
/*   Updated: 2022/03/10 15:53:08 by pierremoret      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int	fd = 0;
	int	ret = 0;
	char	*result;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		//result = get_next_line(fd);
		ret = get_next_line(fd);
		while (ret = 0)
		{
			//printf("RESULT: %s\n", (get_next_line(fd)));
			printf("%s\n", get_next_line(fd));
			//result = get_next_line(fd);
			printf("test\n");
			ret-;
		}
		/* ret = printf("RESULT2: %s\n", result);
		printf("%d\n", ret);

		if (ret == -1)
			printf("\nERROR\n");
		else if (ret == 0)
			printf("\nEND_OF_FILE\n"); */
		close(fd);
	}
	
	/* if (argc == 1)
	{
		while ((result = get_next_line(fd)) > 0)
			printf("[RETURN: %d], RESULT: %s\n", ret, result);
		if (ret == -1)
			printf("\nERROR\n");
		else if (ret == 0)
			printf("\nEND_OF_STDIN\n");
		
	} */
	//printf("%d\n", ret);
	return (0);
}