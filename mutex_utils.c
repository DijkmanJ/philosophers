/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 13:37:42 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/21 18:17:01 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_bool(pthread_mutex_t *mtx, volatile bool *dest, volatile bool v)
{
	pthread_mutex_lock(mtx);
	*dest = v;
	pthread_mutex_unlock(mtx);
}

bool	read_bool(pthread_mutex_t *mtx, volatile bool *dest)
{
	bool	temp;

	pthread_mutex_lock(mtx);
	temp = *dest;
	pthread_mutex_unlock(mtx);
	return (temp);
}

void	write_uint64(pthread_mutex_t *mtx, uint64_t *dest, uint64_t value)
{
	pthread_mutex_lock(mtx);
	*dest = value;
	pthread_mutex_unlock(mtx);
}

uint64_t	read_uint64(pthread_mutex_t *mtx, uint64_t *dest)
{
	uint64_t	temp;

	pthread_mutex_lock(mtx);
	temp = *dest;
	pthread_mutex_unlock(mtx);
	return (temp);
}

int	*inc_int(pthread_mutex_t *mtx, int *value)
{
	pthread_mutex_lock(mtx);
	(*value)++;
	pthread_mutex_unlock(mtx);
	return (value);
}
