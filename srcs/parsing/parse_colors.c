/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:39:47 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/20 14:37:53 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_color(t_parser *infos, char *str, int *color, int i)
{
	int	dec;

	dec = 0;
	while (ft_isdigit(str[i]))
	{
		++i;
		++dec;
	}
	if (dec == 0 || dec > 3)
		error_exit("Bad color identifier\n", infos);
	*color = ft_atoi(&str[i - dec]);
	if (*color < 0 || dec > 255)
		error_exit("Bad color identifier\n", infos);
	i = skip_spaces(str, i);
	return (i);
}

void	treat_colors(t_parser *infos, char *str, t_rgb *color)
{
	int	i;

	if (color->r != -1)
		error_exit("Redefinition of color\n", infos);
	i = skip_spaces(str, 1);
	i = get_color(infos, str, &color->r, i);
	if (str[i] != ',')
		error_exit("Bad color formatting\n", infos);
	i = skip_spaces(str, i + 1);
	i = get_color(infos, str, &color->g, i);
	if (str[i] != ',')
		error_exit("Bad color formatting\n", infos);
	i = skip_spaces(str, i + 1);
	i = get_color(infos, str, &color->b, i);
	if (str[i] != '\n')
		error_exit("Bad color formatting\n", infos);
}
