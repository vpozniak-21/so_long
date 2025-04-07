/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:38:02 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/07 13:38:03 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./so_long_bonus.h"

void	add_enemy(t_game *game)
{
	char	**map;
	int		x;
	int		y;

	map = game->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'Z')
				mlx_put_image_to_window(game->mlx, game->win, game->img[9],
					x * 64, y * 64);
		}
	}
}

void	screen_text(t_game *game)
{
	char	*move;
	char	*collected;

	move = ft_itoa(game->movecounter);
	collected = ft_itoa(game->collected);
	mlx_string_put(game->mlx, game->win, game->scr_x - 130,
		game->scr_y - 50, 0xFFFFFF, "Move Counter: ");
	mlx_string_put(game->mlx, game->win, game->scr_x - 40,
		game->scr_y - 50, 0xFFFFFF, move);
	mlx_string_put(game->mlx, game->win, game->scr_x - 120,
		game->scr_y - 20, 0xFFFFFF, "Collected: ");
	mlx_string_put(game->mlx, game->win, game->scr_x - 40,
		game->scr_y - 20, 0xFFFFFF, collected);
	free(move);
	free(collected);
}

void	orc_attack(t_game *game, int val, char xory)
{
	int	i;

	i = 14;
	while (++i <= 17 && xory == 'x')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img[i],
			(game->p_x + val) * 64, game->p_y * 64);
		usleep(400000);
		mlx_do_sync(game->mlx);
	}
	while (++i <= 17 && xory == 'y')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img[i],
			game->p_x * 64, (game->p_y + val) * 64);
		usleep(400000);
		mlx_do_sync(game->mlx);
	}
	add_enemy(game);
	die_animation(game, xory);
}

void	die_animation(t_game *game, char xory)
{
	int	x;
	int	y;

	y = 8;
	x = 11;
	while (x <= 14 && y != 0)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->img[x],
			game->p_x * 64, game->p_y * 64);
		usleep(500000);
		mlx_do_sync(game->mlx);
		x++;
		--y;
		(x == 15) && (x = 11);
	}
	if (xory == 'y')
		mlx_put_image_to_window(game->mlx, game->win, game->img[10],
			game->p_x * 64, game->p_y * 64);
	else if (xory == 'x')
		mlx_put_image_to_window(game->mlx, game->win, game->img[10],
			game->p_x * 64, game->p_y * 64);
	mlx_do_sync(game->mlx);
	sleep(2);
	endgame(game, 0);
}
