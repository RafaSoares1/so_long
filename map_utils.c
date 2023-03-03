/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:04:42 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/03 15:44:42 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_move_player(t_data * data, char flag)
{
	if (flag == 'W' && (data->map[data->p_x][data->p_y - 1] == 'C' || data->map[data->p_x][data->p_y - 1] == '0'))
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor_img, data->p_x * 64, data->p_y * 64);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->playerd_img, data->p_x * 64, (data->p_y - 1) * 64);
		data->p_y -= 1;
	}
	if (flag == 'A' && (data->map[data->p_x - 1][data->p_y] == 'C' || data->map[data->p_x - 1][data->p_y] == '0'))
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor_img, data->p_x * 64, data->p_y * 64);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->playerd_img, (data->p_x - 1) * 64, data->p_y * 64);
		data->p_x -= 1;
	}
	if (flag == 'S' && (data->map[data->p_x][data->p_y + 1] == 'C' || data->map[data->p_x][data->p_y + 1] == '0'))
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor_img, data->p_x * 64, data->p_y * 64);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->playerd_img, data->p_x * 64, (data->p_y + 1) * 64);
		data->p_y += 1;
	}
	if (flag == 'D' && (data->map[data->p_x + 1][data->p_y] == 'C' || data->map[data->p_x + 1][data->p_y] == '0'))
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->floor_img, data->p_x * 64, data->p_y * 64);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->playerd_img, (data->p_x + 1) * 64, data->p_y  * 64);
		data->p_x += 1;
	}
}

void	ft_get_player_cordinates(t_data *data)
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
			j++;
		}
		i++;
	}
}

int ft_len (char *str)
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
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->playere_img, j * 64, i * 64);
			else if(data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit_img, j * 64, i * 64);
			j++;
		}
		i++;
	}
	close (data->fd);
	ft_get_player_cordinates(data);
}
