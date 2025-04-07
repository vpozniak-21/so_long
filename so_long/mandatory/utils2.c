/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:47 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/07 13:39:48 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./so_long.h"

void	ft_free(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->m_height)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map[i]);
	free(game->map);
	i = 0;
	while (i < game->m_height)
	{
		free(game->temp_map[i]);
		i++;
	}
	free(game->temp_map[i]);
	free(game->temp_map);
	free(game);
}

void	ft_free_exit(char *msg, t_game *game, int code)
{
	ft_putstr(msg);
	if (game)
	{
		if (game->map)
			ft_free(game);
		else
			free(game);
	}
	exit(code);
}

void	ft_putstr(char *str)
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
