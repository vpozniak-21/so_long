/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:28:48 by vpozniak          #+#    #+#             */
/*   Updated: 2025/03/24 18:46:22 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>

// typedef struct	s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

// int	handle_keypress(int keycode, void *mlx)
// {
// 	if (keycode == 65307)  // Escape key
// 	{
// 		mlx_destroy_window(mlx, mlx);
// 		exit(0);
// 	}
// 	return (0);
// }

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if(!mlx_ptr)
		return(1);
	win_ptr = mlx_new_window(mlx_ptr, 600, 400, "Flappyly Ever After (or not)");
	if(!win_ptr)
		return(1);
	//mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr,win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	return(0);
}
