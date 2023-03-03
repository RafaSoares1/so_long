/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:55:35 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/03 15:33:47 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_free_map(t_data *data)
{
    int i;

    i = 0;
    while (data->map[i])
    {
        free(data->map[i]);
        i++;
    }
    free(data->map);
}

int	ft_finish(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->floor_img);
	mlx_destroy_image(data->mlx_ptr, data->wall_img);
	mlx_destroy_image(data->mlx_ptr, data->playere_img);
	mlx_destroy_image(data->mlx_ptr, data->playerd_img);
	mlx_destroy_image(data->mlx_ptr, data->exit_img);
	mlx_destroy_image(data->mlx_ptr, data->collect_img);
	ft_free_map(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
}

void	ft_init_stack(t_data *t)
{
	t->collect_img = 0;
	t->exit_img = 0;
	t->fd = 0;
	t->floor_img = 0;
	t->lines = 0;
	t->map = 0;
	t->mlx_ptr = 0;
	t->playere_img = 0;
	t->wall_img = 0;
	t->win_ptr = 0;
	t->x = 0;
	t->y = 0;
	t->p_x = 0;
	t->p_y = 0;

}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == 65307)
		ft_finish (data);
	if (keysym == 119)
		ft_move_player(data, 'W');
	if (keysym == 97)
		ft_move_player(data, 'A');
	if (keysym == 115)
		ft_move_player(data, 'S');
	if (keysym == 100)
		ft_move_player(data, 'D');
	return (0);
}

int main (int argc, char **argv)
{
	(void) argc;
	t_data	data;

	ft_init_stack(&data);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr ==NULL)
		return (0);
	data.floor_img = mlx_xpm_file_to_image(data.mlx_ptr, FLOOR, &data.x, &data.y);
	data.wall_img = mlx_xpm_file_to_image(data.mlx_ptr, WALL, &data.x, &data.y);
	data.playere_img = mlx_xpm_file_to_image(data.mlx_ptr, PLAYERe, &data.x, &data.y);
	data.playerd_img = mlx_xpm_file_to_image(data.mlx_ptr, PLAYERd, &data.x, &data.y);
	data.exit_img = mlx_xpm_file_to_image(data.mlx_ptr, EXIT, &data.x, &data.y);
	data.collect_img = mlx_xpm_file_to_image(data.mlx_ptr, COLLECT, &data.x, &data.y);
	ft_read_map(&data, argv);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_input, &data);
	mlx_hook(data.win_ptr, DestroyNotify, ButtonPressMask, ft_finish, &data);
	mlx_loop(data.mlx_ptr);
}
