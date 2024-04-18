/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:44:16 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/18 11:38:30 by lgernido         ###   ########.fr       */
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
	parser->floor.r = 0;
	parser->floor.g = 0;
	parser->floor.b = 0;
	parser->ceiling.r = 0;
	parser->ceiling.g = 0;
	parser->ceiling.b = 0;

	return (parser);
}
