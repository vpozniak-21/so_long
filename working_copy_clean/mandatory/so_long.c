/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:27 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/10 14:04:56 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	key_hook(int key, t_game *game)
{
	if (key == KEY_DOWN || key == KEY_S)
		move_u_d(game, 1, 'd');
	else if (key == KEY_UP || key == KEY_W)
		move_u_d(game, -1, 'u');
	else if (key == KEY_LEFT || key == KEY_A)
		move_l_r(game, -1, 'l');
	else if (key == KEY_RIGHT || key == KEY_D)
		move_l_r(game, 1, 'r');
	else if ((key == KEY_ESC) || (key == 12))
		cleanup_game(game, NULL, 0);
	return (0);
}

int	close_window_hook(t_game *game)
{
	cleanup_game(game, NULL, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		cleanup_game(game, "ERROR\nMissing or wrong parameter\n", 1);
	game = malloc(sizeof(t_game));
	if (!game)
		cleanup_game(game, "ERROR\nGame allocation failure.\n", 1);
	ft_bzero(game, sizeof(t_game));
	game->map_name = av[1];
	game->win = NULL;
	if (map_validation(game) != 0)
		cleanup_game(game, NULL, 1);
	start_game(game);
	mlx_hook(game->win, 17, 0, close_window_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
