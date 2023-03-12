/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:04:42 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/09 21:47:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_count_lines(t_data *d)
{
	int	i;
	char	*str;
	
	i = 0;
	while (1)
	{
		str = get_next_line(d->fd);
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

void	ft_fill_map_index(t_data *data)
{
	int	i;
	char *str;

	i = 0;
	while (i <= data->lines)
	{
		str = get_next_line(data->fd);
		if(!str)
		{
			free(str);
			break;
		}
		data->map[i] = ft_strtrim(str, "\n");
		free (str);
		i++;
	}
}

void	ft_fill_window(t_data * d, int i, int j)
{
	while (i < d->lines)
	{
		j = 0;
		while (d->map[i][j] != '\n' && d ->map[i][j] != '\0')
		{
			if(d->map[i][j] == '1')
				mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->wall_img, j * SIZE, i * SIZE);
			else if(d->map[i][j] == '0')
				mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->floor_img, j * SIZE, i * SIZE);
			else if(d->map[i][j] == 'C')
				mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->collect_img, j * SIZE, i * SIZE);
			else if(d->map[i][j] == 'P')
				mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->playerd_img, j * SIZE, i * SIZE);
			else if(d->map[i][j] == 'E')
				mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->exit_img, j * SIZE, i * SIZE);
			else if(d->map[i][j] == 'M')
				mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->enemy_img, j * SIZE, i * SIZE);
				j++;
		}
		i++;
	}
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

void	ft_read_map(t_data *d, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	d->fd = open(argv[1], O_RDONLY);
	d->lines = ft_count_lines(d);
	close (d->fd);
	if (d->lines < 3)
	{
		write(2, "You will need more lines in your map!\n", 38);
		ft_finish2(d);
		exit (0);
	}
	ft_check_columns(argv[1], d);
	d->fd = open(argv[1], O_RDONLY);
	d->map = ft_calloc(d->lines + 1, sizeof(char *));
	ft_fill_map_index(d);
	d->win_ptr = mlx_new_window(d->mlx_ptr, ft_len(d->map[0]) * SIZE - SIZE, d->lines * SIZE, "so_long");
	if (d->win_ptr == NULL)
  {
      free(d->win_ptr);
      return;
  }
	ft_fill_window(d, i, j);
	close (d->fd);
	ft_get_player_coordinates(d);
}
