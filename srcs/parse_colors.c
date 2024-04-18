/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:39:47 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 12:19:14 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_rgb	parse_color(char *str, int i, t_rgb *surface)
{
	if (str[i])
	{
		if (ft_atoi(str + i) >= 0 && ft_atoi(str + i) <= 255)
		{
			surface->r = ft_atoi(str + i);
			while (str[i] && str[i] >= '0' && str[i] <= '9')
				i++;
			if (str[i] && str[i] == ',')
			{
				i++;
				if (ft_atoi(str + i) >= 0 && ft_atoi(str + i) <= 255)
				{
					surface->g = ft_atoi(str + i);
					while (str[i] && str[i] >= '0' && str[i] <= '9')
						i++;
					if (str[i] && str[i] == ',')
					{
						i++;
						if (ft_atoi(str + i) >= 0 && ft_atoi(str + i) <= 255)
							surface->b = ft_atoi(str + i);
					}
				}
			}
		}
	}
	return (*surface);
}

void	treat_colors(t_parser *infos, char *str)
{
	if (check_id(str) == 5)
	{
		infos->floor = parse_color(str, 2, &infos->floor);
	}
	else if (check_id(str) == 6)
	{
		infos->ceiling = parse_color(str, 2, &infos->ceiling);
	}
}
