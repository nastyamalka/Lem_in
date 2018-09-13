/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dopolnenie.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:35:12 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/18 18:35:14 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		ft_find_place(t_opt *inf, int i)
{
	t_way	*p;
	t_ants	*new;

	p = inf->way;
	while (p)
	{
		if (p->head->status == -1 && p->head->s_or_e != 'e')
		{
			p->head->status = i;
			return (1);
		}
		else if (p->head->s_or_e == 'e')
		{
			new = malloc(sizeof(new));
			new->data = i;
			new->next = p->head->ant;
			p->head->ant = new;
			return (1);
		}
		p = p->next;
	}
	return (0);
}

void	free_room(t_room *r)
{
	t_ants	*a_p;

	while (r->ant)
	{
		a_p = r->ant;
		r->ant = r->ant->next;
		if (a_p)
			ft_memdel((void**)(&a_p));
	}
	if (r->name)
		ft_memdel((void**)(&r->name));
}

t_room	*ft_help_norma(t_room *rooms)
{
	t_room	*this;

	this = ft_find_room(rooms, 0);
	this->status = 3;
	this->value = 0;
	this->index_from_where = -1;
	return (this);
}

void	ft_printf_ants(t_opt *inf, t_room *r_p, int *m)
{
	t_ants	*a_p;

	while (r_p && r_p->status != -1 && r_p->s_or_e != 'e')
	{
		*m = 1;
		if (inf->color != 0)
			ft_printf("%s", R);
		ft_printf("L%i%s-%s ", r_p->status, N, r_p->name);
		r_p = r_p->next;
	}
	while (r_p && r_p->ant)
	{
		*m = 1;
		a_p = r_p->ant;
		if (inf->color != 0)
			ft_printf("%s", G);
		ft_printf("L%i%s-%s ", r_p->ant->data, N, r_p->name);
		r_p->ant = r_p->ant->next;
		if (a_p)
			ft_memdel((void **)(&a_p));
	}
}

void	ft_add_ant_to_end(t_room *r_p, int temp2)
{
	t_ants	*new;

	new = malloc(sizeof(new));
	new->data = temp2;
	new->next = r_p->ant;
	r_p->ant = new;
}
