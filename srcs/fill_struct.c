/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:15:03 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 15:42:32 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_id(char *str, t_cub *infos)
{
	int	i;

	i = 0;
	if (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\n')
			return (8);
		else if (str[i] == 'N' && str[i + 1] == 'O')
			return (1);
		else if (str[i] == 'S' && str[i + 1] == 'O')
			return (2);
		else if (str[i] == 'W' && str[i + 1] == 'E')
			return (3);
		else if (str[i] == 'E' && str[i + 1] == 'A')
			return (4);
		else if (str[i] == 'F' && str[i + 1] == ' ')
			return (5);
		else if (str[i] == 'C' && str[i + 1] == ' ')
			return (6);
		else if (valid_map(str[i]) == 0)
		{
			fill_map(str, infos);
			return (7);
		}
		else
			return (0);
	}
	return (0);
}

int	check_file(char *str, int i, t_cub *infos)
{
	int	fd;

	fd = open(str + i, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		error_exit("Can't open texture file\n", infos);
	}
	close(fd);
	return (fd);
}
t_cub	*fill_struct(t_cub *infos, char *str)
{
	t_text *files;

	files = malloc(sizeof(t_text));
	if (!files)
		error_exit("MALLOC\n", infos);
	if (check_id(str, infos) == 1)
		files->north = check_file(str, 3, infos);
	else if (check_id(str, infos) == 2)
		files->south = check_file(str, 3, infos);
	else if (check_id(str, infos) == 3)
		files->west = check_file(str, 3, infos);
	else if (check_id(str, infos) == 4)
		files->east = check_file(str, 3, infos);
	infos->texture_files = files;
    else 
        treat_colors(infos, str);
	return (infos);
}