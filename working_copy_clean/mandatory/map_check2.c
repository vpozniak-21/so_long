/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:08 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/10 18:56:08 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	set_exit(t_game *game)
{
	int		x;
	int		y;
	char	**map;

	map = game->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'E')
			{
				game->exit_x = x;
				game->exit_y = y;
			}
		}
	}
}

int	validate_path(t_game *game)
{
	char	**map;
	int		row;
	int		column;

	map = game->temp_map;
	column = 0;
	while (map[column])
	{
		row = 0;
		while (map[column][row])
		{
			if (map[column][row] != '1')
				cleanup_game(game, "ERROR\nPath is not accessible!\n", 1);
			row++;
		}
		column++;
	}
	game->collected = 0;
	set_exit(game);
	return (0);
}

void	check_path(t_game *game, int y, int x)
{
	if (game->temp_map[y][x] == '1')
		return ;
	if (game->temp_map[y][x] == 'E')
		game->reached_exit = 1;
	if (game->temp_map[y][x] == 'C')
		game->collected++;
	game->temp_map[y][x] = '1';
	check_path(game, y + 1, x);
	check_path(game, y - 1, x);
	check_path(game, y, x + 1);
	check_path(game, y, x - 1);
}

void	set_player_pos(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
	check_path(game, game->player_y, game->player_x);
	validate_path(game);
}

void	check_members_of_map(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] != '0' && game->map[i][j] != '1'
				&& game->map[i][j] != 'C' && game->map[i][j] != 'E'
				&& game->map[i][j] != 'P')
				cleanup_game(game, "ERROR\nForbidden letter in the map!\n", 1);
			if (game->map[i][j] == 'E')
				game->exit_count++;
			else if (game->map[i][j] == 'P')
				game->player_count++;
			else if (game->map[i][j] == 'C')
				game->collectible_count++;
		}
	}
	if (game->collectible_count < 1 || game->player_count != 1
		|| game->exit_count != 1)
		cleanup_game(game, "ERROR\nMissing and/or wrong map characters!\n", 1);
	set_player_pos(game);
}
