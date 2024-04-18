/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:37:18 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 15:44:54 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	valid_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'W' && str[i] != 'E' && str[i] != '\0'
			&& str[i] != '\n' && str[i] != ' ')
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
	if (str[i] && str[i] != '1')
		return (1);
	while (str[i])
		i++;
	i--;
	if (str[i--] != '1')
		return (1);
	return (0);
}

void	fill_map(char *str, t_parser *infos, int state)
{
	int	i;

	i = 0;
	while (infos->map[i] != NULL)
		i++;
	infos->map[i] = ft_strdup(str);
	if (state == 0)
	{
		if (!check_walls(str))
			error_exit("Invalid map\n", infos);
	}
	else
	{
		if (!check_side_wall(str))
			error_exit("Invalid map\n", infos);
	}
}

t_parser	*check_map(t_parser *infos, char **tab)
{
	int		i;
	int		j;
	t_dir	dir;

	i = 0;
	j = 0;
	infos->map = (char **)malloc(sizeof(char *) * 100);
	if (!infos->map)
		error_exit("MALLOC\n", infos);
	while (j < 100)
		infos->map[j++] = NULL;
	while (tab[i] != NULL)
	{
		if (check_id(tab[i]) == 7)
		{
			if (valid_map(tab[i]) == 1)
				error_exit("Invalid map file\n", infos);
			else
			{
				if (i == 7 || i == 20)
					fill_map(tab[i], infos, 0);
				else
					fill_map(tab[i], infos, 1);
			}
		}
		else
			fill_struct(infos, tab[i]);
		i++;
	}
	dir = find_direction(infos->map);
	printf("map ok\n");
	return (infos);
}

int	**fill_real_map(char **map, t_parser *infos)
{
	int		**real_map;
	size_t	map_size;
	int		i;
	int		j;

	i = 0;
	map_size = ft_map_size(map);
	real_map = (int **)malloc(sizeof(int *) * map_size);
	if (!real_map)
		error_exit("MALLOC\n", infos);
	while (map[i])
	{
		j = 0;
		real_map[i] = (int *)malloc(sizeof(int) * ft_strlen(map[i]));
		if (!real_map[i])
			error_exit("MALLOC\n", infos);
		while (map[i][j])
		{
			real_map[i][j] = atoi(map[i] + j);
			j++;
		}
		i++;
	}
	return (real_map);
}
