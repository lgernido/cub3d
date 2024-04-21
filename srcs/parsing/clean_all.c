/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:17:56 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 14:05:37 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clean_tab(t_parser *infos)
{
	int	i;

	if (infos->tab)
	{
		i = 0;
		while (infos->tab[i])
		{
			free(infos->tab[i]);
			i++;
		}
		free(infos->tab);
	}
}

void	clean_map_str(t_parser *infos)
{
	int	i;

	if (infos->map)
	{
		i = 0;
		while (infos->map[i])
		{
			free(infos->map[i]);
			i++;
		}
		free(infos->map);
	}
}

void	clean_all(t_parser *infos, int to_quit)
{
	clean_tab(infos);
	clean_map_str(infos);
	free(infos);
	if (to_quit == 1)
		exit(1);
}

void	really_clean_all(t_parser *info, t_cub *cub, int code)
{
	clean_all(info, 0);
	clean_cub(cub, code);
}
