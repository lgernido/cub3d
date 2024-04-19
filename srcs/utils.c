/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:22:08 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/19 14:36:05 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**handle_space(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (map);
}

size_t	ft_map_size(char **str)
{
	size_t	size;

	size = 0;
	while (str[size] != NULL)
	{
		size++;
	}
	return (size);
}

t_dir	find_direction(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N')
				return (NORTH);
			else if (map[i][j] == 'S')
				return (SOUTH);
			else if (map[i][j] == 'W')
				return (WEST);
			else if (map[i][j] == 'E')
				return (EAST);
			j++;
		}
		i++;
	}
	return (-1);
}

int	check_file(char *str, t_parser *infos)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		error_exit("Texture file can't be opened\n", infos);
		return (1);
	}
	close(fd);
	return (0);
}
