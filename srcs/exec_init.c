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
#include <stdlib.h>

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	compute_image(t_cub *cub);

int	kill_cross(t_cub *param)
{
	clean_all(param, 0);
	return (0);
}

void	init_cub_var(t_cub *cub)
{
	cub->dir.x = -1;
	cub->dir.y = 0;
	cub->fov.x = 0;
	cub->fov.y = 0.66;
}

void init_map(t_cub *cub)
{
	cub->map = malloc(24 * sizeof(int *));
	for (int i = 0; i < 24; ++i) {
		cub->map[i] = malloc(24 * sizeof(int));
		for (int j = 0; j < 24; ++j) {
			cub->map[i][j] = worldMap[i][j];
		}
	}
	return ;
}

void	exec_init(t_cub	*cub)
{
	init_map(cub);
	cub->display.win = mlx_new_window(cub->display.mlx, WIDTH, HEIGHT, "cub");
	if (cub->display.win == NULL)
		clean_all(cub, 1);
	cub->main_img.img = mlx_new_image(cub->display.mlx, WIDTH, HEIGHT);
	cub->main_img.addr = mlx_get_data_addr(cub->main_img.img, &cub->main_img.bits_per_pixel, &cub->main_img.line_length, &cub->main_img.endian);
	compute_image(cub);
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
		current_values->dist_between_sides.x = 0.001;
	else
		current_values->dist_between_sides.x
			= fabs(1 / current_values->vector_direction.x);
	if (current_values->vector_direction.y == 0)
		current_values->dist_between_sides.y = 0.001;
	else
		current_values->dist_between_sides.y
			= fabs(1 / current_values->vector_direction.y);
}

void	compute_steps_dir(t_cub *cub, t_raycaster *current_values)
{
	if (current_values->vector_direction.x < 0)
	{
		current_values->step.x = -1;
		current_values->dist_to_next_side.x = (cub->pos.x - current_values
				->box.x) * current_values->dist_between_sides.x;
	}
	else
	{
		current_values->step.x = 1;
		current_values->dist_to_next_side.x = (current_values->box.x
				+ 1.0 - cub->pos.x) * current_values->dist_between_sides.x;
	}
	if (current_values->vector_direction.y < 0)
	{
		current_values->step.y = -1;
		current_values->dist_to_next_side.y = (cub->pos.y - current_values
				->box.y) * current_values->dist_between_sides.y;
	}
	else
	{
		current_values->step.y = 1;
		current_values->dist_to_next_side.y = (current_values->box.y
				+ 1.0 - cub->pos.y) * current_values->dist_between_sides.y;
	}
}

int	go_to_hit(t_cub *cub, t_raycaster *current_value)
{
	int	wall_is_hit;
	int	side;

	wall_is_hit = 0;
	while (wall_is_hit == 0)
	{
		if (current_value->dist_to_next_side.x
			< current_value->dist_to_next_side.y)
		{
			current_value->dist_to_next_side.x
				+= current_value->dist_between_sides.x;
			current_value->box.x += current_value->step.x;
			side = 0;
		}
		else
		{
			current_value->dist_to_next_side.y
				+= current_value->dist_between_sides.y;
			current_value->box.y += current_value->step.y;
			side = 1;
		}
		if (cub->map[current_value->box.x][current_value->box.y] > 0)
			wall_is_hit = 1;
	}
	return (side);
}

void	compute_vector_length(t_raycaster *current_values, int side)
{
	if (side == 0)
	{
		current_values->wall_to_cam_plane = current_values->dist_to_next_side.x
			- current_values->dist_between_sides.x;
	}
	else
	{
		current_values->wall_to_cam_plane = current_values->dist_to_next_side.y
			- current_values->dist_between_sides.y;
	}
	return ;
}

void	get_y_range(t_raycaster *current_values, int *y_range)
{
	int	line_height;

	if (current_values->wall_to_cam_plane == 0)
		current_values->wall_to_cam_plane += 0.1;
	printf("%lf\n", current_values->wall_to_cam_plane);
	line_height = (int)(HEIGHT / current_values->wall_to_cam_plane);
	printf("%lf\n", current_values->wall_to_cam_plane);
	y_range[0] = -line_height / 2 + HEIGHT / 2;
	if (y_range[0] < 0)
	{
		y_range[0] = 0;
	}
	y_range[1] = line_height / 2 + HEIGHT / 2;
	if (y_range[1] >= HEIGHT)
	{
		y_range[1] = HEIGHT - 1;
	}
	return ;
}

void	push_line(t_cub *cub, int side, int *y_range, int x)
{
	printf("x stripe : %d, Y start : %d, Y end : %d\n", x, y_range[0], y_range[1]);
	if (side == 0)
	{
		draw_line(&cub->main_img, x, y_range, colormap(0, 255, 0, 0));
	}
	else
	{
		draw_line(&cub->main_img, x, y_range, colormap(0, 0, 255, 0));
	}
}

void	compute_image(t_cub *cub)
{
	t_raycaster	current_values;
	int			i;
	int			side;
	int			y_range[2];

	i = 0;
	while (i < WIDTH)
	{
		init_current_values(cub, &current_values, i);
		compute_steps_dir(cub, &current_values);
		side = go_to_hit(cub, &current_values);
		compute_vector_length(&current_values, side);
		get_y_range(&current_values, y_range);
		push_line(cub, side, y_range, i);
		++i;
	}
	mlx_put_image_to_window(cub->display.mlx, cub->display.win,
		cub->main_img.img, 0, 0);
}
