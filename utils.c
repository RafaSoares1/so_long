#include "so_long.h"

int	ft_len(char const *str)
{
	int	i;
	
	i = 0;
	while (str[i] !='\0')
	{
		i++;
	}
	return (i);
}

void	ft_init_stack(t_data *d)
{
	d->collect_img = 0;
	d->exit_img = 0;
	d->fd = 0;
	d->floor_img = 0;
	d->lines = 0;
	d->map = 0;
	d->mlx_ptr = 0;
	d->playera_img = 0;
	d->playerd_img = 0;
	d->playerw_img = 0;
	d->players_img = 0;
	d->wall_img = 0;
	d->win_ptr = 0;
	d->enemy_img = 0;
	d->x = 0;
	d->y = 0;
	d->p_x = 0;
	d->p_y = 0;
	d->collect = 0;
	d->moves = 0;
}

void ft_get_imgs(t_data *d)
{
	d->floor_img = mlx_xpm_file_to_image(d->mlx_ptr, FLOOR, &d->x, &d->y);
	d->wall_img = mlx_xpm_file_to_image(d->mlx_ptr, WALL, &d->x, &d->y);
	d->playera_img = mlx_xpm_file_to_image(d->mlx_ptr, PLAYERA, &d->x, &d->y);
	d->playerd_img = mlx_xpm_file_to_image(d->mlx_ptr, PLAYERD, &d->x, &d->y);
	d->playerw_img = mlx_xpm_file_to_image(d->mlx_ptr, PLAYERW, &d->x, &d->y);
	d->players_img = mlx_xpm_file_to_image(d->mlx_ptr, PLAYERS, &d->x, &d->y);
	d->exit_img = mlx_xpm_file_to_image(d->mlx_ptr, EXIT, &d->x, &d->y);
	d->collect_img = mlx_xpm_file_to_image(d->mlx_ptr, COLLECT, &d->x, &d->y);
	d->enemy_img = mlx_xpm_file_to_image(d->mlx_ptr, ENEMY, &d->x, &d->y);
}

void	ft_check_columns(char *file, t_data *d)
{
	int	i;
	char	*str;
	
	d->fd = open(file, O_RDONLY);
	while (1)
	{
		str = get_next_line(d->fd);
		if(!str)
			break;
		if (ft_len(str) <= 3)
		{
			write(2, "You will need more columns in your map!\n", 40);
			free(str);
			ft_finish2(d);
			close (d->fd);
			exit (0);
		}
		free (str);
	}
	free (str);
	close (d->fd);
}
