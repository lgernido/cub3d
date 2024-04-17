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
	cub->pos.x = 22;
	cub->pos.y = 12;
	cub->dir.x = -1;
	cub->dir.y = 0.00000000001;
	cub->fov.x = 0;
	cub->fov.y = 0.66;
	cub->floor = colormap(0, 173, 43, 217);
	cub->ceiling = colormap(0, 163, 137, 3);
}

void init_map(t_cub *cub)
{
	cub->map = malloc(25 * sizeof(int *));
	for (int i = 0; i < 24; ++i) {
		cub->map[i] = malloc(24 * sizeof(int));
		for (int j = 0; j < 24; ++j) {
			cub->map[i][j] = worldMap[i][j];
		}
	}
	cub->map[24] = NULL;
	return ;
}

void	init_texture(t_cub *cub)
{
	int	i = 0;

	while (i < 4)
	{
		cub->texture[i].line_length = 256;
		cub->texture[i].endian = 256;
		cub->texture[i].bits_per_pixel = 32;
		++i;
	}
	cub->texture[0].img = mlx_xpm_file_to_image(cub->display.mlx, "textures/jul1.xpm",
			&cub->texture[0].line_length, &cub->texture[0].endian);
	cub->texture[0].addr = mlx_get_data_addr(cub->texture[0].img, &cub->texture[0].bits_per_pixel, &cub->texture[0].line_length, &cub->texture[0].endian);
	cub->texture[1].img = mlx_xpm_file_to_image(cub->display.mlx, "textures/jul2.xpm",
			&cub->texture[1].line_length, &cub->texture[1].endian);
	cub->texture[1].addr = mlx_get_data_addr(cub->texture[1].img, &cub->texture[1].bits_per_pixel, &cub->texture[1].line_length, &cub->texture[1].endian);
	cub->texture[2].img = mlx_xpm_file_to_image(cub->display.mlx, "textures/jul3.xpm",
			&cub->texture[2].line_length, &cub->texture[2].endian);
	cub->texture[2].addr = mlx_get_data_addr(cub->texture[2].img, &cub->texture[2].bits_per_pixel, &cub->texture[2].line_length, &cub->texture[2].endian);
	cub->texture[3].img = mlx_xpm_file_to_image(cub->display.mlx, "textures/jul4.xpm",
			&cub->texture[3].line_length, &cub->texture[3].endian);
	cub->texture[3].addr = mlx_get_data_addr(cub->texture[3].img, &cub->texture[3].bits_per_pixel, &cub->texture[3].line_length, &cub->texture[3].endian);
}

