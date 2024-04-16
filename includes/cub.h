/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:27 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/16 14:24:53 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

//==========================================================================//
/*INCLUDES*/

# include "../libft/includes/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

//==========================================================================//
/*STRUCTURES && ENUMS*/

typedef enum e_orientation
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4

}					t_orientation;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;


typedef struct s_map_infos
{
	char			**infos;
	double			x;
	double			y;
	t_orientation	orientation;
}					t_map_infos;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_map_infos		start;
}					t_data;

//==========================================================================//
/*PROTOTYPES*/

// main.c
int					main(int argc, char **argv);

// mlx_init.c
t_data				ft_mlx_init(t_data *data);
int					handle_error(void);

// parse_file.c
void				check_map_format(char *str);
void				error_exit(char *str);
void				check_params(int argc, char **argv);
char				**read_file(int file);

#endif