/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:58:39 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/19 14:58:41 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"

void	open_image(t_cub *cub, char *path, t_mini_map tex)
{
	if (verify_texture(path, EXPECTED_MINI) == 0)
		clean_cub(cub, 2);
	cub->mini_map_texture[tex].img = mlx_xpm_file_to_image(
			cub->display.mlx, path,
			&cub->mini_map_texture[tex].line_length,
			&cub->mini_map_texture[tex].endian);
	if (cub->mini_map_texture[tex].img == NULL)
		clean_cub(cub, 1);
	cub->mini_map_texture[tex].addr = mlx_get_data_addr(
			cub->mini_map_texture[tex].img,
			&cub->mini_map_texture[tex].bits_per_pixel,
			&cub->mini_map_texture[tex].line_length,
			&cub->mini_map_texture[tex].endian);
}

void	init_mini_map_text(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->mini_map_texture[i].line_length = MINIMAP_PIX;
		cub->mini_map_texture[i].endian = MINIMAP_PIX;
		cub->mini_map_texture[i].bits_per_pixel = 32;
		++i;
	}
	open_image(cub, "textures/mini_map/empty.xpm", EMPTY);
	open_image(cub, "textures/mini_map/wall.xpm", WALL);
	open_image(cub, "textures/mini_map/void.xpm", VOID);
	open_image(cub, "textures/mini_map/player.xpm", PLAYER);
}

void	init_mini_map(t_cub *cub)
{
	cub->mini_map.img = mlx_new_image(cub->display.mlx, MINIMAP, MINIMAP);
	cub->mini_map.addr = mlx_get_data_addr(cub->mini_map.img,
			&cub->mini_map.bits_per_pixel, &cub->mini_map.line_length,
			&cub->mini_map.endian);
	if (cub->mini_map.img == NULL)
		clean_cub(cub, 1);
	init_mini_map_text(cub);
}
