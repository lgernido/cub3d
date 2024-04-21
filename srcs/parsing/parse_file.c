/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:09:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/20 14:38:18 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	error_exit(char *str, t_parser *infos)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	if (infos)
		clean_all(infos, 0);
	exit(1);
}

void	check_file_format(char *str, t_parser *infos)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i < 4)
		error_exit("Wrong file extension\n", infos);
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i
			- 4] != '.')
		error_exit("Wrong file extension\n", infos);
}

char	**read_file(int file, char *path, t_parser *infos)
{
	char	**tab;
	char	*line;
	int		i;

	i = 0;
	infos->number_of_line = get_number_of_lines(&file, path);
	if (infos->number_of_line == -1)
		error_exit("Parameters file couldn't be opened\n", infos);
	tab = (char **)ft_calloc(sizeof(char *), infos->number_of_line);
	if (!tab)
		return (NULL);
	line = get_next_line(file, 0);
	while (line != NULL)
	{
		tab[i] = line;
		i++;
		line = get_next_line(file, 0);
	}
	return (tab);
}

void	check_params(char **argv, t_cub *cub)
{
	int			map;
	t_parser	*infos;

	infos = NULL;
	infos = init_struct(infos);
	check_file_format(argv[1], infos);
	map = open(argv[1], O_RDONLY);
	if (map == -1)
		error_exit("Parameters file couldn't be opened\n", infos);
	infos->tab = read_file(map, argv[1], infos);
	close(map);
	if (!infos->tab)
		error_exit("MALLOC\n", infos);
	count_params(infos->tab, infos);
	infos = check_map(infos, infos->tab);
	to_cub(infos, cub);
	clean_all(infos, 0);
	return ;
}
