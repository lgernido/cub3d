/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:45:41 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/18 18:45:41 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_coord(int x, int y, int *prev_x)
{
	if (x == *prev_x)
		return (0);
	else if (x > WIDTH)
	{
		*prev_x = WIDTH;
		return (0);
	}
	else if (x < 0)
	{
		*prev_x = 0;
		return (0);
	}
	else if (y > HEIGHT || y < 0)
		return (0);
	return (1);
}

int	handle_mouse(t_cub *cub)
{
	static int	prev_x = WIDTH / 2;
	int			x;
	int			y;
	double		rot_factor;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(cub->display.mlx, cub->display.win, &x, &y);
	if (check_coord(x, y, &prev_x) == 0)
		return (0);
	rot_factor = ((double)abs(prev_x - x) / (double)WIDTH) * 3.5;
	if (x > prev_x)
		cam_rot(cub, -rot_factor);
	else
		cam_rot(cub, rot_factor);
	prev_x = x;
	compute_image(cub);
	return (0);
}
