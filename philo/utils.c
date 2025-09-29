/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:53:24 by arvardan          #+#    #+#             */
/*   Updated: 2025/09/29 19:32:48 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	real_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	write_state(t_philo_state s, t_philo *ph)
{
	t_table				*t;
	unsigned long long	t_passed;

	t = ph->table;
	t_passed = real_time() - t->start_sim;
	pthread_mutex_lock(&t->write_mutex);
	if (sim_finished(t) && s != DIED)
	{
		pthread_mutex_unlock(&t->write_mutex);
		return ;
	}
	if ((s == TAKING_F_FORK || s == TAKING_S_FORK) && !sim_finished(t))
		printf("[%lld] %d %s\n", t_passed, ph->philo_id, F_MSG);
	else if (s == EATING && !sim_finished(t))
		printf("[%lld] %d %s\n", t_passed, ph->philo_id, E_MSG);
	else if (s == THINKING && !sim_finished(t))
		printf("[%lld] %d %s\n", t_passed, ph->philo_id, T_MSG);
	else if (s == SLEEPING && !sim_finished(t))
		printf("[%lld] %d %s\n", t_passed, ph->philo_id, S_MSG);
	else if (s == DIED)
		printf("[%lld] %d %s\n", t_passed, ph->philo_id, D_MSG);
	pthread_mutex_unlock(&t->write_mutex);
}

void	ft_usleep(long usec, t_table *table)
{
	unsigned long long	start;
	unsigned long long	assign;

	start = real_time();
	assign = (unsigned long long)usec;
	while (!sim_finished(table) && (real_time() - start) < assign)
	{
		usleep(100);
	}
}

void	free_all(t_table *t)
{
	t_philo	*p;
	int		i;

	i = 0;
	while (i < t->philo_count)
	{
		p = t->philos + i;
		pthread_mutex_destroy(&p->philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&t->table_mutex);
	pthread_mutex_destroy(&t->write_mutex);
	free(t->forks);
	free(t->philos);
}

void	*one_philo(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	spinlock(ph->table);
	set_long(&ph->philo_mutex, &ph->last_meal_time, real_time());
	increase_count(&ph->table->table_mutex, &ph->table->running_thread_count);
	write_state(TAKING_F_FORK, ph);
	while (!sim_finished(ph->table))
		ft_usleep(200, ph->table);
	return (NULL);
}
