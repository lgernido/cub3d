/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:22:08 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/20 10:24:03 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"

char	*handle_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			str[i] = '1';
		i++;
	}
	return (str);
}

size_t	ft_map_size(char **str)
{
	size_t	size;

	size = 0;
	while (str[size] != NULL)
	{
		size++;
	}
	return (size);
}

t_dir	find_direction(char c)
{
	if (c == 'N')
		return (NORTH);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'W')
		return (WEST);
	return (EAST);
}

int	get_number_of_lines(int *fd, char *path)
{
	size_t	i;
	char	*line;

	i = 0;
	line = (void *)1;
	while (line != NULL)
	{
		line = get_next_line(*fd, 0);
		if (line != NULL)
			free (line);
		++i;
	}
	get_next_line(*fd, -2);
	close(*fd);
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		return (-1);
	return (i + 1);
}

void	check_txt(t_parser *info, char **text, char *str)
{
	size_t	i;
	size_t	j;

	if (*text != NULL)
		error_exit("Redefinition of texture\n", info);
	i = skip_spaces(str, 2);
	j = i ;
	while (str[j] && str[j] != ' ' && str[j] != '\n')
		j++;
	j = skip_spaces(str, j);
	if (str[j] != '\n')
		error_exit("Texture : Misleading informations\n", info);
	proper_string_end(&str[i]);
	*text = &str[i];
}
