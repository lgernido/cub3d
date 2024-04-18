/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:51:05 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/16 13:51:06 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"
#include <X11/X.h>
#include <stdlib.h>

void	exec_init(t_cub	*cub)
{
	init_map(cub);
	cub->display.win = mlx_new_window(cub->display.mlx, WIDTH, HEIGHT, "cub");
	if (cub->display.win == NULL)
		clean_all(cub, 1);
	cub->main_img.img = mlx_new_image(cub->display.mlx, WIDTH, HEIGHT);
	if (cub->main_img.img == NULL)
		clean_all(cub, 1);
	cub->main_img.addr = mlx_get_data_addr(cub->main_img.img,
			&cub->main_img.bits_per_pixel, &cub->main_img.line_length,
			&cub->main_img.endian);
	init_texture(cub);
	init_cub_var(cub);
	compute_image(cub);
	mlx_hook(cub->display.win, KeyPress, KeyPressMask, handle_key, cub);
	mlx_hook(cub->display.win, 17, 0, kill_cross, cub);
	mlx_loop(cub->display.mlx);
}

void	init_current_values(t_cub *cub, t_raycaster *current_values, int i)
{
	current_values->camera = (i * 2) / (double)WIDTH - 1;
	current_values->vector_direction.x = cub->dir.x
		+ cub->fov.x * current_values->camera;
	current_values->vector_direction.y = cub->dir.y
		+ cub->fov.y * current_values->camera;
	current_values->box.x = (int)cub->pos.x;
	current_values->box.y = (int)cub->pos.y;
	if (current_values->vector_direction.x == 0)
		current_values->dist_between_sides.x = 1e30;
	else
		current_values->dist_between_sides.x
			= fabs(1 / current_values->vector_direction.x);
	if (current_values->vector_direction.y == 0)
		current_values->dist_between_sides.y = 1e30;
	else
		current_values->dist_between_sides.y
			= fabs(1 / current_values->vector_direction.y);
}

void	draw_floor_and_ceilling(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			my_pixel_put(&cub->main_img, i, j, cub->ceiling);
			++j;
		}
		++i;
	}
	i = 0;
	while (i < WIDTH)
	{
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			my_pixel_put(&cub->main_img, i, j, cub->floor);
			++j;
		}
		++i;
	}
}

void	compute_image(t_cub *cub)
{
	t_raycaster	current_values;
	int			i;

	i = 0;
	draw_floor_and_ceilling(cub);
	while (i < WIDTH)
	{
		init_current_values(cub, &current_values, i);
		compute_steps_dir(cub, &current_values);
		go_to_hit(cub, &current_values);
		compute_vector_length(&current_values);
		get_y_range(&current_values);
		push_line(cub, &current_values, i);
		++i;
	}
	mlx_put_image_to_window(cub->display.mlx, cub->display.win,
		cub->main_img.img, 0, 0);
	mlx_destroy_image(cub->display.mlx, cub->main_img.img);
	cub->main_img.img = mlx_new_image(cub->display.mlx, WIDTH, HEIGHT);
	if (cub->main_img.img == NULL)
		clean_all(cub, 1);
	cub->main_img.addr = mlx_get_data_addr(cub->main_img.img,
			&cub->main_img.bits_per_pixel,
			&cub->main_img.line_length, &cub->main_img.endian);
}
