/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_utils2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/14 15:02:23 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/23 15:11:14 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_int(pthread_mutex_t *mtx, int *dest, int value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

int	read_int(pthread_mutex_t *mtx, int *dest)
{
	int	temp;

	pthread_mutex_lock(mtx);
	temp = *dest;
	pthread_mutex_unlock(mtx);
	return (temp);
}

void	ft_free_struct(t_phil **phil)
{
	int	i;

	i = 0;
	while (phil[i])
	{
		free(phil[i]);
		i ++;
	}
	free(phil);
}

void	me_sleep(uint64_t ms)
{
	uint64_t	start;

	start = get_time();
	usleep(ms * 1000 / 2);
	while ((get_time() - start) < ms)
		usleep(100);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}
