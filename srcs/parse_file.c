/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:09:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/16 14:15:24 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	error_exit(char *str)
{
	perror("Error\n");
	perror(str);
	exit(1);
}

void	check_map_format(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i
		- 4] != '.')
		error_exit("Wrong file extension\n");
}

char	**read_file(int file)
{
	char	**infos;
	char	*line;
	int		i;

	i = 0;
	infos = (char **)malloc(sizeof(char *) * 100);
	if (!infos)
		error_exit("MALLOC\n");
	while (get_next_line(file, &line) != NULL)
	{
		infos[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (infos);
}

void	check_params(int argc, char **argv)
{
	int			map;
	t_map_infos	*infos;
	int			i;

	infos = malloc(sizeof(t_map_infos));
	if (!infos)
		error_exit("MALLOC\n");
	if (argc == 2)
	{
		check_map_format(argv[1]);
		map = open(argv[1], O_RDONLY);
		if (map == -1)
			error_exit("Map couldn't be opened\n");
		infos->infos = read_file(map);
	}
	i = 0;
	while (infos->infos[i])
	{
		printf("%s\n", infos->infos[i]);
		i++;
	}
}
