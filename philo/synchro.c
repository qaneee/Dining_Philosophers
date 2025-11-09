/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:53:18 by arvardan          #+#    #+#             */
/*   Updated: 2025/09/29 19:33:03 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	spinlock(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->are_threads_created))
		usleep(1000);
}

bool	all_running(pthread_mutex_t *mutex, long *th, long ph_nbr)
{
	bool	res;

	res = false;
	pthread_mutex_lock(mutex);
	if (*th == ph_nbr)
		res = true;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	increase_count(pthread_mutex_t *mutex, long *val)
{
	pthread_mutex_lock(mutex);
	(*val)++;
	pthread_mutex_unlock(mutex);
}

void	sync_philos(t_philo *p)
{
	if (p->table->philo_count % 2 == 0)
	{
		if (p->philo_id % 2 == 0)
		{
			ft_usleep(30, p->table);
		}
	}
	else
	{
		if (p->philo_id % 2 == 0)
		{
			thinking(p, true);
		}
	}
}
