/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_mac.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:22 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/07 21:47:38 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*Replace Internal MiniLibX Functions If you are using functions like mlx
_loop_end or mlx_destroy_display(which are defined in mlx_int.h),
	you need to replace them with alternatives from the public API of MiniLibX
		.For example :
	Use mlx_destroy_window to destroy the window.Use a custom flag to
	break out of the event loop instead of mlx_loop_end.
void	endgame(t_game *game, int is_win)
{
	if (is_win)
		ft_putstr("You win!\n");
	else
		ft_putstr("Game over!\n");
	mlx_destroy_window(game->mlx, game->win);
	free(game->mlx);  // Free the mlx instance if needed
	exit(0);
}
*/

/*# include "../minilibx-mac/mlx_int.h"
functions mlx_loop_end and mlx_destroy are being redefined
because they are both in
mlx_int.h and mlx.h, causing a conflict*/

#ifndef SO_LONG_MAC_H
# define SO_LONG_MAC_H

# include "../minilibx-mac/mlx.h"
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
// # include "../minilibx-mac/mlx_int.h"

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1
# define PXL 64
# define COLLECTIBLES "./textures/WARM.xpm"
//# define ENEMY "./textures/orc.xpm"- FOR BONUS
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
# define KEY_Q 12

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	**img;
	char	**map;
	char	**temp_map;
	char	*m_name;
	int		fd;
	int		reached_exit;
	int		e_x;
	int		e_y;
	int		p_x;
	int		p_y;
	int		prev_x;
	int		prev_y;
	int		collected;
	int		e_count;
	int		p_count;
	int		c_count;
	int		movecounter;
	int		scr_x;
	int		scr_y;
	int		m_width;
	int		m_height;
	int running; // to control the event
	// loop for mac instead of destroy display
}			t_game;

// utils.c
int			ft_strcmp(char *s1, char *s2);
size_t		ft_strlen(char *s);
char		*ft_strdup(char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(char *s, int c);

// utils2.c
void		ft_free(t_game *game);
void		ft_free_exit(char *msg, t_game *game, int code);
void		ft_putstr(char *str);
char		*ft_itoa(int n);

// so_long.c
void		ft_winloseprint(int is_win);

// gnl
char		*get_next_line(int fd);

// map_check1.c
void		check_walls(t_game *game);
void		find_height(t_game *game);
void		is_rectangular(t_game *game);
void		init_map(t_game *game);
void		is_valid(t_game *game);

// map_check2.c
void		validate_path(t_game *game);
void		check_path(t_game *game, int y, int x);
void		set_player_pos(t_game *game);
void		check_members(t_game *game);
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
void		endgame(t_game *game, int is_win);

#endif
