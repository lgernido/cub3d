/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:25:29 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/20 13:25:29 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int	should_pos_moove(t_cub *cub, int x_sub_square, int y_sub_square,
		t_raw_point coord)
{
	if (x_sub_square < 0 || y_sub_square < 0
		|| x_sub_square > 128 || y_sub_square > 128)
		return (0);
	else if (coord.x == -1 || cub->map[coord.x] == NULL
		|| coord.y < 0 || cub->map[coord.x][coord.y] == -1)
	{
		image_in_image(cub, x_sub_square, y_sub_square, VOID);
		if (x_sub_square >= 64)
			draw_rec(cub, x_sub_square + MINIMAP_PIX, y_sub_square, coord);
		else if (x_sub_square <= 64)
			draw_rec(cub, x_sub_square - MINIMAP_PIX, y_sub_square, coord);
		if (y_sub_square >= 64)
			draw_rec(cub, x_sub_square, y_sub_square + MINIMAP_PIX, coord);
		else if (y_sub_square <= 64)
			draw_rec(cub, x_sub_square, y_sub_square - MINIMAP_PIX, coord);
		return (0);
	}
	else if (cub->map[coord.x][coord.y] >= 1)
		image_in_image(cub, x_sub_square, y_sub_square, WALL);
	else if (cub->map[coord.x][coord.y] == 0)
		image_in_image(cub, x_sub_square, y_sub_square, EMPTY);
	return (1);
}

void	rec_x(t_cub *cub, int x_sub_square, int y_sub_square,
		t_raw_point coord)
{
	if (x_sub_square >= 64)
	{
		coord.x += 1;
		draw_rec(cub, x_sub_square + MINIMAP_PIX, y_sub_square, coord);
		coord.x -= 1;
	}
	if (x_sub_square <= 64)
	{
		coord.x -= 1;
		draw_rec(cub, x_sub_square - MINIMAP_PIX, y_sub_square, coord);
		coord.x += 1;
	}
}

void	draw_rec(t_cub *cub, int x_sub_square, int y_sub_square,
		t_raw_point coord)
{
	if (should_pos_moove(cub, x_sub_square, y_sub_square, coord) == 0)
		return ;
	if (y_sub_square >= 64)
	{
		coord.y += 1;
		draw_rec(cub, x_sub_square, y_sub_square + MINIMAP_PIX, coord);
		coord.y -= 1;
	}
	if (y_sub_square <= 64)
	{
		coord.y -= 1.;
		draw_rec(cub, x_sub_square, y_sub_square - MINIMAP_PIX, coord);
		coord.y += 1;
	}
	rec_x(cub, x_sub_square, y_sub_square, coord);
	return ;
}

void	draw_mini_map(t_cub *cub, int x_sub_square, int y_sub_square,
		t_raw_point coord)
{
	image_in_image(cub, x_sub_square, y_sub_square, PLAYER);
	coord.y += 1;
	draw_rec(cub, x_sub_square, y_sub_square + MINIMAP_PIX, coord);
	coord.y -= 2;
	draw_rec(cub, x_sub_square, y_sub_square - MINIMAP_PIX, coord);
	coord.y += 1;
	coord.x += 1;
	draw_rec(cub, x_sub_square + MINIMAP_PIX, y_sub_square, coord);
	coord.x -= 2;
	draw_rec(cub, x_sub_square - MINIMAP_PIX, y_sub_square, coord);
	coord.x += 2;
	return ;
}
