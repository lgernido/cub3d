/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:44:16 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 12:18:13 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_parser	*init_struct(t_parser *parser)
{
	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
	{
		error_exit("MALLOC\n", parser);
		return (NULL);
	}
	parser->tab = NULL;
	parser->map = NULL;
	parser->north = NULL;
	parser->south = NULL;
	parser->west = NULL;
	parser->east = NULL;
	parser->floor.r = -1;
	parser->floor.g = -1;
	parser->floor.b = -1;
	parser->ceiling.r = -1;
	parser->ceiling.g = -1;
	parser->ceiling.b = -1;
	return (parser);
}

void	check_txt(t_parser *info, char **text, char *str)
{
	size_t	i;

	if (*text != NULL)
		error_exit("Redefinition of texture\n", info);
	i = skip_spaces(str, 2);
	*text = &str[i];
}
