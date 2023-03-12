#include "so_long.h"

int	ft_finish(t_data *d)
{
	mlx_destroy_image(d->mlx_ptr, d->floor_img);
	mlx_destroy_image(d->mlx_ptr, d->wall_img);
	mlx_destroy_image(d->mlx_ptr, d->playera_img);
	mlx_destroy_image(d->mlx_ptr, d->playerd_img);
	mlx_destroy_image(d->mlx_ptr, d->playerw_img);
	mlx_destroy_image(d->mlx_ptr, d->players_img);
	mlx_destroy_image(d->mlx_ptr, d->exit_img);
	mlx_destroy_image(d->mlx_ptr, d->collect_img);
	mlx_destroy_image(d->mlx_ptr, d->enemy_img);
	ft_free_map(d);
	mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	mlx_destroy_display(d->mlx_ptr);
	free(d->mlx_ptr);
	exit(0);
}

int	ft_finish2(t_data *d)
{
	mlx_destroy_image(d->mlx_ptr, d->floor_img);
	mlx_destroy_image(d->mlx_ptr, d->wall_img);
	mlx_destroy_image(d->mlx_ptr, d->playera_img);
	mlx_destroy_image(d->mlx_ptr, d->playerd_img);
	mlx_destroy_image(d->mlx_ptr, d->playerw_img);
	mlx_destroy_image(d->mlx_ptr, d->players_img);
	mlx_destroy_image(d->mlx_ptr, d->exit_img);
	mlx_destroy_image(d->mlx_ptr, d->collect_img);
	mlx_destroy_image(d->mlx_ptr, d->enemy_img);
	mlx_destroy_display(d->mlx_ptr);
	free(d->mlx_ptr);
	exit(0);
}

void	ft_free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}