void	exec_init(t_cub	*cub)
{
	init_map(cub);
	cub->display.win = mlx_new_window(cub->display.mlx, WIDTH, HEIGHT, "cub");
	if (cub->display.win == NULL)
		clean_all(cub, 1);
	cub->main_img.img = mlx_new_image(cub->display.mlx, WIDTH, HEIGHT);
	if (cub->main_img.img == NULL)
		clean_all(cub, 1);
	cub->main_img.addr = mlx_get_data_addr(cub->main_img.img, &cub->main_img.bits_per_pixel, &cub->main_img.line_length, &cub->main_img.endian);
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
		current_values->dist_between_sides.x = 0.0000001;
	else
		current_values->dist_between_sides.x
			= fabs(1 / current_values->vector_direction.x);
	if (current_values->vector_direction.y == 0)
		current_values->dist_between_sides.y = 0.000001;
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

void	go_to_hit(t_cub *cub, t_raycaster *current_value)
{
	int	wall_is_hit;

	wall_is_hit = 0;
	while (wall_is_hit == 0)
	{
		if (current_value->dist_to_next_side.x
			< current_value->dist_to_next_side.y)
		{
			current_value->dist_to_next_side.x
				+= current_value->dist_between_sides.x;
			current_value->box.x += current_value->step.x;
			current_value->side = 0;
		}
		else
		{
			current_value->dist_to_next_side.y
				+= current_value->dist_between_sides.y;
			current_value->box.y += current_value->step.y;
			current_value->side = 1;
		}
		if (cub->map[current_value->box.x][current_value->box.y] > 0)
			wall_is_hit = 1;
	}
}

void	compute_vector_length(t_raycaster *current_values)
{
	if (current_values->side == 0)
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

void	get_y_range(t_raycaster *current_values)
{
	int	line_height;

	// if (current_values->wall_to_cam_plane == 0)
	// 	current_values->wall_to_cam_plane += 0.1;
	line_height = (int)(HEIGHT / current_values->wall_to_cam_plane);
	current_values->line_size[0] = -line_height / 2 + HEIGHT / 2 + 100;
	if (current_values->line_size[0] < 0)
	{
		current_values->line_size[0] = 0;
	}
	current_values->line_size[1] = line_height / 2 + HEIGHT / 2 + 100;
	if (current_values->line_size[1] >= HEIGHT || current_values->line_size[1]
		< current_values->line_size[0])
	{
		current_values->line_size[1] = HEIGHT - 1;
	}
	return ;
}

void	draw_wall(t_raycaster *current_values, t_dir wall_face, t_cub *cub, int x)
{
	int					line_height;
	double				step_in_texture;
	double				position_in_texture;
	unsigned int		color;

	line_height = (int)(HEIGHT / current_values->wall_to_cam_plane);
	step_in_texture = 1.0 * TEXTURE_SIZE / line_height;
	position_in_texture = 0.;
	while (current_values->line_size[0] != current_values->line_size[1])
	{
		current_values->texCoord.y = (int)position_in_texture;
		if ((current_values->texCoord.y) >= TEXTURE_SIZE)
			current_values->texCoord.y = TEXTURE_SIZE - 1;
		position_in_texture += step_in_texture;
		color = retrieve_color_from_texture(&cub->texture[wall_face],
				&current_values->texCoord);
		my_pixel_put(&cub->main_img, x, current_values->line_size[0], color);
		current_values->line_size[0]++;
	}
}

void	get_texture_x_axis(t_cub *cub, t_raycaster *current_values, int x)
{
	current_values->relative_coord_in_wall = cub->pos.y + current_values
		->wall_to_cam_plane * current_values->vector_direction.y;
	current_values->relative_coord_in_wall
		-= floor(current_values->relative_coord_in_wall);
	current_values->texCoord.x = (int)(current_values
			->relative_coord_in_wall * (double)TEXTURE_SIZE);
	if (current_values->vector_direction.x > 0)
		current_values->texCoord.x = TEXTURE_SIZE
			- current_values->texCoord.x - 1;
	if (current_values->vector_direction.x > 0)
		draw_wall(current_values, SOUTH, cub, x);
	else
		draw_wall(current_values, NORTH, cub, x);
}

void	get_texture_y_axis(t_cub *cub, t_raycaster *current_values, int x)
{
	current_values->relative_coord_in_wall = cub->pos.x + current_values
		->wall_to_cam_plane * current_values->vector_direction.x;
	current_values->relative_coord_in_wall
		-= floor(current_values->relative_coord_in_wall);
	current_values->texCoord.x = (int)(current_values
			->relative_coord_in_wall * (double)TEXTURE_SIZE);
	if (current_values->vector_direction.y < 0)
		current_values->texCoord.x = TEXTURE_SIZE
			- current_values->texCoord.x - 1;
	if (current_values->vector_direction.y > 0)
	{
		draw_wall(current_values, WEST, cub, x);
	}
	else
	{
		draw_wall(current_values, EAST, cub, x);
	}
}

void	push_line(t_cub *cub, t_raycaster *current_values, int x)
{
	if (current_values->side == 0)
		get_texture_x_axis(cub, current_values, x);
	else
		get_texture_y_axis(cub, current_values, x);
}

void	clear_image(t_cub *cub)
{
	int	i;
	int	y_range[2];

	y_range[0] = 0;
	y_range[1] = HEIGHT;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(&cub->main_img, i, y_range, 0);
		++i;
	}
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
			my_pixel_put(&cub->main_img, i, j, cub->floor);
			++j;
		}
		++i;
	}
	i = 0;
	while (i < WIDTH)
	{
		j =  HEIGHT / 2;
		while (j < HEIGHT)
		{
			my_pixel_put(&cub->main_img, i, j, cub->ceiling);
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
	// draw_floor_and_ceilling(cub);
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
	cub->main_img.addr = mlx_get_data_addr(cub->main_img.img, &cub->main_img.bits_per_pixel, &cub->main_img.line_length, &cub->main_img.endian);
}
