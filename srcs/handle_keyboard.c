/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:14:34 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/17 12:14:35 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <math.h>

int	kill_cross(t_cub *param)
{
	clean_cub(param, 0);
	return (0);
}

void	go_ns(t_cub *cub, double dir)
{
	if ((cub->map[(int)(cub->pos.x + ((0.5 * cub->dir.x) * dir))]
		[(int)(cub->pos.y + ((0.2 * cub->fov.y) * dir))] == 0)
			&& (cub->map[(int)(cub->pos.x + ((0.5 * cub->dir.x) * dir))]
		[(int)(cub->pos.y - ((0.2 * cub->fov.y) * dir))] == 0))
	{
		cub->pos.x += (0.1 * cub->dir.x) * dir;
	}
	if ((cub->map[(int)(cub->pos.x + ((0.2 * cub->dir.x) * dir))]
		[(int)(cub->pos.y + ((0.5 * cub->dir.y) * dir))] == 0)
			&& (cub->map[(int)(cub->pos.x + ((0.2 * cub->dir.x) * dir))]
		[(int)(cub->pos.y - ((0.5 * cub->fov.y) * dir))] == 0))
	{
		cub->pos.y += (0.1 * cub->dir.y) * dir;
	}
}

void	go_ew(t_cub *cub, double dir)
{
	if ((cub->map[(int)(cub->pos.x + ((0.2 * cub->dir.x) * dir))]
		[(int)(cub->pos.y + ((0.5 * cub->fov.y) * dir))] == 0)
		&& (cub->map[(int)(cub->pos.x - ((0.2 * cub->dir.x) * dir))]
		[(int)(cub->pos.y + ((0.5 * cub->fov.y) * dir))] == 0))
	{
		cub->pos.y += (0.1 * cub->fov.y) * dir;
	}
	else
	{
		go_ns(cub, -1.);
		return ;
	}
	if ((cub->map[(int)(cub->pos.x + ((0.2 * cub->fov.x) * dir))]
		[(int)(cub->pos.y + ((0.5) * cub->fov.y) * dir)] == 0)
			&& (cub->map[(int)(cub->pos.x - ((0.2 * cub->fov.x) * dir))]
			[(int)(cub->pos.y + ((0.5) * cub->fov.y) * dir)] == 0))
	{
		cub->pos.x += (0.1 * cub->fov.x) * dir;
	}
}

void	cam_rot(t_cub *cub, double rot_index)
{
	const double	old_dir = cub->dir.x;
	const double	old_fov = cub->fov.x;
	const double	rot_cos = cos(rot_index);
	const double	rot_sin = sin(rot_index);

	cub->dir.x = cub->dir.x * rot_cos - cub->dir.y * rot_sin;
	cub->dir.y = old_dir * rot_sin + cub->dir.y * rot_cos;
	cub->fov.x = cub->fov.x * rot_cos - cub->fov.y * rot_sin;
	cub->fov.y = old_fov * rot_sin + cub->fov.y * rot_cos;
}

int	handle_key(int key, t_cub *cub)
{
	if (key == XK_Escape)
		clean_cub(cub, 0);
	if (key == XK_w)
		go_ns(cub, 1.);
	if (key == XK_s)
		go_ns(cub, -1.);
	if (key == XK_a)
		go_ew(cub, -1);
	if (key == XK_d)
		go_ew(cub, 1);
	if (key == XK_Right)
		cam_rot(cub, -0.25);
	if (key == XK_Left)
		cam_rot(cub, 0.25);
	compute_image(cub);
	return (0);
}
