/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonct.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaouad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:52:09 by cmaouad           #+#    #+#             */
/*   Updated: 2019/09/10 16:41:43 by malibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		nb_tetris(char *map)
{
	int i;

	i = 0;
	while (*map++)
		if (*map == '\n')
			i++;
	i = (i + 1) / 5;
	if (i >= 26)
		return (0);
	return (i);
}

int		ft_sqrt(int nb)
{
	int root;

	root = 0;
	while (root * root < nb)
		root++;
	if (root * root >= nb)
		return (root);
	return (0);
}

char	*map_recup(char *av)
{
	int		ret;
	int		fd;
	char	*map;
	char	buff[BUFF_SIZE + 1];

	if (!(map = (char*)malloc(sizeof(char) * 1)))
		return (NULL);
	map[0] = '\0';
	if ((fd = open(av, O_RDONLY)) == -1)
	{
		free(map);
		return (NULL);
	}
	while ((ret = read(fd, buff, BUFF_SIZE)) != 0)
	{
		buff[ret] = '\0';
		if (!(map = ft_strjoin_free(map, buff)))
		{
			free(map);
			return (NULL);
		}
	}
	close(fd);
	return (map);
}
