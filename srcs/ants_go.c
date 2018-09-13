/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_go.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 17:49:51 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/18 17:49:55 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room	*ft_check_for_pr(t_way *way)
{
	t_way	*w_p;
	t_room	*r_p;

	w_p = way;
	while (w_p->head)
	{
		if (w_p->head->status != -1 || w_p->head->ant != NULL)
			return (w_p->head);
		r_p = w_p->head;
		w_p->head = w_p->head->next;
		if (r_p)
		{
			ft_memdel((void**)(&(r_p->name)));
			ft_memdel((void**)(&r_p));
		}
	}
	return (NULL);
}

int		ft_print_way(t_opt *inf)
{
	t_room	*r_p;
	t_way	*w_p;
	int		m;

	m = 0;
	w_p = inf->way;
	while (w_p)
	{
		r_p = ft_check_for_pr(w_p);
		if (r_p)
			ft_printf_ants(inf, r_p, &m);
		w_p = w_p->next;
	}
	ft_printf("\n");
	return (m);
}

void	ft_move(t_opt *inf)
{
	t_way	*w_p;
	t_room	*r_p;
	int		temp;
	int		temp2;

	w_p = inf->way;
	while (w_p)
	{
		temp2 = -1;
		r_p = w_p->head;
		while (r_p->s_or_e != 'e')
		{
			temp = temp2;
			temp2 = r_p->status;
			r_p->status = temp;
			r_p = r_p->next;
		}
		if (temp2 != -1)
			ft_add_ant_to_end(r_p, temp2);
		w_p = w_p->next;
	}
}

int		ft_check_next(t_way *way)
{
	t_way	*w_p;

	while (way)
	{
		if (way->head->next || (way->head->s_or_e == 'e' && way->head->ant))
			return (1);
		w_p = way;
		way = way->next;
		if (w_p)
			ft_memdel((void**)(&w_p));
	}
	return (0);
}

void	ft_go(t_opt *inf)
{
	int		i;

	i = 1;
	while (i <= inf->n_of_ant)
	{
		while (i <= inf->n_of_ant && ft_find_place(inf, i) == 1)
			i++;
		ft_print_way(inf);
		ft_move(inf);
	}
	ft_go_to_end(inf);
}
