/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:51:28 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/04 15:00:36 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "libft/libft.h"
#include "./minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <fcntl.h>
#include <unistd.h>

# define WALL "./textures/WALL.xpm"
# define FLOOR "./textures/FLOOR.xpm"
# define PLAYERA "./textures/RickA.xpm"
# define PLAYERD "./textures/RickD.xpm"
# define PLAYERW "./textures/RickW.xpm"
# define PLAYERS "./textures/RickS.xpm"
# define COLLECT "./textures/COLLECT.xpm"
# define EXIT "./textures/EXIT.xpm"
# define ENEMY "./textures/ENEMY.xpm"

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		x;
	int		y;
	void	*wall_img;
	void	*floor_img;
	void	*collect_img;
	void	*playera_img;
	void	*playerd_img;
	void	*playerw_img;
	void	*players_img;
	void	*exit_img;
	void	*enemy_img;
	int		fd;
	int		lines;
	char	**map;
	int		p_x;
	int		p_y;
	int		collect;
	int		moves;
}				t_data;



//MAP
void	ft_read_map(t_data *data, char **argv);
int		ft_count_lines(int fd);
int		ft_len (char const *str);

int	ft_move_player(t_data * d, int y, int x, char flag);
void	ft_get_player_coordinates(t_data *data);
int		ft_finish(t_data *data);

#endif