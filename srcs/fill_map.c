/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:16:35 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/19 13:33:10 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill_map(char *str, t_parser *infos)
{
	int	i;

	i = 0;
	while (infos->map[i] != NULL)
		i++;
	if (str[0] != '\0' && str[0] != '\n')
		infos->map[i] = ft_strdup(str);
}

t_parser	*check_map(t_parser *infos, char **tab)
{
	int	i;
	int	j;

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
	infos->map[i] = "\0";
	map_format(infos->map, infos);
	return (infos);
}
