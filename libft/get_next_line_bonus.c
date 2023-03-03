/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsoares <emsoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:17:29 by emsoares          #+#    #+#             */
/*   Updated: 2022/11/29 13:19:40 by emsoares         ###   ########.fr       */
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
	static char	*stash [FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (0);
	stash[fd] = find_line(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = print_line(stash[fd]);
	stash[fd] = start_next_stash(stash[fd]);
	return (line);
}

/* int	main(void)
{
	char	*line;
	char	*line2;
	int		i;
	int		fd1;
	int		fd2;
	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	i = 0;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf(" %s", line);
		free(line);
		line2 = get_next_line(fd2);
		printf("%s", line2);
		free(line2);
		i++;
	}
	close(fd1);
	close(fd2);
	return (0);
} */
