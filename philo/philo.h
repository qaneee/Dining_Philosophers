# ifndef PHILO_H
#define PHILO_H

#define COLOR_THINKING "\033[38;2;173;216;230m"
#define COLOR_EATING   "\033[38;2;144;238;144m"
#define COLOR_SLEEPING "\033[38;2;255;248;220m"
#define COLOR_FORK     "\033[38;2;222;184;135m"
#define COLOR_DEAD     "\033[38;2;220;20;60m"
#define COLOR_RESET    "\033[0m"

#define T_MSG COLOR_THINKING "is thinking" COLOR_RESET
#define E_MSG COLOR_EATING   "is eating"   COLOR_RESET
#define S_MSG COLOR_SLEEPING "is sleeping" COLOR_RESET
#define F_MSG COLOR_FORK     "has taken a fork" COLOR_RESET
#define D_MSG COLOR_DEAD     "died"        COLOR_RESET

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_table t_table;
typedef struct s_philo t_philo;
typedef struct s_fork  t_fork;

typedef enum e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
	TAKING_F_FORK,
	TAKING_S_FORK,
	DIED,
} t_philo_state;

typedef struct s_fork
{
	pthread_mutex_t fork;
	int				fork_id;
} t_fork;

typedef struct s_table
{
    int					philo_count;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;	
	long				must_eat;
	unsigned long long	start_sim;
	long				running_thread_count;
	bool				end_sim;
	bool				are_threads_created;
	pthread_t			monitor;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		write_mutex;
	t_fork				*forks;
	t_philo				*philos;		 
}	t_table;

typedef struct s_philo
{
	int				philo_id;
	int				meals_eaten;
	bool			is_full;
	t_fork			*first_fork;		
	t_fork			*second_fork;
	long			last_meal_time;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
} t_philo;

//utils
unsigned long long	real_time(void);
long				ft_atol(const char *str);
void				write_state(t_philo_state s, t_philo *ph);
void				ft_usleep(long usec, t_table *table);
void				free_all(t_table *t);

//init
void    init_all(t_table *t);

//set and get
void    set_bool(pthread_mutex_t *mutex, bool *dst, bool val);
bool    get_bool(pthread_mutex_t *mutex, bool *val);
void    set_long(pthread_mutex_t *mutex, long *dst, long val);
long    get_long(pthread_mutex_t *mutex, long *val);
bool    sim_finished(t_table *t);

//simulation
void    *monitoring(void *data);
void	start_dinner(t_table *table);
void    *one_philo(void *data);
void	*routine(void *data);
void	thinking(t_philo *p, bool val);

//sync
void    spinlock(t_table *table);
bool    all_running(pthread_mutex_t *mutex, long *th, long ph_nbr);
void    increase_count(pthread_mutex_t *mutex, long *val);
void    sync_philos(t_philo *p);

#endif