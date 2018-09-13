/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_room.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:11:58 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/19 12:12:02 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_free_2d(char **mas, int n)
{
	int		i;

	i = 0;
	if (mas)
		while (i < n && mas[i])
		{
			if (mas[i])
				ft_memdel((void**)(&(mas[i++])));
		}
	if (mas)
		ft_memdel((void**)(&mas));
}

int		ft_valid(char **s, t_opt *inf)
{
	t_room	*r_p;
	int		x;
	int		y;

	x = ft_atoi(*(s + 1));
	y = ft_atoi(*(s + 2));
	r_p = inf->rooms;
	while (r_p)
	{
		if (ft_strcmp(r_p->name, *s) == 0)
			return ((r_p->x == x && r_p->y == y) ? 2 : 0);
		r_p = r_p->next;
	}
	r_p = inf->rooms;
	while (r_p)
	{
		if (r_p->x == x && r_p->y == y && ft_strcmp(r_p->name, *s) != 0)
			return (0);
		r_p = r_p->next;
	}
	return (1);
}

int		ft_comment(t_opt *inf, char *s)
{
	if (!ft_strcmp(s, "##start"))
	{
		if (inf->strt == -1 && !(inf->en != 0 && inf->end == -1))
			inf->s = 's';
		else
			return (-2);
		return (3);
	}
	if (!ft_strcmp(s, "##end"))
	{
		if (inf->end == -1 && !(inf->s != 0 && inf->strt == -1))
			inf->en = 'e';
		else
			return (-1);
		return (3);
	}
	return (2);
}

void	ft_error(int num_of_w, char **words, t_opt *inf)
{
	if (ft_is_str_num(words[num_of_w - 1]) == 0 || ft_is_str_num(words
	[num_of_w - 2]) == 0 || ft_strchr(words[0], '-'))
	{
		ft_free_2d(words, num_of_w);
		(inf->e) ? ft_printf("\e[1;31mSTOP! Incorect room\e[0m\n")
		: ft_printf("Error\n");
		exit(1);
	}
	if (*words[0] == 'L' || ft_valid(words, inf) == 0)
	{
		(inf->e) ? ft_printf("\e[1;31mSTOP! Incorect room\e[0m\n")
		: ft_printf("Error\n");
		exit(1);
	}
	if (ft_valid(words, inf) == 1)
		ft_room(words, inf);
}

int		ft_is_room(char *s, t_opt *inf)
{
	char	**words;
	int		num_of_w;

	if (!s || s[0] == '\0')
	{
		(inf->e) ? ft_printf("\e[1;31mSTOP! Incorect room\e[0m\n")
		: ft_printf("Error\n");
		return (-3);
	}
	if (s[0] == '#')
		return (ft_comment(inf, s));
	words = ft_strsplit(s, ' ');
	num_of_w = ft_countw(words);
	if (num_of_w != 3)
	{
		ft_free_2d(words, num_of_w);
		if (ft_strchr(s, '-'))
			return (0);
		(inf->e) ? ft_printf("\e[1;31mSTOP! Incorect room\e[0m\n")
		: ft_printf("Error\n");
		exit(1);
	}
	ft_error(num_of_w, words, inf);
	ft_free_2d(words, num_of_w);
	return (1);
}
