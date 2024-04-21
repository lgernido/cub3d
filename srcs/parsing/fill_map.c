/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:16:35 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/20 13:48:44 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fill_map(char *str, t_parser *infos)
{
	int	i;

	i = 0;
	while (infos->map[i] != NULL)
		i++;
	str = handle_space(str);
	infos->map[i] = ft_strdup(str);
	if (infos->map[i] == NULL)
		error_exit("MALLOC\n", infos);
}

t_parser	*check_map(t_parser *infos, char **tab)
{
	int	i;

	i = 0;
	infos->map = (char **)ft_calloc(sizeof(char *), infos->number_of_line);
	if (!infos->map)
		error_exit("MALLOC\n", infos);
	while (tab[i])
	{
		if (check_id(tab[i]) == 7)
		{
			if (valid_map(tab[i], infos) == 1 || check_id(tab[i + 1]) == 8)
				error_exit("Invalid map file\n", infos);
			else
				fill_map(tab[i], infos);
		}
		else
			fill_struct(infos, tab[i]);
		i++;
	}
	map_format(infos->map, infos);
	return (infos);
}

int	skip_spaces(char *str, int i)
{
	while (str[i] && str[i] != '\n' && str[i] == ' ')
		++i;
	return (i);
}

void	proper_string_end(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] > 32 && str[i] < 126)
		++i;
	str[i] = '\0';
}
