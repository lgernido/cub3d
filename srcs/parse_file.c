/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:09:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/16 12:53:26 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	error_exit(char *str)
{
	perror("Error\n");
	perror(str);
	exit(1);
}

void	check_map_format(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i
		- 4] != '.')
		error_exit("Wrong file extension\n");
}

void	check_params(int argc, char **argv)
{
	// int map;
	if (argc == 2)
	{
		check_map_format(argv[1]);
		// map = open(argv[1], O_RDONLY);
		// if (map = -1)
		// 	error_exit("Map couldn't be opened\n");
		printf("FORMAT OK");
	}
}