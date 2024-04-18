/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:22:08 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 08:39:11 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	handle_space(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_is_space(map[i][j]))
				map[i][j] = '1';
			j++;
		}
		i++;
	}
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
