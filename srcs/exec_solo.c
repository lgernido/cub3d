/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:55:58 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/18 17:56:00 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_cub_var(t_cub *cub)
{
	cub->dir.x = -1;
	cub->dir.y = 0;
	cub->fov.x = 0;
	cub->fov.y = 0.66;
	if (cub->p_dir == EAST)
		cam_rot(cub, -1.5708);
	else if (cub->p_dir == WEST)
		cam_rot(cub, 1.5708);
	else if (cub->p_dir == SOUTH)
		cam_rot(cub, 3.14159);
}
