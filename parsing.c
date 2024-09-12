/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jdijkman <jdijkman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 15:32:25 by jdijkman      #+#    #+#                 */
/*   Updated: 2024/08/23 17:34:20 by jdijkman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (n > 0 && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] == s2[i])
			i ++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		n --;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

bool	max(char *str)
{
	char	*max_int_str;
	size_t	str_len;
	size_t	max_len;

	max_int_str = "2147483647";
	max_len = ft_strlen(max_int_str);
	str_len = ft_strlen(str);
	if (str_len > max_len)
		return (true);
	if (str_len < max_len)
		return (false);
	if (ft_strncmp(str, max_int_str, str_len) > 0)
		return (true);
	return (false);
}

int	parse_input(int argc, char **argv)
{
	if (argc < 5)
		return (printf("invalid argc\n"), 1);
	if (argv[1][0] == '\0' || argv[2][0] == '\0' || \
		argv[3][0] == '\0' || argv[4][0] == '\0')
		return (printf("invalid arguments\n"), 1);
	if (isnbr(argv[1]) || isnbr(argv[2]) || isnbr(argv[3]) || isnbr(argv[4]))
		return (printf("arguments must be positive integers\n"), 1);
	if (max(argv[1]) || max(argv[2]) || max(argv[3]) || max(argv[4]))
		return (printf("arguments cannot be bigger than max int\n"), 1);
	if (argv[1][0] == '0' && argv[1][1] == '\0')
		return (printf("number of philosophers cannot be 0\n"), 1);
	if (argc > 5)
	{
		if (argv[5][0] == '\0' || isnbr(argv[5]) || max(argv[5]))
			return (printf("invalid meal count\n"), 1);
	}
	if (argv[1][0] == '1' && argv[1][1] == '\0')
	{
		printf("0 1 has taken a fork\n");
		me_sleep(ft_atoi(argv[2]));
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (1);
	}
	return (0);
}
