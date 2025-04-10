/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:47 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/10 20:03:18 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

// void	cleanup_game(t_game *game, const char *msg, int exit_code)
// {
// 	int	i;

// 	if (msg)
// 		ft_putstr(msg);
// 	if (!game)
// 		exit(exit_code);
// 	if (game->map)
// 	{
// 		i = 0;
// 		while (i < game->map_height && game->map[i])
// 		{
// 			free(game->map[i]);
// 			i++;
// 		}
// 		free(game->map);
// 	}
// 	if (game->temp_map)
// 	{
// 		i = 0;
// 		while (i < game->map_height && game->temp_map[i])
// 		{
// 			free(game->temp_map[i]);
// 			i++;
// 		}
// 		free(game->temp_map);
// 	}
// 	if (game->img)
// 	{
// 		i = 0;
// 		while (i < 8 && game->img[i])
// 		{
// 			mlx_destroy_image(game->mlx, game->img[i]);
// 			i++;
// 		}
// 		free(game->img);
// 	}
// 	if (game->win)
// 		mlx_destroy_window(game->mlx, game->win);
// 	if (game->mlx)
// 		free(game->mlx);
// 	free(game);
// 	exit(exit_code);
// }
void	cleanup_game(t_game *game, const char *msg, int exit_code)
{
	int	i;

	if (msg)
		ft_putstr(msg);
	if (!game)
		exit(exit_code);
	i = 0;
	while (game->map && i < game->map_height && game->map[i])
		free(game->map[i++]);
	free(game->map);
	i = 0;
	while (game->temp_map && i < game->map_height && game->temp_map[i])
		free(game->temp_map[i++]);
	free(game->temp_map);
	i = 0;
	while (game->img && i < 8 && game->img[i])
		mlx_destroy_image(game->mlx, game->img[i++]);
	free(game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	free(game);
	exit(exit_code);
}

void	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
}

size_t	get_digits(int n)
{
	size_t	i;

	i = 1;
	n /= 10;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str_num;
	size_t	digits;
	int		num;

	num = n;
	digits = get_digits(n);
	if (n < 0)
	{
		num *= -1;
		digits++;
	}
	str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str_num)
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str_num + 0) = '-';
	return (str_num);
}
