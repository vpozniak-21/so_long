/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mac.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:22 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/14 13:29:58 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_MAC_H
# define SO_LONG_MAC_H

# include "../minilibx-mac/mlx.h"
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# define PXL 64
# define COLLECTIBLES "./textures/WARM.xpm"
# define DOOR "./textures/RAINBOW.xpm"
# define BG "./textures/BACKGROUND.xpm"
# define WALL "./textures/GRASS.xpm"
# define P_DOWN "./textures/P_D.xpm"
# define P_UP "./textures/P_U.xpm"
# define P_LEFT "./textures/P_L.xpm"
# define P_RIGHT "./textures/P_R.xpm"
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	**img;
	char	**map;
	char	**temp_map;
	char	*map_name;
	int		fd;
	int		reached_exit;
	int		exit_x;
	int		exit_y;
	int		player_x;
	int		player_y;
	// int		prev_x;
	// int		prev_y;
	int		collected;
	int		exit_count;
	int		player_count;
	int		collectible_count;
	int		movecounter;
	int		scr_x;
	int		scr_y;
	int		map_width;
	int		map_height;
	// int		should_exit;
}			t_game;

// utils.c
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlen(char *s);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(char *s, int c);

// utils2.c
void		cleanup_game(t_game *game, const char *msg, int exit_code);
void		ft_putstr(const char *str);
char		*ft_itoa(int n);

// so_long.c

// gnl
char		*get_next_line(int fd);
void		ft_bzero(void *s, size_t n);
char 		*extract_line(char **saved_text);

// map_check1.c
int			map_validation(t_game *game);
int			map_initialization(t_game *game);
int			map_check_if_rectangular(t_game *game);
int			map_check_if_walls(t_game *game);

// map_check2.c
int			validate_path(t_game *game);
void		check_path(t_game *game, int y, int x);
void		set_player_pos(t_game *game);
void		check_members_of_map(t_game *game);
void		set_exit(t_game *game);

// graphics.c
void		print_bg(t_game *game);
void		start_game(t_game *game);
void		add_images(t_game *game);
void		print_nonmovings(t_game *game);
void		print_player(t_game *game, char d);

// moves.c
void		refresh_frame(t_game *game, char d);
void		move_l_r(t_game *game, int val, char d);
void		move_u_d(t_game *game, int val, char d);

#endif
