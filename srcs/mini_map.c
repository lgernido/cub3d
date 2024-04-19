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
	cub->mini_map_texture[tex].img = mlx_xpm_file_to_image(
			cub->display.mlx, path,
			&cub->mini_map_texture[tex].line_length,
			&cub->mini_map_texture[tex].endian);
	if (cub->mini_map_texture[tex].img == NULL)
		clean_all(cub, 1);
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
		clean_all(cub, 1);
	init_mini_map_text(cub);
}

void	image_in_image(t_cub *cub, int y, int x, t_mini_map tex)
{
	t_raw_point		coord;
	unsigned int	color;

	coord.x = 0;
	coord.y = 0;
	while (coord.x < MINIMAP_PIX)
	{
		coord.y = 0;
		while (coord.y < MINIMAP_PIX)
		{
			color = retrieve_color_from_texture(&cub->mini_map_texture[tex],
					&coord);
			my_pixel_put(&cub->mini_map, x + coord.x, y + coord.y, color);
			++coord.y;
		}
		++coord.x;
	}
}

void	draw_mini_map_rec(t_cub *cub, int x_sub_square, int y_sub_square, t_raw_point coord)
{
	// printf("Entered coord in image : x = %d, y = %d|||||| %d\n", coord.x, coord.y, cub->map[coord.x][coord.y]);
	if (x_sub_square < 0 || y_sub_square < 0
		|| x_sub_square > 128 || y_sub_square > 128)
		return ;
	else if (cub->map[coord.x] == NULL || coord.x == -1
		|| coord.y < 0 || cub->map[coord.x][coord.y] == -1)
	{
		image_in_image(cub, x_sub_square, y_sub_square, VOID);
		if (x_sub_square >= 64)
			draw_mini_map_rec(cub, x_sub_square + MINIMAP_PIX, y_sub_square, coord);
		else if (x_sub_square <= 64)
			draw_mini_map_rec(cub, x_sub_square - MINIMAP_PIX, y_sub_square, coord);
		if (y_sub_square >= 64)
			draw_mini_map_rec(cub, x_sub_square, y_sub_square + MINIMAP_PIX, coord);
		else if (y_sub_square <= 64)
			draw_mini_map_rec(cub, x_sub_square, y_sub_square - MINIMAP_PIX, coord);
		return ;
	}
	else if (cub->map[coord.x][coord.y] >= 1)
		image_in_image(cub, x_sub_square, y_sub_square, WALL);
	else if (cub->map[coord.x][coord.y] == 0)
		image_in_image(cub, x_sub_square, y_sub_square, EMPTY);
	if (y_sub_square >= 64)
	{
		coord.y += 1;
		draw_mini_map_rec(cub, x_sub_square, y_sub_square + MINIMAP_PIX, coord);
		coord.y -= 1;
	}
	if (y_sub_square <= 64)
	{
		coord.y -= 1.;
		draw_mini_map_rec(cub, x_sub_square, y_sub_square - MINIMAP_PIX, coord);
		coord.y += 1;
	}
	if (x_sub_square >= 64)
	{
		coord.x += 1;
		draw_mini_map_rec(cub, x_sub_square + MINIMAP_PIX, y_sub_square, coord);
		coord.x -= 1;
	}
	if (x_sub_square <= 64)
	{
		coord.x -= 1;
		draw_mini_map_rec(cub, x_sub_square - MINIMAP_PIX, y_sub_square, coord);
		coord.x += 1;
	}
	return ;
}

void	draw_mini_map(t_cub *cub, int x_sub_square, int y_sub_square, t_raw_point coord)
{
	image_in_image(cub, x_sub_square, y_sub_square, PLAYER);
	coord.y += 1;
	draw_mini_map_rec(cub, x_sub_square, y_sub_square + MINIMAP_PIX, coord);
	coord.y -= 2;
	draw_mini_map_rec(cub, x_sub_square, y_sub_square - MINIMAP_PIX, coord);
	coord.y += 1;
	coord.x += 1;
	draw_mini_map_rec(cub, x_sub_square + MINIMAP_PIX, y_sub_square, coord);
	coord.x -= 2;
	draw_mini_map_rec(cub, x_sub_square - MINIMAP_PIX, y_sub_square, coord);
	coord.x += 2;

}
