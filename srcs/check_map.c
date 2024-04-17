/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:37:18 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 13:48:48 by lgernido         ###   ########.fr       */
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

int	check_id(char *str, t_cub *infos)
{
	int	i;

	i = 0;
	if (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
			return (8);
		else if (str[i] == 'N' && str[i + 1] == 'O')
			return (1);
		else if (str[i] == 'S' && str[i + 1] == 'O')
			return (2);
		else if (str[i] == 'W' && str[i + 1] == 'E')
			return (3);
		else if (str[i] == 'E' && str[i + 1] == 'A')
			return (4);
		else if (str[i] == 'F' && str[i + 1] == ' ')
			return (5);
		else if (str[i] == 'C' && str[i + 1] == ' ')
			return (6);
		else if (valid_map(str[i]) == 0)
		{
			fill_map(str, infos);
			return (7);
		}
		else
			return (0);
	}
	return (0);
}

void	check_map(t_cub *infos, char **tab)
{
	int i;

	i = 0;
	infos->map_str = (char **)malloc(sizeof(char *) * 100);
	if (!infos->map_str)
		error_exit("MALLOC\n");
	while (tab[i] != NULL)
	{
		if (check_id(tab[i], infos) == 0)
			error_exit("Invalid map file\n");
		i++;
	}
	printf("map ok\n");
}