/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:12:25 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 14:12:34 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# define C_NONE         "\033[0m"
# define C_CYAN         "\033[36m"

typedef struct s_data		t_data;
typedef struct s_envp		t_envp;

struct				s_envp
{
	char	*name;
	char	*value;
	t_envp	*next;
};

struct				s_data
{
	char	**input;
	t_envp	*envp;
};

int					ft_lst_len(t_data *data);
int					ft_lst_add(char *envl, t_data *data);
int					ft_lst_new(char **envp, t_data *data);
void				ft_init_data(char **envp, t_data *data);
t_envp				*ft_env_var_exist(char *name, t_data *data);
void				ft_change_dlr(t_data *data);
void				ft_change_tld(t_data *data);
char				*ft_find_binary(t_data *data);

void				ft_free_tab(char **tab);
void				ft_free_lst(t_envp *envp);
void				ft_free_data(t_data *data);
char				**ft_tabjoin_free(char **tab, char *str);

void				ft_err_exit(t_data *data);
void				ft_print_error(char *var, char *error);
void				ft_err_tld_exit(char **new_str,
					char **endline, t_data *data);
void				ft_err_dlr_exit(char **var, char **end,
					char **new_str, t_data *data);

/*
** Parsing
*/

void				ft_get_command(t_data *data);
void				ft_exec_command(t_data *data);

/*
** Builtins
*/

void				ft_change_dir(t_data *data);
void				ft_setenv(t_data *data);
void				ft_unsetenv(t_data *data);
void				ft_display_env(t_data *data);
void				ft_exit(t_data *data);
void				ft_echo(t_data *data);

#endif
