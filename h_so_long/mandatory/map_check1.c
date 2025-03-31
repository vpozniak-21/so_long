/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:37:24 by hceviz            #+#    #+#             */
/*   Updated: 2025/03/26 19:12:25 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	check_walls(t_game *game)
{
	int		i;

	i = 0;
	while (game->map[0][i] && game->map[game->m_height - 1][i])
	{
		if (game->map[0][i] != '1' || game->map[game->m_height - 1][i] != '1')
			ft_free_exit("ERROR\nMap is not enclosed properly!\n", game, 1);
		i++;
	}
	i = 0;
	while (game->map[i])
	{
		if (game->map[i][0] != '1' || game->map[i][game->m_width - 1] != '1')
			ft_free_exit("ERROR\nMap is not enclosed properly!\n", game, 1);
		i++;
	}
	check_members(game);
}

void	find_height(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	game->m_height = 0;
	game->fd = open(game->m_name, O_RDONLY);
	line = get_next_line(game->fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(game->fd);
	}
	game->m_height = i;
	free(line);
	line = NULL;
	close(game->fd);
}

void	is_rectangular(t_game *game)
{
	int		i;

	i = 0;
	if (game->m_width < 5 || game->m_height < 4)
		ft_free_exit("ERROR\nMap is too small!\n", game, 1);
	while (i < game->m_height - 1)
	{
		if ((int)ft_strlen(game->map[i]) != game->m_width)
			ft_free_exit("ERROR\nLines are not equal.\n", game, 1);
		i++;
	}
	if (game->m_height == game->m_width)
		ft_free_exit("ERROR\nMap is not rectangular!\n", game, 1);
	check_walls(game);
}

void	init_map(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	find_height(game);
	game->map = (char **)malloc((game->m_height + 1) * sizeof(char *));
	game->temp_map = (char **)malloc((game->m_height + 1) * sizeof(char *));
	game->fd = open(game->m_name, O_RDONLY);
	if (!game->map || !game->temp_map)
		ft_free_exit("Error\nMap allocation error!", game, 1);
	line = get_next_line(game->fd);
	while (line)
	{
		game->map[i] = line;
		game->temp_map[i] = ft_strdup(line);
		line = get_next_line(game->fd);
		i++;
	}
	free(line);
	game->map[i] = NULL;
	game->temp_map[i] = NULL;
	game->m_width = (int)ft_strlen(game->map[0]);
	close(game->fd);
	is_rectangular(game);
}

void	is_valid(t_game *game)
{
	char	*line;

	line = NULL;
	game->fd = open(game->m_name, O_RDONLY);
	if (game->fd < 0)
		ft_free_exit("ERROR\nFile is not exist.\n", game, 1);
	if (ft_strcmp((game->m_name + (ft_strlen(game->m_name) - 4)), ".ber") != 0)
		ft_free_exit("ERROR\nWrong map file extension.\n", game, 1);
	line = get_next_line(game->fd);
	if (line == NULL)
		ft_free_exit("ERROR\nEmpty file!\n", game, 1);
	free(line);
	close(game->fd);
	game->collected = 0;
	game->e_count = 0;
	game->p_count = 0;
	game->c_count = 0;
	game->movecounter = 0;
	init_map(game);
}
