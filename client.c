/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhalab <aalhalab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:24:56 by aalhalab          #+#    #+#             */
/*   Updated: 2024/03/20 18:12:49 by aalhalab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void string_to_binary(int pid, char *str) {
    int i;
    int j;
    int c;
    int bit;

    i = 0;
    while (str[i]) {
        c = str[i];
        j = 7;
        while (j >= 0) {
            bit = (c >> j) & 1;
            if (bit == 1) {
                kill(pid, SIGUSR1);
            } else {
                kill(pid, SIGUSR2);
            }
            j--;
            usleep(100);
        }
        i++;
    }
}

int main(int argc, char **argv) {
    pid_t pid;

    if (argc != 3) {
        printf("Usage: %s <pid> <string>\n", argv[0]);
        return 1;
    }

    pid = atoi(argv[1]);
    string_to_binary(pid, argv[2]);

    return 0;
}