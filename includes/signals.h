/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinajib <hinajib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:39:15 by hinajib           #+#    #+#             */
/*   Updated: 2025/06/27 18:42:48 by hinajib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal_status;

void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	setup_shell_signals(void);
void	setup_exec_signals(void);
void	ignore_sigquit(void);
void	restore_shell_signals(void);

#endif