/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:24:56 by aalhalab          #+#    #+#             */
/*   Updated: 2024/03/24 23:08:45 by aalhalab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../ft_printf/ft_printf.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int	ft_atoi(const char *str)
{
	int	g[2];

	g[0] = 0;
	g[1] = 0;
	while ((*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	(*str == '+' || *str == '-') && (g[1] = *(str++));
	while (*str >= '0' && *str <= '9')
		g[0] = (g[0] * 10) + (*(str++) - 48);
	return (g[0] * (((2 * (g[1] == '-')) - 1) * -1));
}

void	ack_handler(int sig)
{
	write(1, "Message received by server\n", 27);
}

void	send_bit(int pid, int bit)
{
	if (bit == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

void	send_data(int pid, int data, int size)
{
	int	i;
	int	bit;

	i = size - 1;
	while (i >= 0)
	{
		bit = (data >> i) & 1;
		send_bit(pid, bit);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
	{
		write(1, "error\n", 6);
		return (1);
	}
	signal(SIGUSR1, ack_handler);
	pid = ft_atoi(argv[1]);
	send_data(pid, strlen(argv[2]), 32);
	i = 0;
	while (argv[2][i])
	{
		send_data(pid, argv[2][i], 8);
		i++;
	}
	return (0);
}
