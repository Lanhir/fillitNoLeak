/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaouad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:55:22 by cmaouad           #+#    #+#             */
/*   Updated: 2019/09/10 17:11:31 by malibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static	int		valid_map(char *map, int i, int j, int count)
{
	while (map[++i])
	{
		if (map[i] == '#')
			j++;
		if ((++count % 5) == 0 && map[i] != '\n')
			return (0);
		if (map[i] != '#' && map[i] != '.' && map[i] != '\n')
			return (0);
		if (count == 21)
		{
			if (j != 4 || map[i] != '\n')
				return (0);
			j = 0;
			count = 0;
		}
	}
	if (count != 20 || j != 4)
		return (0);
	return (1);
}

static	int		check_tetris(char *map)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while ((map[++j] != '\n' || map[j + 1] != '\n') && (map[j] != '\0'))
	{
		if (map[j] == '#')
		{
			i += (map[j - 5] == '#') ? 1 : 0;
			i += (map[j - 1] == '#') ? 1 : 0;
			i += (map[j + 1] == '#') ? 1 : 0;
			i += (map[j + 5] == '#') ? 1 : 0;
		}
	}
	if (i < 6)
		return (0);
	return (1);
}

static	char	*create_tetris_next(char *map, char *tetris, char c)
{
	int		i;

	i = -1;
	if (!(tetris = (char*)malloc(sizeof(char) * 20)))
		return (NULL);
	while ((map[++i] != '\n' || map[i + 1] != '\n') && (map[i + 1] != '\0'))
	{
		if (map[i] == '#')
			tetris[i] = c;
		else
			tetris[i] = map[i];
	}
	tetris[i] = '\0';
	return (tetris);
}

static	int		create_tetris(char *map, t_fillit *fillit)
{
	int		i;
	int		j;

	fillit->tetris_nbr = nb_tetris(map);
	j = -1;
	if (!(fillit->tetris = (char**)malloc(sizeof(char*) *
					fillit->tetris_nbr + 1)))
		return (0);
	fillit->tetris[fillit->tetris_nbr] = NULL;
	i = 0;
	while (map[++j])
	{
		if (j == 0 || (map[j] == '\n' && map[j + 1] == '\n'))
		{
			if (!(check_tetris(map + (i * 21))))
				return (0);
			if (!(fillit->tetris[i] = create_tetris_next(map + (i * 21),
					fillit->tetris[i], 'A' + i)))
				return (0);
			i++;
		}
	}
	return (1);
}

int				map_check(char *av, t_fillit *fillit)
{
	char	*map;
	int		i;

	if (!(map = map_recup(av)))
		return (0);
	if (!(valid_map(map, -1, 0, 0)))
	{
		free(map);
		return (0);
	}
	if (!(create_tetris(map, fillit)))
		return (0);
	fillit->size_map_min = ft_sqrt(fillit->tetris_nbr * 4);
	i = -1;
	while (fillit->tetris[++i])
	{
		fillit->tetris[i] = ft_push_top(fillit->tetris[i], 'A' + i, 0, 0);
		fillit->tetris[i] = ft_push_left(fillit->tetris[i]);
		fillit->tetris[i] = ft_reduce_tetris(fillit->tetris[i], -1, 0, 0);
	}
	if (map)
		free(map);
	return (1);
}
