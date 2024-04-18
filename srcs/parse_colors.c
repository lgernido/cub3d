/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:39:47 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 10:20:43 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	give_me_color(char *str, int i)
{
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	parse_color(char *str, int i)
{
	if (str[i])
		if (ft_atoi(str + i) >= 0 && ft_atoi(str + i) <= 255)
		{
			while (str[i] && str[i] >= '0' && str[i] <= '9')
				i++;
			if (str[i] && str[i] == ',')
			{
				i++;
				if (ft_atoi(str + i) >= 0 && ft_atoi(str + i) <= 255)
				{
					while (str[i] && str[i] >= '0' && str[i] <= '9')
						i++;
					if (str[i] && str[i] == ',')
					{
						i++;
						if (ft_atoi(str + i) >= 0 && ft_atoi(str + i) <= 255)
							return (give_me_color(str, i));
					}
				}
			}
		}
	return (1);
}

void	treat_colors(t_parser *infos, char *str)
{
	if (check_id(str) == 5)
	{
		infos->floor = parse_color(str, 2);
	}
	else if (check_id(str) == 6)
	{
		infos->ceiling = parse_color(str, 2);
	}
}
