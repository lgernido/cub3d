/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purmerinos <purmerinos@protonmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:02:58 by purmerinos        #+#    #+#             */
/*   Updated: 2024/04/20 15:04:20 by purmerinos       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "mlx.h"

int	continue_verify(char *dimension_string, char *line)
{
	if (line == NULL)
	{
		ft_putendl_fd("Error\nWrong texture format", 2);
		return (0);
	}
	if (ft_strncmp(dimension_string, line, ft_strlen(dimension_string)) != 0)
	{
		ft_putendl_fd("Error\nWrong texture format", 2);
		return (0);
	}
	free (line);
	return (1);
}

int	verify_texture(char *path, char *dimension_string)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error", 2);
		return (0);
	}
	i = 0;
	line = NULL;
	while (i < 3)
	{
		if (line != NULL)
			free(line);
		line = get_next_line(fd, 0);
		++i;
	}
	close (fd);
	get_next_line(fd, -2);
	return (continue_verify(dimension_string, line));
}

int	open_wall_text(t_cub *cub, t_img *texture_dest, char *texture_path)
{
	texture_dest->line_length = TEXTURE_SIZE;
	texture_dest->endian = TEXTURE_SIZE;
	texture_dest->bits_per_pixel = 32;
	texture_dest->img = mlx_xpm_file_to_image(cub->display.mlx, texture_path,
			&texture_dest->line_length, &texture_dest->endian);
	if (texture_dest->img == NULL)
		return (0);
	texture_dest->addr = mlx_get_data_addr(texture_dest->img,
			&texture_dest->bits_per_pixel, &texture_dest->line_length,
			&texture_dest->endian);
	return (1);
}
