/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:04:42 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/04 14:56:07 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_move_player(t_data * d, int y, int x, char flag)
{
	if (d->map[y][x] == '0' || d->map[y][x] == 'C')
	{
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->floor_img, d->p_x * 64, d->p_y * 64);
		if (flag == 'A')
			mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->playera_img, x * 64, y * 64);
		if (flag == 'W')
			mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->playerw_img, x * 64, y * 64);
		if (flag == 'S')
			mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->players_img, x * 64, y * 64);
		else
			mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->playerd_img, x * 64, y * 64);
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

void	ft_get_player_coordinates(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < data->lines)
	{
		j = 0;
		while(data->map[i][j])
		{
			if (data->map[i][j] == 'P')
			{
				data->p_x = j;
				data->p_y = i;
			}
			if (data->map[i][j] == 'C')
				data->collect++;
			j++;
		}
		i++;
	}
}

int ft_len (char const *str)
{
    int i;

    i = 0;

    while (str[i] !='\0')
    {
        i++;
    }
    return (i);
}

int	ft_count_lines(int fd)
{
	int	i;
	char *str;
	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if(!str)
		{
			break;
		}
		free(str);
		i++;
	}
	free (str);
	return (i);
}

void	ft_read_map(t_data *data, char **argv)
{
	data->fd = open(argv[1], O_RDONLY);
	int i = 0;
	int j = 0;

	data->lines = ft_count_lines(data->fd);
	close (data->fd);
	data->fd = open(argv[1], O_RDONLY);
	data->map = ft_calloc(data->lines + 1, sizeof(char *));
	while (i <= data->lines)
	{
		data->map[i] = get_next_line(data->fd);
		if(!data->map[i])
		{
			free(data->map[i]);
			break;
		}
		i++;
	}
	i = 0;
	data->win_ptr = mlx_new_window(data->mlx_ptr, ft_len(data->map[0]) * 64 - 64, data->lines * 64, "so_long");
	if (data->win_ptr ==NULL)
    {
        free(data->win_ptr);
        return;
    }
	while (i < data->lines)
	{
		j = 0;
		while (data->map[i][j] != '\n' && data ->map[i][j] != '\0')
		{
			if(data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall_img, j * 64, i * 64);
			else if(data->map[i][j] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor_img, j * 64, i * 64);
			else if(data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->collect_img, j * 64, i * 64);
			else if(data->map[i][j] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->playerd_img, j * 64, i * 64);
			else if(data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_img, j * 64, i * 64);
			else if(data->map[i][j] == 'M')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->enemy_img, j * 64, i * 64);
			j++;
		}
		i++;
	}
	close (data->fd);
	ft_get_player_coordinates(data);
}
