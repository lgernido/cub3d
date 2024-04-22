/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:46:19 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/21 19:46:19 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

static void	fill_texture(t_parser *infos, t_cub *cub)
{
	if (verify_texture(infos->north, EXPECTED_TEXT) == 0)
		really_clean_all(infos, cub, 2);
	if (verify_texture(infos->south, EXPECTED_TEXT) == 0)
		really_clean_all(infos, cub, 2);
	if (verify_texture(infos->east, EXPECTED_TEXT) == 0)
		really_clean_all(infos, cub, 2);
	if (verify_texture(infos->west, EXPECTED_TEXT) == 0)
		really_clean_all(infos, cub, 2);
	if (open_wall_text(cub, &cub->texture[NORTH], infos->north) == 0)
		really_clean_all(infos, cub, 1);
	if (open_wall_text(cub, &cub->texture[SOUTH], infos->south) == 0)
		really_clean_all(infos, cub, 1);
	if (open_wall_text(cub, &cub->texture[EAST], infos->east) == 0)
		really_clean_all(infos, cub, 1);
	if (open_wall_text(cub, &cub->texture[WEST], infos->west) == 0)
		really_clean_all(infos, cub, 1);
}

static void	get_little_infos(t_parser *infos, t_cub *cub)
{
	cub->floor = colormap(0, infos->floor.r, infos->floor.g, infos->floor.b);
	cub->ceiling = colormap(0, infos->ceiling.r,
			infos->ceiling.g, infos->ceiling.b);
	player_position(infos, cub);
	if (cub->pos.x == 0.)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("No player starting position", 2);
		really_clean_all(infos, cub, 2);
	}
}

static char	*ft_strsuperdup(const char *s)
{
	size_t	len;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	str = malloc(len + 1 * sizeof (char));
	if (str == NULL)
		return (str);
	while (s[i] != '\0')
	{
		str[i] = s[i] - 48;
		++i;
	}
	str[i] = -1;
	return (str);
}

static void	copy_map(t_cub *cub, t_parser *infos)
{
	int	i;

	i = 0;
	while (infos->map[i] != NULL)
		i++;
	cub->map = ft_calloc(i + 2, sizeof(char **));
	if (cub->map == NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("No memory available", 2);
		really_clean_all(infos, cub, 2);
	}
	i = 0;
	while (infos->map[i] != NULL)
	{
		cub->map[i] = ft_strsuperdup(infos->map[i]);
		if (cub->map[i] == NULL)
		{
			ft_putendl_fd("Error", 2);
			ft_putendl_fd("No memory available", 2);
			really_clean_all(infos, cub, 2);
		}
		++i;
	}
	return ;
}

void	to_cub(t_parser *infos, t_cub *cub)
{
	cub->display.mlx = mlx_init();
	if (cub->display.mlx == NULL)
		really_clean_all(infos, cub, 1);
	get_little_infos(infos, cub);
	fill_texture(infos, cub);
	copy_map(cub, infos);
	return ;
}
