/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:15:03 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/22 11:39:05 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

int	check_id(char *str)
{
	int	i;

	i = 0;
	if (str && str[i])
	{
		if (!ft_strncmp(str, "\n", 1))
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
		else
			return (7);
	}
	return (0);
}

t_parser	*fill_struct(t_parser *infos, char *str)
{
	if (check_id(str) == 1)
		check_txt(infos, &infos->north, str);
	else if (check_id(str) == 2)
		check_txt(infos, &infos->south, str);
	else if (check_id(str) == 3)
		check_txt(infos, &infos->west, str);
	else if (check_id(str) == 4)
		check_txt(infos, &infos->east, str);
	else if (check_id(str) == 5)
		treat_colors(infos, str, &infos->floor);
	else if (check_id(str) == 6)
		treat_colors(infos, str, &infos->ceiling);
	return (infos);
}

void	double_pos_error(t_parser *infos, t_cub *cub)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("Multiple player postion", 2);
	really_clean_all(infos, cub, 2);
}

int	player_position(t_parser *infos, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (infos->map[i])
	{
		j = 0;
		while (infos->map[i][j])
		{
			if (ft_strchr("NSEW", infos->map[i][j]))
			{
				if (cub->pos.x != 0.0)
					double_pos_error(infos, cub);
				cub->pos.x = (double)i + 0.5;
				cub->pos.y = (double)j + 0.5;
				cub->p_dir = find_direction(infos->map[i][j]);
				infos->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	count_params(char **tab, t_parser *infos)
{
	int	i;
	int	params;

	i = 0;
	params = 0;
	while (tab[i])
	{
		if (check_id(tab[i]) >= 1 && check_id(tab[i]) <= 6)
			params++;
		i++;
	}
	if (params != 6)
		error_exit("Invalid number of parameters\n", infos);
	return (0);
}
