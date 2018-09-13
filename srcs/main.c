/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:51:44 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/18 12:36:21 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_pr_way(t_opt inf)
{
	t_room	*p;
	t_way	*p_w;

	p_w = inf.way;
	ft_printf("\nWays:\n");
	while (p_w)
	{
		p = p_w->head;
		if (p_w->index % 3 == 0)
			ft_printf("%s", M);
		else if (p_w->index % 3 == 1)
			ft_printf("%s", Y);
		else if (p_w->index % 3 == 2)
			ft_printf("%s", U);
		ft_printf("%i:\n%s-", p_w->index, inf.rooms->name);
		while (p)
		{
			ft_printf("%s", p->name);
			if (p->next)
				ft_printf("-");
			p = p->next;
		}
		ft_printf("\n\n%s", N);
		p_w = p_w->next;
	}
}

int		ft_read_flag(char **v, int c, t_opt *inf)
{
	int		i;

	i = 0;
	while (i < c)
	{
		if (v[i][0] == '-' && v[i][1] == 'E' && v[i][2] == '\0')
			inf->e = 1;
		else if (v[i][0] == '-' && v[i][1] == 'C' && v[i][2] == '\0')
			inf->color = 1;
		else if (v[i][0] == '-' && v[i][1] == 'F' && v[i][2] == '\0')
			inf->how_to_go = 1;
		else if (v[i][0] == '-' && v[i][1] == 'S' && v[i][2] == '\0')
			inf->show = 1;
		else if (v[i][0] == '-' && v[i][1] == 'O' && v[i][2] == '\0' && ++i < c)
			inf->fd = open(v[i], O_RDONLY);
		else
		{
			(inf->e) ? ft_printf("\e[1;31mUsage: ./lem-in [-F(Fast - find o"
			"ne way)/ -E(Error managment) / -O filename(open file) / -C(color a"
			"nts) / -S(show possible ways)]\e[0m\n") : ft_printf("Error\n");
			exit(1);
		}
		i++;
	}
	return (1);
}

void	ft_obnul_inf(t_opt *inf)
{
	inf->rooms = NULL;
	inf->n_of_rooms = 0;
	inf->s = 0;
	inf->en = 0;
	inf->strt = -1;
	inf->end = -1;
	inf->matr_smezh = NULL;
	inf->way = NULL;
	inf->fd = 0;
	inf->e = 0;
	inf->color = 0;
	inf->how_to_go = 0;
	inf->room_end = NULL;
	inf->show = 0;
	inf->new_line = malloc(1);
	inf->new_line[0] = '\n';
}

void	ft_free_all(t_opt *inf)
{
	t_room	*r_p;

	while (inf->rooms)
	{
		free_room(inf->rooms);
		r_p = inf->rooms;
		inf->rooms = inf->rooms->next;
		if (r_p)
			ft_memdel((void**)(&r_p));
	}
	if (inf->rooms)
		ft_memdel((void**)(&inf->rooms));
	if (inf->quee)
		ft_memdel((void**)(&inf->quee));
}

int		main(int ac, char **av)
{
	t_opt	inf;

	ft_obnul_inf(&inf);
	if (ac > 1)
		ft_read_flag(av + 1, ac - 1, &inf);
	inf.num_of_ways = (inf.how_to_go == 1) ? 1 : 20000000;
	if (ft_check_ant(&inf) == 0)
		return (0);
	if (ft_check_room(&inf) == -1)
		return (0);
	else
	{
		if (ft_do(&inf) == 0)
			(inf.e && inf.rooms != NULL) ?
	ft_printf("\e[1;31mNo ways were built\e[0m\n") : ft_printf("Error\n");
		else
		{
			if (inf.show == 1)
				ft_pr_way(inf);
			ft_go(&inf);
		}
	}
	ft_free_all(&inf);
	return (0);
}
