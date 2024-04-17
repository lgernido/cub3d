/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:37:18 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 16:01:09 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	valid_map(char c)
{
	if (c != '1' && c != '2' && c != 'N' && c != 'S' && c != 'W' && c != 'E'
		&& c != '\0')
		return (1);
	else
		return (0);
}

int	check_walls(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] == '1')
		i++;
	if (str[i] && str[i] == '\0')
		return (1);
	return (0);
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
	if (str[i] != '1')
		return (1);
	return (0);
}

void	fill_map(char *str, t_cub *infos)
{
	int	i;

	i = 0;
	while (infos->map_str[i] != NULL)
		i++;
	infos->map_str[i] = ft_strdup(str);
	if (i == 0)
	{
		if (check_walls(str) == 1)
			error_exit("Invalid map\n", infos);
	}
	else if (check_side_wall(str) == 1 && check_walls(str) == 1)
		error_exit("Invalid map\n", infos);
}

void	check_map(t_cub *infos, char **tab)
{
	int	i;

	i = 0;
	infos->map_str = (char **)malloc(sizeof(char *) * 100);
	if (!infos->map_str)
		error_exit("MALLOC\n", infos);
	while (tab[i] != NULL)
	{
		if (check_id(tab[i], infos) == 0)
			error_exit("Invalid map file\n", infos);
		else
			fill_struct(infos, tab[i]);
		i++;
	}
	printf("map ok\n");
}
int	**fill_map(char **map, t_cub *infos)
{
	int i;

	int **real_map;
	int map_size;

	i = 0;
	map_size = // faire une fonction de con;
		real_map = (int **)malloc(sizeof(int *) * map_size);
	if (!real_map)
		error_exit("MALLOC\n");
	while (map[i])
	{
		real_map[i] = atoi(map[i]);
		i++;
	}
	return (real_map);
}