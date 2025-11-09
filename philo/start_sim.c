/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:53:10 by arvardan          #+#    #+#             */
/*   Updated: 2025/09/28 15:34:44 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->first_fork->fork);
	write_state(TAKING_F_FORK, ph);
	pthread_mutex_lock(&ph->second_fork->fork);
	write_state(TAKING_S_FORK, ph);
	set_long(&ph->philo_mutex, &ph->last_meal_time, real_time());
	ph->meals_eaten++;
	write_state(EATING, ph);
	ft_usleep(ph->table->time_to_eat, ph->table);
	if (ph->table->must_eat > 0 && ph->meals_eaten >= ph->table->must_eat)
		set_bool(&ph->philo_mutex, &ph->is_full, true);
	pthread_mutex_unlock(&ph->first_fork->fork);
	pthread_mutex_unlock(&ph->second_fork->fork);
}

void	thinking(t_philo *p, bool val)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!val)
		write_state(THINKING, p);
	if (p->table->philo_count % 2 == 0)
		return ;
	t_eat = p->table->time_to_eat;
	t_sleep = p->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.5, p->table);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	spinlock(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, real_time());
	increase_count(&philo->table->table_mutex,
		&philo->table->running_thread_count);
	sync_philos(philo);
	while (!sim_finished(philo->table))
	{
		eating(philo);
		if (sim_finished(philo->table))
			break ;
		write_state(SLEEPING, philo);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		if (sim_finished(philo->table))
			break ;
		thinking(philo, false);
	}
	return (NULL);
}

static void	create_threads(t_table *t)
{
	int	i;

	if (t->philo_count == 1)
	{
		pthread_create(&t->monitor, NULL, monitoring, t);
		pthread_create(&t->philos[0].thread_id, NULL,
			one_philo, &t->philos[0]);
	}
	else
	{
		i = 0;
		while (i < t->philo_count)
		{
			pthread_create(&t->philos[i].thread_id, NULL,
				routine, &t->philos[i]);
			i++;
		}
		pthread_create(&t->monitor, NULL, monitoring, t);
	}
}

void	start_dinner(t_table *t)
{
	int	i;

	if (t->must_eat == 0)
		return ;
	t->start_sim = real_time();
	i = 0;
	while (i < t->philo_count)
	{
		set_long(&t->philos[i].philo_mutex,
			&t->philos[i].last_meal_time, t->start_sim);
		i++;
	}
	create_threads(t);
	set_bool(&t->table_mutex, &t->are_threads_created, true);
	i = 0;
	while (i < t->philo_count)
	{
		pthread_join(t->philos[i].thread_id, NULL);
		i++;
	}
	set_bool(&t->table_mutex, &t->end_sim, true);
	pthread_join(t->monitor, NULL);
}
