/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:00 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/10 19:46:56 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	print_player(t_game *game, char d)
{
	int	x;
	int	y;

	x = game->player_x * 64;
	y = game->player_y * 64;
	if (d == 'u')
		mlx_put_image_to_window(game->mlx, game->win, game->img[6], x, y);
	if (d == 'd')
		mlx_put_image_to_window(game->mlx, game->win, game->img[5], x, y);
	if (d == 'r')
		mlx_put_image_to_window(game->mlx, game->win, game->img[4], x, y);
	if (d == 'l')
		mlx_put_image_to_window(game->mlx, game->win, game->img[3], x, y);
}

void	print_nonmovings(t_game *game)
{
	int		x;
	int		y;
	void	*mlx;

	y = -1;
	mlx = game->mlx;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->collectible_count == game->collected)
			{
				game->map[game->exit_y][game->exit_x] = 'E';
				mlx_put_image_to_window(mlx, game->win, game->img[1],
					game->exit_x * 64, game->exit_y * 64);
			}
			if (game->map[y][x] == '1')
				mlx_put_image_to_window(mlx, game->win, game->img[7], x * 64, y
					* 64);
			if (game->map[y][x] == 'C')
				mlx_put_image_to_window(mlx, game->win, game->img[0], x * 64, y
					* 64);
		}
	}
}

void	print_bg(t_game *game)
{
	int	x;
	int	y;
	int	xx;
	int	yy;

	y = -1;
	yy = 0;
	while (game->map[++y])
	{
		x = -1;
		xx = 0;
		while (game->map[y][++x])
		{
			mlx_put_image_to_window(game->mlx, game->win, game->img[2], xx, yy);
			xx += PXL;
		}
		yy += PXL;
	}
}

void	add_images(t_game *game)
{
	int	pxl;

	pxl = PXL;
	game->img = malloc(sizeof(void *) * 8);
	game->img[0] = mlx_xpm_file_to_image(game->mlx, COLLECTIBLES, &pxl, &pxl);
	game->img[1] = mlx_xpm_file_to_image(game->mlx, DOOR, &pxl, &pxl);
	game->img[2] = mlx_xpm_file_to_image(game->mlx, BG, &pxl, &pxl);
	game->img[3] = mlx_xpm_file_to_image(game->mlx, P_LEFT, &pxl, &pxl);
	game->img[4] = mlx_xpm_file_to_image(game->mlx, P_RIGHT, &pxl, &pxl);
	game->img[5] = mlx_xpm_file_to_image(game->mlx, P_DOWN, &pxl, &pxl);
	game->img[6] = mlx_xpm_file_to_image(game->mlx, P_UP, &pxl, &pxl);
	game->img[7] = mlx_xpm_file_to_image(game->mlx, WALL, &pxl, &pxl);
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init();
	add_images(game);
	game->scr_x = (PXL * game->map_width);
	game->scr_y = (PXL * game->map_height);
	game->win = mlx_new_window(game->mlx, game->scr_x, game->scr_y, "so_long");
	print_bg(game);
	print_nonmovings(game);
	print_player(game, 'u');
}
