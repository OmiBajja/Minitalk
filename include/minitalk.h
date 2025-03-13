/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:58:43 by obajja            #+#    #+#             */
/*   Updated: 2025/03/12 23:44:09 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <ft_printf.h>
# include <signal.h>

typedef struct s_client
{
	unsigned char	byte;
	char			*str;
	int				count;
	int				pid;
	struct s_client	*next;
}					t_client;

#endif
