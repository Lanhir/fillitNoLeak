/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaouad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:54:05 by cmaouad           #+#    #+#             */
/*   Updated: 2019/09/11 15:53:18 by malibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static	void	ft_delete_map(t_fillit *fillit, char letter)
{
	int		i;
	int		j;

	j = 0;
	while (fillit->map[j])
	{
		i = 0;
		while (fillit->map[j][i])
		{
			if (fillit->map[j][i] == letter)
				fillit->map[j][i] = '.';
			i++;
		}
		j++;
	}
}

static	char	ft_check_letter(char *map)
{
	char	letter;
	int		i;

	i = 0;
	while (map[i])
	{
		if (ft_isalpha(map[i]))
			letter = map[i];
		i++;
	}
	return (letter);
}

static	int		put_tetris_map(t_fillit *fillit, char *tetris, int x, int y)
{
	int		i;
	int		tmp;

	i = -1;
	tmp = x;
	if (check_same_carac(fillit, tetris, x, y))
		while (tetris[++i])
		{
			if (tetris[i] == '.')
				x++;
			if (ft_isalpha(tetris[i]))
			{
				if (fillit->map[y][x] == '.')
					fillit->map[y][x++] = tetris[i];
			}
			if (tetris[i] == '\n')
			{
				y++;
				x = tmp;
			}
		}
	else
		return (0);
	return (1);
}

static	char	**ft_fillit(t_fillit *fillit, char **tetris, int x, int y)
{
	while (!(put_tetris_map(fillit, *tetris, x, y)))
	{
		x++;
		if (x > fillit->size_map_min - 1)
		{
			y++;
			x = 0;
			if (y > fillit->size_map_min - 1)
			{
				return (NULL);
			}
		}
	}
	if (*(tetris + 1))
	{
		while (!(ft_fillit(fillit, tetris + 1, 0, 0)))
		{
			ft_delete_map(fillit, ft_check_letter(*tetris));
			return (ft_fillit(fillit, tetris, ++x, y));
		}
	}
	return (fillit->map);
}

void			ft_resolve(t_fillit *fillit)
{
	int		i;

	i = -1;
	fillit->map = ft_creat_map(fillit);
	while ((ft_fillit(fillit, fillit->tetris, 0, 0)) == NULL)
	{
		ft_free(fillit->map);
		fillit->size_map_min++;
		fillit->map = ft_creat_map(fillit);
	}
	while (fillit->map[++i])
		ft_putstr(fillit->map[i]);
	ft_free(fillit->map);
	ft_free(fillit->tetris);
}
