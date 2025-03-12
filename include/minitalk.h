/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:58:43 by obajja            #+#    #+#             */
/*   Updated: 2025/03/12 12:58:53 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <signal.h>
#include <ft_printf.h>

typedef struct s_client
{
    unsigned char byte;
    char *str;
    int count;
    int pid;
    struct s_client *next;   
} t_client;

#endif
