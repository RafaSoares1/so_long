/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:55:35 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/07 16:44:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_check_map_file(t_data *d, char *file_name)
{
	int	i;

	i = 0;
	d->fd = open(file_name, O_RDONLY);
	i = ft_strlen(file_name) - 1;
	while (file_name[i] != '.')
		i--;
	if (ft_strncmp((file_name + i), ".ber", 4) != 0)
	{
		write(2,"ERROR IN FILE TYPE\n",19);
		close(d->fd);
		exit(1);
	}
	if (d->fd < 0)
	{
		write(2,"ERROR IN FD\n",12);
		close(d->fd);
		exit(1);
	}
	close(d->fd);
	d->fd = 0;
}

int main (int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
	{
		ft_printf("Please, check the input --> ./so_long <Map path>\n");
		return (0);
	}	
	ft_init_stack(&data);
	if (argc == 2)
	{
	ft_check_map_file(&data, argv[1]);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (0);
	ft_get_imgs(&data);
	ft_read_map(&data, argv);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, handle_input, &data);
	mlx_hook(data.win_ptr, DestroyNotify, ButtonPressMask, ft_finish, &data);
	mlx_loop(data.mlx_ptr);
	}
	return (0);
}
