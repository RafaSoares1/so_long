/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:55:35 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/04 14:58:37 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_get_imgs(t_data *data)
{
	data->floor_img = mlx_xpm_file_to_image(data->mlx_ptr, FLOOR, &data->x, &data->y);
	data->wall_img = mlx_xpm_file_to_image(data->mlx_ptr, WALL, &data->x, &data->y);
	data->playera_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYERA, &data->x, &data->y);
	data->playerd_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYERD, &data->x, &data->y);
	data->playerw_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYERW, &data->x, &data->y);
	data->players_img = mlx_xpm_file_to_image(data->mlx_ptr, PLAYERS, &data->x, &data->y);
	data->exit_img = mlx_xpm_file_to_image(data->mlx_ptr, EXIT, &data->x, &data->y);
	data->collect_img = mlx_xpm_file_to_image(data->mlx_ptr, COLLECT, &data->x, &data->y);
	data->enemy_img = mlx_xpm_file_to_image(data->mlx_ptr, ENEMY, &data->x, &data->y);
}

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
	mlx_destroy_image(data->mlx_ptr, data->playera_img);
	mlx_destroy_image(data->mlx_ptr, data->playerd_img);
	mlx_destroy_image(data->mlx_ptr, data->playerw_img);
	mlx_destroy_image(data->mlx_ptr, data->players_img);
	mlx_destroy_image(data->mlx_ptr, data->exit_img);
	mlx_destroy_image(data->mlx_ptr, data->collect_img);
	mlx_destroy_image(data->mlx_ptr, data->enemy_img);
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
	t->playera_img = 0;
	t->playerd_img = 0;
	t->playerw_img = 0;
	t->players_img = 0;
	t->wall_img = 0;
	t->win_ptr = 0;
	t->enemy_img = 0;
	t->x = 0;
	t->y = 0;
	t->p_x = 0;
	t->p_y = 0;
	t->collect = 0;
	t->moves = 0;
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

int main (int argc, char **argv)
{
	(void) argc;
	t_data	data;

	ft_init_stack(&data);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr ==NULL)
		return (0);
	ft_get_imgs(&data);
	ft_read_map(&data, argv);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_input, &data);
	mlx_hook(data.win_ptr, DestroyNotify, ButtonPressMask, ft_finish, &data);
	mlx_loop(data.mlx_ptr);
}
