/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:16:35 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/19 08:26:13 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill_map(char *str, t_parser *infos)
{
	int	i;

	i = 0;
	while (infos->map[i] != NULL)
		i++;
	infos->map[i] = ft_strdup(str);
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
				fill_map(tab[i], infos);
		}
		else
			fill_struct(infos, tab[i]);
		i++;
	}
    map_format(infos->map, infos);
	dir = find_direction(infos->map);
	printf("map ok\n");
	return (infos);
}

int	**fill_real_map(char **map, t_parser *infos)
{
	int **real_map;
	size_t map_size;
	int i;
	int j;

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