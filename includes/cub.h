/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:27 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/17 15:29:27 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

//==========================================================================//
/*INCLUDES*/

# include "../libft/includes/libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

//==========================================================================//
/*STRUCTURES && ENUMS*/

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}			t_dir;

typedef struct s_text
{
	int		north;
	int		south;
	int		west;
	int		east;
}			t_text;

typedef struct s_point
{
	double	x;
	double	y;
}			t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
}			t_data;

typedef struct s_cub
{
	t_img texture[4]; // All textures should be stored here as images
	t_img *main_img;  // Not relevant for parsing
	t_data *display;  // Not relevant for parsing.
	t_point pos;      // First position of the player.
	t_dir p_dir;      // Start directon of the player.
	t_point dir;      // Not relevant for parsing.
	t_point camera;   // not relevant for parsing.
	int floor;        // Color of the floor.
	int ceiling;      // color of the ceiling.
						// Last row should be NULL. After last valid member of row,
	// one more shoul be set as -1.
	t_text	*texture_files;
	char	**tab;
	char	**map_str;
	int		*map[];
}			t_cub;

//==========================================================================//
/*PROTOTYPES*/

// main.c
int			main(int argc, char **argv);

// mlx_init.c
t_data		ft_mlx_init(t_data *data);
int			handle_error(void);

// parse_file.c
void		check_file_format(char *str, t_cub *infos);
void		error_exit(char *str, t_cub *cub);
void		check_params(int argc, char **argv);
char		**read_file(int file);

// check_map.c

int			valid_map(char c);
void		check_map(t_cub *infos, char **tab);
int			check_side_wall(char *str);
int			check_walls(char *str);
void		fill_map(char *str, t_cub *infos);

// fill_struct.c

int			check_id(char *str, t_cub *infos);
int			check_file(char *str, int i, t_cub *infos);
t_cub		*fill_struct(t_cub *infos, char *str);

// clean_all.c

void		clean_all(t_cub *infos);
void		clean_map_str(t_cub *infos);
void		clean_tab(t_cub *infos);

// utils.c
void		handle_space(char **map);

#endif
