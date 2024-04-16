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

void	exec_init(t_cub	*cub)
{
	cub->display->mlx = mlx_init();
	if (cub->display->mlx == NULL)
}
