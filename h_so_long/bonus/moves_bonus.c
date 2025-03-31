/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:12:11 by hceviz            #+#    #+#             */
/*   Updated: 2025/03/14 15:02:28 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"
//if (map[game->p_y + val][game->p_x] == 'C'
//|| map[game->p_y + val][game->p_x] == 'E'
//|| map[game->p_y + val][game->p_x] == '0')

void	endgame(t_game *game, int is_win)
{
	int	i;

	if (game->img)
	{
		i = -1;
		while (++i < 18)
			mlx_destroy_image(game->mlx, game->img[i]);
		free(game->img);
	}
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_loop_end(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (is_win == 1)
		ft_winloseprint(1);
	else if (is_win == 0)
		ft_winloseprint(0);
	ft_free_exit("", game, 0);
}

void	move_l_r(t_game *game, int val, char d)
{
	char	**map;

	map = game->map;
	if (map[game->p_y][game->p_x + val] != '1')
	{
		map[game->p_y][game->p_x] = '0';
		++game->movecounter;
		if (map[game->p_y][game->p_x + val] == 'Z')
			orc_attack(game, val, 'x');
		game->p_x += val;
		if (map[game->p_y][game->p_x] == 'C')
			++game->collected;
		if (map[game->p_y][game->p_x] == 'E'
		&& game->collected == game->c_count)
		{
			map[game->p_y][game->p_x] = 'P';
			refresh_frame(game, d);
			endgame(game, 1);
		}
		map[game->p_y][game->p_x] = 'P';
		refresh_frame(game, d);
	}
}

void	move_u_d(t_game *game, int val, char d)
{
	char	**map;

	map = game->map;
	if (map[game->p_y + val][game->p_x] != '1')
	{
		map[game->p_y][game->p_x] = '0';
		++game->movecounter;
		if (map[game->p_y + val][game->p_x] == 'Z')
			orc_attack(game, val, 'y');
		game->p_y += val;
		if (map[game->p_y][game->p_x] == 'C')
			++game->collected;
		if (map[game->p_y][game->p_x] == 'E'
		&& game->collected == game->c_count)
		{
			map[game->p_y + val][game->p_x] = 'P';
			refresh_frame(game, d);
			endgame(game, 1);
		}
		map[game->p_y][game->p_x] = 'P';
		refresh_frame(game, d);
	}
}

void	refresh_frame(t_game *game, char d)
{
	char	*counter;
	char	*collected;

	print_bg(game);
	print_nonmovings(game);
	add_enemy(game);
	print_player(game, d);
	screen_text(game);
	counter = ft_itoa(game->movecounter);
	collected = ft_itoa(game->collected);
	ft_putstr("Move counter-> ");
	ft_putstr(counter);
	ft_putstr("		Collected-> ");
	ft_putstr(collected);
	write(1, "\n", 1);
	free(counter);
	free(collected);
}
