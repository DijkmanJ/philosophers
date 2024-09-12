/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/29 15:17:04 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/26 18:24:31 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	isnbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i ++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

void	ft_exit(char *error_msg, int exit_code)
{
	printf("%s\n", error_msg);
	exit(exit_code);
}

void	ft_print(pthread_mutex_t *mtx, int time, t_phil *phil, char *msg)
{
	pthread_mutex_lock(mtx);
	printf("%d %d %s\n", time, phil->id + 1, msg);
	pthread_mutex_unlock(mtx);
}
