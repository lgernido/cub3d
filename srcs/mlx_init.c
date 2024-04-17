/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:11 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 09:00:01 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handle_error(void)
{
	printf("Erreur avec la MLX\n");
	exit(1);
}

// t_data	ft_mlx_init(t_data *data)
// {
// 	data->mlx = mlx_init();
// 	if (!data->mlx)
// 		handle_error();
// 	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
// 	if (!data->win)
// 	{
// 		mlx_destroy_display(data->mlx);
// 		free(data->mlx);
// 		handle_error();
// 	}
// 	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
// 	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
// 			&data->img.line_length, &data->img.endian);
// 	return (*data);
// }
