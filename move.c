
#include "so_long.h"

void	ft_put_image(t_data *d, int y, int x, char flag)
{
	if (flag == 'A')
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->playera_img, x * SIZE, y * SIZE);
	else if (flag == 'W')
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->playerw_img, x * SIZE, y * SIZE);
	else if (flag == 'S')
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->players_img, x * SIZE, y * SIZE);
	else
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->playerd_img, x * SIZE, y * SIZE);
}

int	ft_move_player(t_data *d, int y, int x, char flag)
{
	if (d->map[y][x] == '0' || d->map[y][x] == 'C')
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->floor_img, d->p_x * SIZE, d->p_y * SIZE);
		ft_put_image(d, y, x, flag);
		if (d->map[y][x] == 'C')
			d->collect -=1;
		d->map[d->p_y][d->p_x] = '0';
		d->map[y][x] = '0';
		d->p_y = y;
		d->p_x = x;
		d->moves++;	
		return(1);
	}
	else if (d->map[y][x] == 'E' && d->collect == 0)
	{
		ft_printf("Total Moves: %d\n", d->moves + 1);
		ft_finish (d);
	}
	return(0);
}

int	handle_input(int keysym, t_data *data)
{
	int	result;

	result = 0;
	if (keysym == 65307)
		ft_finish (data);
	if (keysym == 119)//W
		result = ft_move_player(data, data->p_y - 1, data->p_x, 'W');
	if (keysym == 97)//A
		result = ft_move_player(data, data->p_y, data->p_x - 1, 'A');
	if (keysym == 115)//S
		result = ft_move_player(data, data->p_y + 1, data->p_x, 'S');
	if (keysym == 100)//D
		result = ft_move_player(data, data->p_y, data->p_x + 1, 'D');
	if (result == 1)
		ft_printf("Move number: %d\n", data->moves);
	return (0);
}
