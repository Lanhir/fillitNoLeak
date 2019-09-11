/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaouad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:53:29 by cmaouad           #+#    #+#             */
/*   Updated: 2019/09/02 17:44:41 by cmaouad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char			*ft_reduce_tetris(char *str, int i, int j, int link)
{
	char	*tmp;

	tmp = ft_strnew(20);
	while (str[++i])
	{
		while (!ft_isalpha(str[i]) && str[i])
			tmp[j++] = str[i++];
		if (ft_isalpha(str[i]) && str[i])
		{
			while (ft_isalpha(str[i]) && str[i])
			{
				tmp[j++] = str[i++];
				link++;
			}
			if (link < 4)
				tmp[j++] = '\n';
			while (!ft_isalpha(str[i]) && str[i] && str[i] != '\n')
				i++;
		}
		if (link == 4)
			tmp[j++] = '\0';
	}
	free(str);
	return (tmp);
}

static	char	*ft_str_char(char *tmp, int i, int j, char c)
{
	while (i < j)
	{
		tmp[i] = c;
		tmp[i + 5] = c;
		tmp[i + 10] = c;
		tmp[i + 15] = c;
		i++;
	}
	return (tmp);
}

char			*ft_push_left(char *tetris)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strnew(20);
	while (tetris[i] == '.' && tetris[i + 5] == '.' && tetris[i + 10]
			== '.' && tetris[i + 15] == '.')
		i++;
	while ((ft_isalpha(tetris[i]) || ft_isalpha(tetris[i + 5]) ||
		ft_isalpha(tetris[i + 10]) || ft_isalpha(tetris[i + 15])) || i < 4)
	{
		tmp[j] = tetris[i];
		tmp[j + 5] = tetris[i + 5];
		tmp[j + 10] = tetris[i + 10];
		tmp[j + 15] = tetris[i + 15];
		i++;
		j++;
	}
	tmp = ft_str_char(tmp, j, 4, '.');
	tmp = ft_str_char(tmp, 4, 5, '\n');
	tmp[19] = '\0';
	free(tetris);
	return (tmp);
}

char			*ft_push_top(char *tetris, char letter, int i, int y)
{
	while (tetris[i] != letter)
		i++;
	if (i < 4)
	{
		while (y != 4)
			if (tetris[i++] == letter)
				y++;
		while (i < 19)
		{
			if (i == 4 || i == 9 || i == 14)
				tetris[i++] = '\n';
			else
				tetris[i++] = '.';
		}
	}
	else
	{
		i -= (i - 5);
		while (i < 20)
			tetris[y++] = tetris[i++];
		return (ft_push_top(tetris, letter, 0, 0));
	}
	return (tetris);
}
