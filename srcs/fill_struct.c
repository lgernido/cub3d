/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:15:03 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 13:18:15 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_walls(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] == '1')
		i++;
	if (str[i] && str[i] == '\0')
		return (1);
	return (0);
}

int	check_side_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] != '1')
		return (1);
	while (str[i])
		i++;
	i--;
	if (str[i] != '1')
		return (1);
	return (0);
}

int	check_file(char *str, int i)
{
	int	fd;

	fd = open(str + i, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		error_exit("Can't open texture file\n");
	}
	close(fd);
	return (0);
}

void	fill_map(char *str, t_cub *infos)
{
	int	i;

	i = 0;
	while (infos->map_str[i] != NULL)
		i++;
	infos->map_str[i] = ft_strdup(str);
}

// t_cub	*fill_struct(t_cub *infos, char **tab)
// {
// }