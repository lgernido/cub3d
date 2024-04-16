/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:41:26 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/16 14:41:27 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx.h"

void	clean_display(t_data *display)
{
	if (display->win != NULL)
	{
		mlx_destroy_window(display->mlx, display->win);
	}
	if (display->mlx != NULL)
	{
		mlx_destroy_display(display->mlx);
		free(display->mlx);
	}
}

void	clean_texture(t_img *textures, t_data *display)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i].img != NULL)
			mlx_destroy_image(display->mlx, textures[i].img);
		++i;
	}
}

void	clean_map(int	**map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		++i;
	}
	free(map);
}

void	clean_all(t_cub *cub)
{
	clean_texture(cub->texture, cub->display);
	if (cub->main_img.img != NULL)
	{
		mlx_destroy_image(cub->display->mlx, cub->main_img.img);
	}
	if (cub->map != NULL)
	{
		clean_map(cub->map);
	}
	if (cub->display != NULL)
	{
		clean_display(cub->display);
		free(cub->display);
	}
}
