/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:09:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 16:02:08 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	error_exit(char *str, t_cub *cub)
{
	perror("Error\n");
	perror(str);
	if (cub)
		clean_all(cub);
	exit(1);
}

void	check_file_format(char *str, t_cub *infos)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i
		- 4] != '.')
		error_exit("Wrong file extension\n", infos);
}

char	**read_file(int file)
{
	char	**infos;
	char	*line;
	int		i;

	i = 0;
	infos = (char **)malloc(sizeof(char *) * 100);
	if (!infos)
		return (NULL);
	line = get_next_line(file);
	while (line != NULL)
	{
		infos[i] = line;
		i++;
		line = get_next_line(file);
	}
	infos[i] = NULL;
	return (infos);
}

void	check_params(int argc, char **argv)
{
	int		map;
	t_cub	*infos;

	infos = malloc(sizeof(t_cub));
	if (!infos)
		error_exit("MALLOC\n", infos);
	if (argc == 2)
	{
		check_file_format(argv[1], infos);
		map = open(argv[1], O_RDONLY);
		if (map == -1)
			error_exit("Map couldn't be opened\n", infos);
		infos->tab = read_file(map);
		if (!infos->tab)
			error_exit("MALLOC\n", infos);
		check_map(infos, infos->tab);
		infos->map = fill_map(infos->map_str, infos);
	}
}
