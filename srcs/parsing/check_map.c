/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:37:18 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/20 11:58:37 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	map_position(t_parser *infos)
{
	int	i;
	int	j;

	i = 0;
	while (infos->tab[i])
	{
		j = 0;
		while (infos->tab[i][j])
		{
			j++;
		}
		i++;
	}
	if (valid_map(infos->tab[i - 1], infos))
		error_exit("Map not at the end of file\n", infos);
	return (0);
}

int	valid_map(char *str, t_parser *infos)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[0] == '\n')
		{
			error_exit("Invalid map file\n", infos);
		}
		else if (str[i] != '0' && str[i] != '1' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'W' && str[i] != 'E' && str[i] != '\0'
			&& str[i] != ' ' && str[i] != '\n')
			return (1);
		else
			i++;
	}
	return (0);
}

int	check_walls(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	check_side_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '1')
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i - 1] != '1')
		return (0);
	return (1);
}

void	map_format(char **str, t_parser *infos)
{
	int	i;
	int	map_size;

	i = 0;
	map_size = ft_map_size(str);
	map_position(infos);
	while (str[i])
	{
		if (i == 0 || i == map_size - 1)
		{
			if (!check_walls(str[i]))
			{
				error_exit("Invalid walls\n", infos);
			}
		}
		else if (!check_side_wall(str[i]))
		{
			error_exit("Invalid walls\n", infos);
		}
		i++;
	}
}
