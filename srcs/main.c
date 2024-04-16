/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgernido <lgernido@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:50:31 by lgernido          #+#    #+#             */
/*   Updated: 2024/04/16 11:57:52 by lgernido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include "mlx.h"

int	main(void)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof (t_cub));
	// data = ft_mlx_init(&data); --> Not necessary at min, will be done
	// after parsing. Only mlx need to be init so texture images can refer to it.
	cub.display.mlx = mlx_init();
	if (cub.display.mlx == NULL)
		clean_all(&cub, 1);
	exec_init(&cub);
	// parse
}
