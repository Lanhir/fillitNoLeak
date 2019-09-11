/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaouad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:52:53 by cmaouad           #+#    #+#             */
/*   Updated: 2019/09/11 15:53:27 by malibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		ft_free(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
	}
	free(tab);
}

char		**ft_creat_map(t_fillit *fillit)
{
	char	**ret;
	int		i;
	int		j;

	if (!(ret = (char**)malloc(sizeof(char*) * fillit->size_map_min + 1)))
		return (NULL);
	i = -1;
	while (++i < fillit->size_map_min)
	{
		ret[i] = ft_strnew(fillit->size_map_min + 1);
		j = -1;
		while (++j < fillit->size_map_min)
			ret[i][j] = '.';
		ret[i][fillit->size_map_min] = '\n';
	}
	ret[fillit->size_map_min] = NULL;
	return (ret);
}

int			check_same_carac(t_fillit *fillit, char *tetris, int x, int y)
{
	int		i;
	int		tmp;

	i = -1;
	tmp = x;
	while (tetris[++i])
	{
		if (ft_isalpha(fillit->map[y][x]) && ft_isalpha(tetris[i]))
			return (0);
		if (tetris[i] != '\n')
			x++;
		if (x > fillit->size_map_min)
			return (0);
		if (tetris[i] == '\n')
		{
			y++;
			x = tmp;
			if (y > fillit->size_map_min - 1)
				return (0);
		}
	}
	return (1);
}
