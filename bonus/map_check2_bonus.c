/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:38:13 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/07 13:38:14 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./so_long_bonus.h"

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
				game->e_x = x;
				game->e_y = y;
			}
		}
	}
}

void	validate_path(t_game *game)
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
				ft_free_exit("ERROR\nPath is not accessible!\n", game, 1);
			row++;
		}
		column++;
	}
	game->collected = 0;
	set_exit(game);
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
				game->p_x = x;
				game->p_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
	check_path(game, game->p_y, game->p_x);
	validate_path(game);
}

void	check_members(t_game *game)
{
	char	**map;
	char	*row;

	map = game->map;
	while (*map)
	{
		row = *map;
		while (*row)
		{
			if (*row != '0' && *row != '1' && *row != 'Z'
				&& *row != 'C' && *row != 'E' && *row != 'P')
				ft_free_exit("ERROR\nForbidden letter in the map!\n", game, 1);
			if (*row == 'E')
				++game->e_count;
			else if (*row == 'P')
				++game->p_count;
			else if (*row == 'C')
				++game->c_count;
			row++;
		}
		map++;
	}
	if (game->c_count < 1 || game->p_count != 1 || game->e_count != 1)
		ft_free_exit("ERROR\nMissing and/or wrong map characters!\n", game, 1);
	set_player_pos(game);
}
