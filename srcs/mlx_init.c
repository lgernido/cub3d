/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:49:11 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 11:29:44 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	handle_error(void)
{
	printf("Erreur avec la MLX\n");
	exit(1);
}

t_data	ft_mlx_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		handle_error();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		handle_error();
	}
	return (*data);
}
