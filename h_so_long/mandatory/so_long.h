/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hceviz <hceviz@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:04:26 by hceviz            #+#    #+#             */
/*   Updated: 2025/03/22 09:51:38 by hceviz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define BUFFER_SIZE 1
# define PXL 64
# define COLLECTIBLES "./textures/key.xpm"
# define ENEMY "./textures/orc.xpm"
# define DOOR "./textures/door.xpm"
# define BG "./textures/bg.xpm"
# define WALL "./textures/wall.xpm"
# define P_DOWN "./textures/p_down.xpm"
# define P_UP "./textures/p_up.xpm"
# define P_LEFT "./textures/p_left.xpm"
# define P_RIGHT "./textures/p_right.xpm"
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_ESC 65307
# define WIN_CLOSE 17

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		**img;
	char		**map;
	char		**temp_map;
	char		*m_name;
	int			fd;
	int			reached_exit;
	int			e_x;
	int			e_y;
	int			p_x;
	int			p_y;
	int			prev_x;
	int			prev_y;
	int			collected;
	int			e_count;
	int			p_count;
	int			c_count;
	int			movecounter;
	int			scr_x;
	int			scr_y;
	int			m_width;
	int			m_height;	
}				t_game;

//utils.c
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);

//utils2.c
void	ft_free(t_game *game);
void	ft_free_exit(char *msg, t_game *game, int code);
void	ft_putstr(char *str);
char	*ft_itoa(int n);

//so_long.c
void	ft_winloseprint(int is_win);

//gnl
char	*get_next_line(int fd);

//map_check1.c
void	check_walls(t_game *game);
void	find_height(t_game *game);
void	is_rectangular(t_game *game);
void	init_map(t_game *game);
void	is_valid(t_game *game);

//map_check2.c
void	validate_path(t_game *game);
void	check_path(t_game *game, int y, int x);
void	set_player_pos(t_game *game);
void	check_members(t_game *game);
void	set_exit(t_game *game);

//graphics.c
void	print_bg(t_game *game);
void	start_game(t_game *game);
void	add_images(t_game *game);
void	print_nonmovings(t_game *game);
void	print_player(t_game *game, char d);

//moves.c
void	refresh_frame(t_game *game, char d);
void	move_l_r(t_game *game, int val, char d);
void	move_u_d(t_game *game, int val, char d);
void	endgame(t_game *game, int is_win);

#endif
