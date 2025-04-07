/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:38:23 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/07 13:38:24 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./so_long_bonus.h"

void	ft_winloseprint(int is_win)
{
	char	*line;
	char	*file;
	int		fd;

	if (is_win == 1)
		file = "./victory.txt";
	else if (is_win == 0)
		file = "./gameover.txt";
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_putstr(line);
		write(1, "\n", 1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	key_hook(int key, t_game *game)
{
	if (key == KEY_DOWN)
		move_u_d(game, 1, 'd');
	else if (key == KEY_UP)
		move_u_d(game, -1, 'u');
	else if (key == KEY_LEFT)
		move_l_r(game, -1, 'l');
	else if (key == KEY_RIGHT)
		move_l_r(game, 1, 'r');
	else if (key == KEY_ESC)
		endgame(game, 0);
	else if (key == 12) // if q is pressed the the game quits
		endgame(game, 0);
	return (0);
}

int	close_window_hook(t_game *game)
{
	endgame(game, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		ft_free_exit("ERROR\nMissing or wrong parameter\n", game, 1);
	game = malloc(sizeof(t_game));
	if (!game)
		ft_free_exit("ERROR\nGame allocation failure.\n", game, 1);
	game->m_name = av[1];
	game->win = NULL;
	is_valid(game);
	start_game(game);
	mlx_hook(game->win, 17, 0, close_window_hook, game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_string_put(game->mlx, game->win, game->scr_x - 130, game->scr_y - 50,
		0xFFFFFF, "Move Counter: ");
	mlx_loop(game->mlx);
	return (0);
}
