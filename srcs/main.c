/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:50:31 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/19 14:27:58 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "mlx.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc < 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("No map.", 2);
		return (1);
	}
	if (argc > 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Too many arguments.", 2);
		return (1);
	}
	ft_bzero(&cub, sizeof (t_cub));
	check_params(argc, argv, &cub);
	cub.display.mlx = mlx_init();
	if (cub.display.mlx == NULL)
		clean_cub(&cub, 1);
	// exec_init(&cub);
}
