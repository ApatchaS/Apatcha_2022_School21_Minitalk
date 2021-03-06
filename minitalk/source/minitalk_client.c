/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:21:04 by asippy            #+#    #+#             */
/*   Updated: 2022/03/05 19:17:43 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void	ft_send_message(int pid, int info, size_t flag)
{
	size_t	bits_length;
	size_t	iter;

	bits_length = 8;
	if (flag)
		bits_length = 32;
	iter = 0;
	while (iter < bits_length)
	{
		if (info & (1 << iter))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		iter++;
		usleep(70);
	}
	return ;
}

static int	ft_atoi(const char *str)
{
	unsigned long long	res;
	int					sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (res > __LONG_LONG_MAX__)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (res * sign);
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	int		pid;
	int		message_length;
	size_t	iter;

	if (argc != 3)
	{
		ft_printf("Pass 2 arguments: server's PID and message to be sent\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message_length = ft_strlen(argv[2]);
	ft_send_message(pid, message_length, 1);
	iter = 0;
	while (argv[2][iter] != '\0')
	{
		ft_send_message(pid, argv[2][iter], 0);
		iter++;
	}
	ft_send_message(pid, argv[2][iter], 0);
	return (0);
}
