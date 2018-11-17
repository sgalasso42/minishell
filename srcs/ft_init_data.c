/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 20:32:18 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:30:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_add_shlvl(t_data *data)
{
	t_envp	*shlvl;
	int		lvl;

	shlvl = ft_env_var_exist("SHLVL", data);
	lvl = ft_atoi(shlvl->value);
	free(shlvl->value);
	if (!(shlvl->value = ft_itoa(lvl + 1)))
		return (0);
	return (1);
}

int			ft_get_envp(char **envp, t_data *data)
{
	t_envp	*start;
	int		i;

	i = 0;
	if (!(ft_lst_new(envp, data)))
		return (0);
	start = data->envp;
	while (envp[++i])
	{
		if (!(ft_lst_add(envp[i], data)))
			return (0);
	}
	data->envp = start;
	return ((!(ft_add_shlvl(data))) ? 0 : 1);
}

void		ft_err_create_envp_exit(char **new_env, char **pwd)
{
	free(new_env);
	ft_strdel(pwd);
	exit(EXIT_FAILURE);
}

char		**ft_create_envp(void)
{
	char	**new_env;
	char	*pwd;

	pwd = 0;
	new_env = 0;
	if (!(new_env = (char **)(ft_memalloc(sizeof(char *) * 4))))
		exit(EXIT_FAILURE);
	if (!(pwd = getcwd(NULL, 0)))
		ft_err_create_envp_exit(new_env, 0);
	if (!(new_env[0] = ft_strjoin("PWD=", pwd)))
		ft_err_create_envp_exit(new_env, &pwd);
	ft_strdel(&pwd);
	if (!(new_env[1] = ft_strdup("SHLVL=0")))
	{
		ft_free_tab(new_env);
		exit(EXIT_FAILURE);
	}
	if (!(new_env[2] = ft_strdup("_=/usr/bin/env")))
	{
		ft_free_tab(new_env);
		exit(EXIT_FAILURE);
	}
	return (new_env);
}

void		ft_init_data(char **envp, t_data *data)
{
	ft_bzero(data, sizeof(data));
	if (!envp[0])
	{
		envp = ft_create_envp();
		if (!(ft_get_envp(envp, data)))
			ft_free_lst(data->envp);
		ft_free_tab(envp);
	}
	else
		ft_get_envp(envp, data);
}
