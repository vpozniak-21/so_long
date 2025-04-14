/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:04 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/14 15:14:04 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"
#include <stdio.h>

int	map_check_if_walls(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[0][i] && game->map[game->map_height - 1][i])
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
			cleanup_game(game, "ERROR\nMap is not enclosed properly!\n", 1);
		i++;
	}
	i = 0;
	while (game->map[i])
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			cleanup_game(game, "ERROR\nMap is not enclosed properly!\n", 1);
		i++;
	}
	check_members_of_map(game);
	return (0);
}

void	find_height(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	game->map_height = 0;
	game->fd = open(game->map_name, O_RDONLY);
	line = get_next_line(game->fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(game->fd);
	}
	game->map_height = i;
	free(line);
	line = NULL;
	close(game->fd);
}

int	map_check_if_rectangular(t_game *game)
{
	int	i;

	i = 0;
	if (game->map_width < 5 || game->map_height < 4)
		cleanup_game(game, "ERROR\nMap is too small!\n", 1);
	while (i < game->map_height - 1)
	{
		if ((int)ft_strlen(game->map[i]) != game->map_width)
			cleanup_game(game, "ERROR\nLines are not equal.\n", 1);
		i++;
	}
	if (game->map_height == game->map_width)
		cleanup_game(game, "ERROR\nMap is not rectangular!\n", 1);
	map_check_if_walls(game);
	return (0);
}

int	map_initialization(t_game *game)
{
	char	*line;
	int		i;
	// size_t	len;

	i = 0;
	find_height(game);
	game->map = (char **)malloc((game->map_height + 1) * sizeof(char *));
	game->temp_map = (char **)malloc((game->map_height + 1) * sizeof(char *));
	game->fd = open(game->map_name, O_RDONLY);
	if (!game->map || !game->temp_map)
		cleanup_game(game, "Error\nMap allocation error!", 1);
	line = get_next_line(game->fd);
	while (line)
	{
		game->map[i] = line;
		game->temp_map[i] = ft_strdup(line);
		// printf("Line %d: [%s] (len=%zu)\n", i, game->map[i],
		ft_strlen(game->map[i]);
		line = get_next_line(game->fd);
		i++;
	}
	free(line);
	game->map[i] = NULL;
	game->temp_map[i] = NULL;
	game->map_width = (int)ft_strlen(game->map[0]);
	// len = ft_strlen(game->map[0]);
	// if (len > 0 && game->map[0][len - 1] == '\n')
	// 	len--;
	// game->map_width = len;
	close(game->fd);
	map_check_if_rectangular(game);
	return (0);
}

int	map_validation(t_game *game)
{
	char	*line;

	line = NULL;
	game->fd = open(game->map_name, O_RDONLY);
	if (game->fd < 0)
		cleanup_game(game, "ERROR\nFile does not exist.\n", 1);
	if (ft_strcmp((game->map_name + (ft_strlen(game->map_name) - 4)),
			".ber") != 0)
		cleanup_game(game, "ERROR\nWrong map file extension.\n", 1);
	line = get_next_line(game->fd);
	if (line == NULL)
		cleanup_game(game, "ERROR\nEmpty file!\n", 1);
	free(line);
	close(game->fd);
	game->collected = 0;
	game->exit_count = 0;
	game->player_count = 0;
	game->collectible_count = 0;
	game->movecounter = 0;
	map_initialization(game);
	return (0);
}
