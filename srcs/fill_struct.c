/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:15:03 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 12:45:17 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_id(char *str)
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
		else
			return (7);
	}
	return (0);
}

t_parser	*fill_struct(t_parser *infos, char *str)
{
	if (check_id(str) == 1)
		infos->north = (str + 3);
	else if (check_id(str) == 2)
		infos->south = (str + 3);
	else if (check_id(str) == 3)
		infos->west = (str + 3);
	else if (check_id(str) == 4)
		infos->east = (str + 3);
	else
		treat_colors(infos, str);
	return (infos);
}
