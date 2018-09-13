/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_que.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:44:51 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/18 14:44:56 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

t_room	*ft_find_room(t_room *rooms, int index)
{
	while (rooms)
	{
		if (rooms->index == index)
			return (rooms);
		rooms = rooms->next;
	}
	return (NULL);
}

void	ft_made_quee(t_opt *inf)
{
	int		i;

	i = 0;
	inf->quee = malloc(sizeof(int) * inf->n_of_rooms);
	while (i < inf->n_of_rooms)
		inf->quee[i++] = -1;
}

void	ft_push_in_quee(t_opt *inf, int index)
{
	int		i;
	int		j;
	t_room	*p;
	t_room	*room;

	i = 0;
	j = 0;
	while (inf->matr_smezh[index][i])
	{
		if (inf->matr_smezh[index][i] == '1')
		{
			room = inf->rooms;
			p = ft_find_room(room, i);
			if (p && p->status == 1)
			{
				while (j < inf->n_of_rooms && inf->quee[j] != -1)
					j++;
				inf->quee[j] = i;
				p->status = 2;
				p->index_from_where = index;
				p->prev = ft_find_room(room, index);
			}
		}
		i++;
	}
}

t_room	*ft_take_from_quee(t_opt *inf)
{
	int		i;
	int		index;
	t_room	*rooms;

	if (inf->quee[0] == -1)
		return (NULL);
	index = inf->quee[0];
	i = 0;
	while (inf->quee[i] != -1)
	{
		inf->quee[i] = inf->quee[i + 1];
		i++;
	}
	rooms = inf->rooms;
	return (ft_find_room(rooms, index));
}

void	ft_push_back(t_way **way, t_way *new_way)
{
	t_way	*p;

	p = *way;
	if (p == NULL)
	{
		new_way->index = 1;
		*way = new_way;
		return ;
	}
	while (p->next)
		p = p->next;
	new_way->index = p->index + 1;
	p->next = new_way;
}
