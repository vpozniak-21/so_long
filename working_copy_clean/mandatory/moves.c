/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:13 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/10 19:56:16 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	move_l_r(t_game *game, int val, char d)
{
	char	**map;

	map = game->map;
	if (map[game->player_y][game->player_x + val] != '1')
	{
		map[game->player_y][game->player_x] = '0';
		game->player_x += val;
		++game->movecounter;
		if (map[game->player_y][game->player_x] == 'C')
			++game->collected;
		if (map[game->player_y][game->player_x] == 'E'
			&& game->collected == game->collectible_count)
		{
			map[game->player_y][game->player_x] = 'P';
			refresh_frame(game, d);
			sleep(1);
			ft_putstr("\nGame completed successfully!\n");
			cleanup_game(game, NULL, 0);
			return ;
		}
		map[game->player_y][game->player_x] = 'P';
		refresh_frame(game, d);
	}
}

void	move_u_d(t_game *game, int val, char d)
{
	char	**map;

	map = game->map;
	if (map[game->player_y + val][game->player_x] != '1')
	{
		map[game->player_y][game->player_x] = '0';
		game->player_y += val;
		++game->movecounter;
		if (map[game->player_y][game->player_x] == 'C')
			++game->collected;
		if (map[game->player_y][game->player_x] == 'E'
			&& game->collected == game->collectible_count)
		{
			map[game->player_y + val][game->player_x] = 'P';
			refresh_frame(game, d);
			sleep(1);
			ft_putstr("\nGame completed successfully!\n");
			cleanup_game(game, NULL, 0);
			return ;
		}
		map[game->player_y][game->player_x] = 'P';
		refresh_frame(game, d);
	}
}

void	refresh_frame(t_game *game, char d)
{
	char	*counter;
	char	*collected;

	print_bg(game);
	print_nonmovings(game);
	print_player(game, d);
	counter = ft_itoa(game->movecounter);
	collected = ft_itoa(game->collected);
	ft_putstr("Move counter: ");
	ft_putstr(counter);
	ft_putstr("		Collected: ");
	ft_putstr(collected);
	write(1, "\n", 1);
	free(counter);
	free(collected);
}
