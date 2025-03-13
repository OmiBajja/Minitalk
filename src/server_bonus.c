/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:58:58 by obajja            #+#    #+#             */
/*   Updated: 2025/03/13 01:22:44 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static char	*g_str = 0;

void	ender(int *count, char *byte, int *pid)
{
	ft_printf("%s\n", g_str);
	*byte = 0;
	*count = 0;
	free(g_str);
	g_str = NULL;
	kill(*pid, SIGUSR2);
	*pid = 0;
}

char	*str_extender(char append)
{
	char	*extendo;
	char	*temp;
	int		len;

	temp = ft_strdup(g_str);
	free(g_str);
	if (temp)
		len = ft_strlen(temp);
	else
		len = 1;
	extendo = ft_calloc(len + 2, 1);
	ft_memcpy(extendo, temp, len);
	extendo[len] = append;
	free(temp);
	return (extendo);
}

void	byte_aggregator(int sig, siginfo_t *info, void *txt)
{
	static char	byte = 0;
	static int	count = 0;
	static int	pid = 0;

	(void)txt;
	if (pid == 0)
		pid = info->si_pid;
	if (!g_str)
		g_str = ft_calloc(2, 1);
	byte <<= 1;
	if (sig == SIGUSR2)
		byte |= 1;
	count++;
	if (count == 8)
	{
		g_str = str_extender(byte);
		if (byte == '\0')
			return (ender(&count, &byte, &pid));
		byte = 0;
		count = 0;
	}
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	ear;

	ft_printf("PID: %d\n", getpid());
	sigemptyset(&ear.sa_mask);
	ear.sa_sigaction = byte_aggregator;
	ear.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &ear, NULL);
	sigaction(SIGUSR2, &ear, NULL);
	while (1)
		pause();
	return (0);
}
