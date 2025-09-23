#include "philo.h"

void    set_bool(pthread_mutex_t *mutex, bool *dst, bool val)
{
    pthread_mutex_lock(mutex);
    *dst = val;
    pthread_mutex_unlock(mutex);
}

bool    get_bool(pthread_mutex_t *mutex, bool *val)
{
    bool    ret;

    pthread_mutex_lock(mutex);
    ret = *val;
    pthread_mutex_unlock(mutex);
    return (ret);
}

void    set_long(pthread_mutex_t *mutex, long *dst, long val)
{
    pthread_mutex_lock(mutex);
    *dst = val;
    pthread_mutex_unlock(mutex);
}

long    get_long(pthread_mutex_t *mutex, long *val)
{
    long    ret;

    pthread_mutex_lock(mutex);
    ret = *val;
    pthread_mutex_unlock(mutex);
    return (ret);
}

bool    sim_finished(t_table *t)
{
    return (get_bool(&t->table_mutex, &t->end_sim)); 
}