/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:52:34 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/18 14:52:38 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	ft_del_from_room(t_opt *inf, int index)
{
	t_room	*p;

	p = inf->rooms;
	while (p && p->next->index != index)
		p = p->next;
	p->next = p->next->next;
}

void	ft_go_to_start(t_room *room, t_opt *inf)
{
	t_way	*new_way;
	t_room	*p;

	new_way = malloc(sizeof(t_way));
	new_way->head = ft_find_room(inf->rooms, room->index);
	new_way->num_of_room = room->value;
	new_way->head->status = -1;
	new_way->head->ant = NULL;
	while (room->s_or_e != 's')
	{
		inf->room_end = NULL;
		room = room->prev;
		p = ft_find_room(inf->rooms, room->index);
		room->status = -1;
		if (room->s_or_e == 's')
			break ;
		ft_del_from_room(inf, room->index);
		p->next = new_way->head;
		new_way->head = p;
	}
	new_way->next = NULL;
	ft_push_back(&(inf->way), new_way);
}

int		ft_find_way(t_opt *inf)
{
	t_room	*this;
	t_room	*prev;
	t_room	*rooms;
	char	m;

	m = 0;
	rooms = inf->rooms;
	ft_made_quee(inf);
	ft_push_in_quee(inf, 0);
	ft_help_norma(rooms);
	while (inf->quee[0] != -1)
	{
		this = ft_take_from_quee(inf);
		ft_push_in_quee(inf, this->index);
		this->status = 3;
		prev = ft_find_room(rooms, this->index_from_where);
		this->value = prev->value + 1;
		if (this->s_or_e == 'e')
		{
			m = 1;
			ft_go_to_start(this, inf);
			break ;
		}
	}
	return (m);
}

void	ft_obnul_room(t_room *rooms)
{
	t_room	*p;

	p = rooms;
	while (p)
	{
		p->status = 1;
		p->index_from_where = -1;
		p->value = -1;
		p = p->next;
	}
}

int		ft_do(t_opt *inf)
{
	t_room	*p;
	int		i;

	if (inf->strt == -1 || inf->end == -1)
		return (0);
	p = inf->rooms;
	while (p)
	{
		if (p->index == inf->strt)
			break ;
		p = p->next;
	}
	i = 0;
	if (inf->room_end == NULL)
		return (0);
	while (i++ < inf->num_of_ways)
	{
		ft_obnul_room(inf->rooms);
		if (ft_find_way(inf) == 0 || inf->way->head->next == NULL)
			break ;
		if (inf->quee)
			ft_memdel((void**)(&inf->quee));
	}
	return ((inf->way) ? 1 : 0);
}
