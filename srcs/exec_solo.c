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

void	init_cub_var(t_cub *cub)
{
	cub->pos.x = 1.5;
	cub->pos.y = 12.5;
	cub->dir.x = -1;
	cub->dir.y = 0;
	cub->fov.x = 0;
	cub->fov.y = 0.66;
	cub->floor = colormap(0, 182, 182, 182);
	cub->ceiling = colormap(0, 92, 92, 92);
	// cam_rot(cub, 3.14159);
}

void init_map(t_cub *cub)
{
	cub->map = malloc(25 * sizeof(int *));
	for (int i = 0; i < 24; ++i) {
		cub->map[i] = malloc(25 * sizeof(int));
		for (int j = 0; j < 24; ++j) {
			cub->map[i][j] = worldMap[i][j];
		}
		cub->map[i][24] = -1;
	}
	cub->map[24] = NULL;
	return ;
}

void	init_texture(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->texture[i].line_length = TEXTURE_SIZE;
		cub->texture[i].endian = TEXTURE_SIZE;
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
