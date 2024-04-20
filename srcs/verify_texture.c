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

int	verify_texture(char *path, char *dimension_string)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("cub3D: %s: %s\n", path, strerror(errno));
		return (0);
	}
	i = 0;
	line = NULL;
	while (i < 3)
	{
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
		++i;
	}
	if (ft_strncmp(dimension_string, line, ft_strlen(dimension_string)) != 0)
	{
		printf("cub3D: %s: Wrong texture format.\n", path);
		return (0);
	}
	return (1);
}
