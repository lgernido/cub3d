/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:43:27 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/16 11:57:32 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

//==========================================================================//
/*INCLUDES*/

//#include "..libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800

//==========================================================================//
/*STRUCTURES*/
typedef enum e_dir {
	NORTH,
	SOUTH,
	EAST,
	WEST
}						t_dir;

typedef struct s_point {
	double	x;
	double	y;
}								t_point;

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
	double				camera; // Not a point, only x is needed.
	t_point				vector_direction; // Which direction vector is send.
	t_raw_point	box; // The locaton on the map in a raw value.
	t_raw_point	step; // Only 1 or -1. Indicate the direction a vector should move.
	t_point				dist_to_next_side; // Represent the lenght the vector 
	//need to be increment to reach the next side.
	t_point				dist_between_sides; // Distance for translating one side to another.
	double				wall_to_cam_plane;
}							t_raycaster;

typedef struct s_cub {
	t_img	texture[4]; // All textures should be stored here as images
	t_img	main_img; // Not relevant for parsing
	t_data	display; // Not relevant for parsing.
	t_point	pos; // First position of the player.
	t_dir		p_dir; // Start directon of the player.
	t_point	dir; // Not relevant for parsing.
	t_point	fov; // not relevant for parsing.	
	int			floor; // Color of the floor.
	int			ceiling; // color of the ceiling.
	int		**map; // Last row should be NULL. After last valid member of row, 
	// one more shoul be set as -1.
}								t_cub;

//==========================================================================//
/*PROTOTYPES*/

// main.c
int			main(void);

// mlx_init.c
t_data		ft_mlx_init(t_data *data);
int			handle_error(t_cub *cub);
void		clean_all(t_cub *cub, int error_code);
void		exec_init(t_cub	*cub);
void		draw_line(t_img *img, int x, int *y_range, int color);
int			colormap(int t, int r, int g, int b);

#endif
