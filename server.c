/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:25:25 by aalhalab          #+#    #+#             */
/*   Updated: 2024/03/20 18:08:35 by aalhalab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int received = 0;
int bits_received = 0;

void signal_handler(int sig) {
    received = received << 1;
    if (sig == SIGUSR1) {
        received = received | 1;
    }
    bits_received++;
    if (bits_received == 8) {
        printf("Received character: %c\n", (char)received);
        received = 0;
        bits_received = 0;
    }
}

int main() {
    int p;

    p = getpid();
    printf("Server PID: %d\n", p);

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        pause();
    }

    return 0;
}