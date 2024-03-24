/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:25:25 by aalhalab          #+#    #+#             */
/*   Updated: 2024/03/24 23:58:59 by aalhalab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void	send_ack(int pid)
{
	kill(pid, SIGUSR1);
}

void	handle_len_bit(int sig, int *len, int *len_received)
{
	*len = *len << 1;
	if (sig == SIGUSR1)
		*len = *len | 1;
	(*len_received)++;
}

void	handle_char_bit(int sig, int *received, int *bits_received, int *len)
{
	*received = *received << 1;
	if (sig == SIGUSR1)
		*received = *received | 1;
	(*bits_received)++;
	if (*bits_received == 8)
	{
		write(1, received, 1);
		*received = 0;
		*bits_received = 0;
		(*len)--;
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	received = 0;
	static int	bits_received = 0;
	static int	len = 0;
	static int	len_received = 0;

	(void)context;
	if (len_received < 32)
		handle_len_bit(sig, &len, &len_received);
	else
		handle_char_bit(sig, &received, &bits_received, &len);
	if (len == 0 && len_received >= 32)
	{
		write(1, "\n", 1);
		len_received = 0;
		send_ack(info->si_pid);
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				p;

	p = getpid();
	ft_printf("Server PID: %d\n", p);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
