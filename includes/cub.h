/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:27 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/20 14:32:29 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

//==========================================================================//
/*INCLUDES*/

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define WIDTH 1150
# define HEIGHT 920
# define TEXTURE_SIZE 64
# define MINIMAP 144
# define MINIMAP_PIX 16
# define EXPECTED_TEXT "\"64 64"
# define EXPECTED_MINI "\"16 16"

//==========================================================================//
/*STRUCTURES && ENUMS*/

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}			t_dir;

typedef enum e_mini_map {
	EMPTY,
	WALL,
	VOID,
	PLAYER
}						t_mini_map;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}			t_rgb;

typedef struct s_parser
{
	char	**tab;
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_rgb	floor;
	t_rgb	ceiling;
	int		number_of_line;
}			t_parser;

typedef struct s_point
{
	double	x;
	double	y;
}			t_point;

typedef struct s_raw_point {
	int	x;
	int	y;
}								t_raw_point;

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

typedef struct s_raycaster {
	double				camera;
	t_point				vector_direction;
	t_raw_point			box;
	t_raw_point			step;
	t_point				dist_to_next_side;
	int					side;
	t_point				dist_between_sides;
	t_raw_point			texcoord;
	double				wall_to_cam_plane;
	double				relative_coord_in_wall;
	int					line_size[2];
}							t_raycaster;

typedef struct s_cub {
	t_img	texture[4];
	t_img	main_img;
	t_img	mini_map;
	t_img	mini_map_texture[4];
	t_data	display;
	t_point	pos;
	t_dir	p_dir;
	t_point	dir;
	t_point	fov;	
	int		floor;
	int		ceiling;
	char	**map;
}			t_cub;

//==========================================================================//
/*PROTOTYPES*/

// main.c
int				main(int argc, char **argv);

// mlx_init.c
// t_data			ft_mlx_init(t_data *data);
// int				handle_error(t_cub *cub);

//==========================================================================//
//exec_init.c

void			exec_init(t_cub	*cub);

void			compute_image(t_cub *cub);

//==========================================================================//

// Raycaster.c 

// Define the value to increase vector to reach next border of a cube
void			compute_steps_dir(t_cub *cub, t_raycaster *current_values);

// Let vector advance until it touch a wall. Return where wall was hit 
// and from which side
void			go_to_hit(t_cub *cub, t_raycaster *current_value);

// Return vector lenght
void			compute_vector_length(t_raycaster *current_values);

// Return the range in which the wall should be displayed on screen.
void			get_y_range(t_raycaster *current_values);

//==========================================================================//
//mini_map.c

void			init_mini_map(t_cub *cub);
void			draw_mini_map(t_cub *cub, int x_sub_square, int y_sub_square,
					t_raw_point coord);
void			draw_rec(t_cub *cub, int x_sub_square, int y_sub_square,
					t_raw_point coord);

//==========================================================================//

// draw_line.c -- All the function in this files are used to draw the wall  
// to its place once the raycasting is done 

// Init for drawingline.
void			push_line(t_cub *cub, t_raycaster *current_values, int x);

//==========================================================================//
//drawing_utlis.c

// Take transparency, r, g, b, as charcode and combine them in an int.
int				colormap(int t, int r, int g, int b);

// push the given color on the specified pixel of the image.
void			my_pixel_put(t_img *img, int x, int y, unsigned int color);

// return the color of a pixel at the given coord of the specified image. 
unsigned int	retrieve_color_from_texture(t_img *img, t_raw_point *coord);

//==========================================================================//
// handle_keyboard.c

// Entry point for parsing keyboard input
int				handle_key(int key, t_cub *cub);

// Rotate cam
void			cam_rot(t_cub *cub, double rot_index);

// Close window
int				kill_cross(t_cub *param);
int				handle_mouse(t_cub *cub);

//==========================================================================//
//clean_exit.c
void			clean_cub(t_cub *cub, int error_code);
int				verify_texture(char *path, char *dimension_string);
int				open_wall_text(t_cub *cub, t_img *texture_dest,
					char *texture_path);

// Functon for testing solo exec
void			init_cub_var(t_cub *cub);

// init_struct.c

t_parser		*init_struct(t_parser *parser);

// parse_file.c
void			check_file_format(char *str, t_parser *infos);
void			error_exit(char *str, t_parser *infos);
void			check_params(char **argv, t_cub *cub);
char			**read_file(int file, char *path, t_parser *infos);
void			to_cub(t_parser *infos, t_cub *cub);

// check_map.c

int				valid_map(char *str, t_parser *infos);
int				check_side_wall(char **map, int line);
int				check_walls(char *str);
void			map_format(char **str, t_parser *infos);
int				map_position(t_parser *infos);

// fill_map.c
t_parser		*check_map(t_parser *infos, char **tab);
void			fill_map(char *str, t_parser *infos);
int				skip_spaces(char *str, int i);
void			proper_string_end(char *str);

// fill_struct.c

int				check_id(char *str);
t_parser		*fill_struct(t_parser *infos, char *str);
int				player_position(t_parser *infos, t_cub *cub);
void			fill_cub(char *str, t_cub *cub);
int				count_params(char **tab, t_parser *infos);

// parse_colors.c

void			treat_colors(t_parser *infos, char *str, t_rgb *color);
t_rgb			parse_color(char *str, int i, t_rgb *surface, t_parser *infos);

// clean_all.c

void			clean_all(t_parser *infos, int to_quit);
void			clean_map_str(t_parser *infos);
void			clean_tab(t_parser *infos);
void			really_clean_all(t_parser *info, t_cub *cub, int code);

// utils.c
char			*handle_space(char *str);
size_t			ft_map_size(char **str);
t_dir			find_direction(char c);
int				get_number_of_lines(int *fd, char *path);
void			check_txt(t_parser *info, char **text, char *str);

#endif
