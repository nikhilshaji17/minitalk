/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkunnath <nkunnath@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:37:35 by nkunnath          #+#    #+#             */
/*   Updated: 2024/12/19 18:37:37 by nkunnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	Signal(int signo, void *handler, bool use_siginfo)
{
	struct	sigaction sa = {0};

	if (use_siginfo)
	{
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = handler;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(signo, &sa, NULL) < 0)
	{
		perror("Sigaction failed\n");
		exit(EXIT_FAILURE);
	}
}

void	Kill(pid_t pid, int signo)
{
	if (kill(pid, signo) < 0)
	{
		perror("Kill failed\n");
		exit(EXIT_FAILURE);
	}
}
