/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaouad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:54:38 by cmaouad           #+#    #+#             */
/*   Updated: 2019/09/10 18:07:10 by malibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		main(int ac, char **av)
{
	t_fillit	fillit;

	if (ac < 2)
		ft_putstr("Zero means there are no arguments here.\n");
	else if (ac > 2)
		ft_putstr("How did you failed that?\n");
	else
	{
		if (!(map_check(av[1], &fillit)))
		{
			ft_putstr("error\n");
			return (0);
		}
		ft_resolve(&fillit);
	}
	return (0);
}
