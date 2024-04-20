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
#include "libft.h"
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

void	clean_texture(t_img *textures, t_data *display, int size_of_tab)
{
	int	i;

	i = 0;
	while (i < size_of_tab)
	{
		if (textures[i].img != NULL)
			mlx_destroy_image(display->mlx, textures[i].img);
		++i;
	}
}

void	clean_map(char **map)
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

void	clean_cub(t_cub *cub, int error_code)
{
	clean_texture(cub->texture, &cub->display, 4);
	clean_texture(cub->mini_map_texture, &cub->display, 4);
	if (cub->main_img.img != NULL)
		mlx_destroy_image(cub->display.mlx, cub->main_img.img);
	if (cub->mini_map.img != NULL)
		mlx_destroy_image(cub->display.mlx, cub->mini_map.img);
	if (cub->map != NULL)
		clean_map(cub->map);
	clean_display(&cub->display);
	if (error_code == 1)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Minilibx Fault.", 2);
	}
	exit(error_code);
}
