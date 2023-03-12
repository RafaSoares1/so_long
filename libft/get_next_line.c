/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:35:39 by emsoares          #+#    #+#             */
/*   Updated: 2023/03/01 18:28:31 by emsoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*start_next_stash(char *stash)
{
	char	*reserve;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	reserve = ft_calloc((ft_strlen(stash) - i + 1), sizeof(char));
	i++;
	while (stash[i])
	{
		reserve[j] = stash[i];
		j++;
		i++;
	}
	free (stash);
	return (reserve);
}

char	*print_line(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	str = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		str[i] = '\n';
	return (str);
}

char	*ft_free(char *stash, char *temp)
{
	char	*final;

	final = ft_strjoin(stash, temp);
	free (stash);
	return (final);
}

char	*find_line(char *stash, int fd)
{
	char	*temp;
	int		count_char;

	if (!stash)
		stash = ft_calloc(1, 1);
	temp = ft_calloc ((BUFFER_SIZE + 1), sizeof(char));
	count_char = 1;
	while (!ft_strchr(stash, '\n') && count_char != 0)
	{
		count_char = read (fd, temp, BUFFER_SIZE);
		if (count_char == -1)
		{
			free (temp);
			free (stash);
			return (NULL);
		}
		temp [count_char] = '\0';
		stash = ft_free(stash, temp);
	}
	free (temp);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = find_line(stash, fd);
	if (!stash)
		return (NULL);
	line = print_line(stash);
	stash = start_next_stash(stash);
	return (line);
}

/* int	main(void)
{
	char	*str;
	int		i;
	int		fd;
	
	fd = open("test2.txt", O_RDONLY);
	i = 1;
	while (i <= 6)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	close(fd);
	return (0);
}*/
