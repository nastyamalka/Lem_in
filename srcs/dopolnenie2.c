/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dopolnenie2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkevy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 12:14:51 by amalkevy          #+#    #+#             */
/*   Updated: 2018/06/19 12:14:55 by amalkevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		ft_f_room(char *s1, char *s2, t_opt *inf)
{
	t_room	*r_p;

	inf->r1 = -1;
	inf->r2 = -1;
	r_p = inf->rooms;
	while (r_p)
	{
		if (ft_strcmp(r_p->name, s1) == 0)
			inf->r1 = r_p->index;
		if (ft_strcmp(r_p->name, s2) == 0)
			inf->r2 = r_p->index;
		if (inf->r1 != -1 && inf->r2 != -1)
			return (1);
		r_p = r_p->next;
	}
	return (0);
}

int		ft_fit(char *s, char *def, t_opt *inf)
{
	char	*s1;
	char	*s2;

	s1 = ft_strsub(s, 0, (unsigned int)(def - s));
	s2 = ft_strsub(s, (unsigned int)(def - s) + 1,
	ft_strlen(s) - (def - s) - 1);
	if (s1 && s2)
	{
		if (ft_f_room(s1, s2, inf) == 0)
		{
			ft_memdel((void**)&s1);
			ft_memdel((void**)&s2);
			return (0);
		}
		ft_memdel((void**)&s1);
		ft_memdel((void**)&s2);
		inf->matr_smezh[inf->r1][inf->r2] = '1';
		inf->matr_smezh[inf->r2][inf->r1] = '1';
		return (1);
	}
	return (0);
}

void	ft_st_or_end(t_opt *inf, t_room *new_room)
{
	if (inf->s != 0 && inf->strt == -1)
	{
		new_room->next = inf->rooms;
		inf->rooms = new_room;
		new_room->s_or_e = 's';
		new_room->index = 0;
		inf->strt = 0;
	}
	if (inf->en != 0 && inf->end == -1)
	{
		inf->room_end = new_room;
		new_room->s_or_e = 'e';
		inf->end = inf->n_of_rooms;
	}
	else
		inf->n_of_rooms++;
}
