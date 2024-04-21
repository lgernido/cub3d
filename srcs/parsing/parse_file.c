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
		clean_all(infos);
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

void	check_params(int argc, char **argv, t_cub *cub)
{
	int			map;
	t_parser	*infos;
	t_dir		direction;
	int			i;

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
		count_params(infos->tab, infos);
		infos = check_map(infos, infos->tab);
		direction = find_direction(infos->map);
		cub = to_cub(infos, cub);
		i = 0;
		while (infos->map[i] != NULL)
		{
			printf("%s", infos->map[i]);
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
		printf("cube direction %d\n", cub->p_dir);
		printf("cube position :  x:%f, y:%f\n", cub->pos.x, cub->pos.y);
	}
	really_clean_all(infos, cub);
}

t_cub	*to_cub(t_parser *infos, t_cub *cub)
{
	int	i;

	i = 0;
	cub->p_dir = find_direction(infos->map);
	player_position(infos, cub);
	verify_texture(infos->north, EXPECTED_TEXT);
	verify_texture(infos->south, EXPECTED_TEXT);
	verify_texture(infos->east, EXPECTED_TEXT);
	verify_texture(infos->west, EXPECTED_TEXT);
	// while (infos->map[i] != NULL)
	// {
	// 	fill_cub(infos->map[i], cub);
	// 	i++;
	// }
	return (cub);
}
