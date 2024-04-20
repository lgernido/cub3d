/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:09:34 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/20 10:12:21 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	error_exit(char *str, t_parser *infos)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	if (infos)
		clean_all(infos);
	exit(1);
}

void	check_file_format(char *str, t_parser *infos)
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
	char	**tab;
	char	*line;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * 100);
	if (!tab)
		return (NULL);
	line = get_next_line(file);
	while (line != NULL)
	{
		tab[i] = line;
		i++;
		line = get_next_line(file);
	}
	tab[i] = NULL;
	return (tab);
}

void	check_params(int argc, char **argv)
{
	int			map;
	t_parser	*infos;
	int			i;
	t_dir		direction;

	infos = NULL;
	infos = init_struct(infos);
	if (argc == 2)
	{
		check_file_format(argv[1], infos);
		map = open(argv[1], O_RDONLY);
		if (map == -1)
			error_exit("Parameters file couldn't be opened\n", infos);
		infos->tab = read_file(map);
		if (!infos->tab)
			error_exit("MALLOC\n", infos);
		infos = check_map(infos, infos->tab);
		direction = find_direction(infos->map);
		i = 0;
		while (infos->map[i] != NULL)
		{
			printf("%s\n", infos->map[i]);
			i++;
		}
		printf("\n\n");
		printf("infos.north: %s\n", infos->north);
		printf("infos.south: %s\n", infos->south);
		printf("infos.west: %s\n", infos->west);
		printf("infos.east: %s\n", infos->east);
		printf("Couleur du sol : R: %d, G: %d, B: %d\n", infos->floor.r,
			infos->floor.g, infos->floor.b);
		printf("Couleur du plafond : R: %d, G: %d, B: %d\n", infos->ceiling.r,
			infos->ceiling.g, infos->ceiling.b);
		printf("Orientation : %d\n", direction);
	}
}

// void	to_cub(t_parser *infos, t_cub *cub)
// {
// 	t_cub	*cub;

// 	cub = malloc(sizeof(t_cub));
// 	if (!cub)
// 		error_exit("MALLOC\n");
// 	cub->dir = find_direction(infos->map);
// 	cub->map = infos->map;
// }
