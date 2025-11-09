/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:53:01 by arvardan          #+#    #+#             */
/*   Updated: 2025/09/25 10:16:27 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dst, bool val)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Error while locking a mutex!\n");
		exit (EXIT_FAILURE);
	}
	*dst = val;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("Error while unlocking a mutex!\n");
		exit (EXIT_FAILURE);
	}
}

bool	get_bool(pthread_mutex_t *mutex, bool *val)
{
	bool	ret;

	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Error while locking a mutex!\n");
		exit (EXIT_FAILURE);
	}
	ret = *val;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("Error while unlocking a mutex!\n");
		exit (EXIT_FAILURE);
	}
	return (ret);
}

void	set_long(pthread_mutex_t *mutex, long *dst, long val)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Error while locking a mutex!\n");
		exit (EXIT_FAILURE);
	}
	*dst = val;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("Error while unlocking a mutex!\n");
		exit (EXIT_FAILURE);
	}
}

long	get_long(pthread_mutex_t *mutex, long *val)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Error while locking a mutex!\n");
		exit (EXIT_FAILURE);
	}
	ret = *val;
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("Error while unlocking a mutex!\n");
		exit (EXIT_FAILURE);
	}
	return (ret);
}

bool	sim_finished(t_table *t)
{
	return (get_bool(&t->table_mutex, &t->end_sim));
}
