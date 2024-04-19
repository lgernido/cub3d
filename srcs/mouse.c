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
#include "mlx.h"

int	handle_mouse(t_cub *cub)
{
	static int	prev_x = WIDTH / 2;
	int			x;
	int			y;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(cub->display.mlx, cub->display.win, &x, &y);
	if (x < prev_x + 2 && x > prev_x - 2)
	{
		prev_x = WIDTH / 2;
		mlx_mouse_move(cub->display.mlx, cub->display.win,
			WIDTH / 2, HEIGHT / 2);
		return (0);
	}
	if (x < WIDTH / 2)
		cam_rot(cub, 0.05);
	else if (x > WIDTH / 2)
		cam_rot(cub, -0.05);
	compute_image(cub);
	if (x < 0 || x > WIDTH)
		mlx_mouse_move(cub->display.mlx, cub->display.win,
			WIDTH / 2, HEIGHT / 2);
	prev_x = x;
	return (0);
}
