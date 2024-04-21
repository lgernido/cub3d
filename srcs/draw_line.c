/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:02:15 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/18 18:02:15 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	fill_draw_info(double *step_in_texture, double *position_in_texture,
		int line_height)
{
	if (line_height < HEIGHT)
	{
		*position_in_texture = 0.;
		*step_in_texture = 1.0 * TEXTURE_SIZE / line_height;
	}
	else
	{
		*position_in_texture = ((((double)line_height / 2)
					- ((double)HEIGHT / 2))
				* ((double)TEXTURE_SIZE / 2)) / ((double)line_height / 2);
		*step_in_texture = ((double)TEXTURE_SIZE / 2)
			/ ((double)line_height / 2);
	}
}

static void	draw_wall(t_raycaster *current_values, t_dir wall_face,
		t_cub *cub, int x)
{
	int					line_height;
	double				step_in_texture;
	double				position_in_texture;
	unsigned int		color;

	line_height = (int)(HEIGHT / current_values->wall_to_cam_plane);
	fill_draw_info(&step_in_texture, &position_in_texture, line_height);
	while (current_values->line_size[0] != current_values->line_size[1])
	{
		current_values->texcoord.y = (int)floor(position_in_texture);
		if ((current_values->texcoord.y) >= TEXTURE_SIZE)
			current_values->texcoord.y = TEXTURE_SIZE - 1;
		position_in_texture += step_in_texture;
		color = retrieve_color_from_texture(&cub->texture[wall_face],
				&current_values->texcoord);
		my_pixel_put(&cub->main_img, x, current_values->line_size[0], color);
		current_values->line_size[0]++;
	}
}

static void	get_texture_x_axis(t_cub *cub, t_raycaster *current_values, int x)
{
	current_values->relative_coord_in_wall = cub->pos.y + current_values
		->wall_to_cam_plane * current_values->vector_direction.y;
	current_values->relative_coord_in_wall
		-= floor(current_values->relative_coord_in_wall);
	current_values->texcoord.x = (int)(current_values
			->relative_coord_in_wall * (double)TEXTURE_SIZE);
	if (current_values->vector_direction.x > 0)
		current_values->texcoord.x = TEXTURE_SIZE
			- current_values->texcoord.x - 1;
	if (current_values->vector_direction.x > 0)
		draw_wall(current_values, SOUTH, cub, x);
	else
		draw_wall(current_values, NORTH, cub, x);
}

static void	get_texture_y_axis(t_cub *cub, t_raycaster *current_values, int x)
{
	current_values->relative_coord_in_wall = cub->pos.x + current_values
		->wall_to_cam_plane * current_values->vector_direction.x;
	current_values->relative_coord_in_wall
		-= floor(current_values->relative_coord_in_wall);
	current_values->texcoord.x = (int)(current_values
			->relative_coord_in_wall * (double)TEXTURE_SIZE);
	if (current_values->vector_direction.y < 0)
		current_values->texcoord.x = TEXTURE_SIZE
			- current_values->texcoord.x - 1;
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
