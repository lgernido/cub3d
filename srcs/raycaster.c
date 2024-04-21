/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:05:06 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/18 18:05:07 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		if (cub->map[current_value->box.x][current_value->box.y] == 1)
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

	if (current_values->wall_to_cam_plane == 0)
		current_values->wall_to_cam_plane += 1e30;
	line_height = (int)(HEIGHT / current_values->wall_to_cam_plane);
	current_values->line_size[0] = -line_height / 2 + HEIGHT / 2;
	if (current_values->line_size[0] < 0)
	{
		current_values->line_size[0] = 0;
	}
	current_values->line_size[1] = line_height / 2 + HEIGHT / 2;
	if (current_values->line_size[1] > HEIGHT || current_values->line_size[1]
		< current_values->line_size[0])
	{
		current_values->line_size[1] = HEIGHT;
	}
	return ;
}
