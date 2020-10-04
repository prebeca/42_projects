/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 13:53:11 by user42            #+#    #+#             */
/*   Updated: 2020/10/04 18:30:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "dirent.h"
# include "errno.h"
# include "string.h"

int		parse_input(char *input);
int		parse_echo(char *line);
void	ft_pwd(void);
void	change_directory(char *path);
int		table_len(char ** tab);
#endif