/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:17:56 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 14:22:43 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clean_tab(t_cub *infos)
{
		int i;

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

void	clean_map_str(t_cub *infos)
{
		int i;

	if (infos->map_str)
	{
		i = 0;
		while (infos->map_str[i])
		{
			free(infos->tab[i]);
			i++;
		}
		free(infos->map_str);
	}
}

void	clean_all(t_cub *infos)
{
	clean_tab(infos);
	clean_map_str(infos);
	free(infos);
}