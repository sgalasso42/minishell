/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 22:49:53 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:17:02 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_cd_home(t_data *data)
{
	t_envp	*home;

	if (!data->input[1])
	{
		if (!(home = ft_env_var_exist("HOME", data)))
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (0);
		}
		else if (!(data->input = ft_tabjoin_free(data->input, home->value)))
			ft_err_exit(data);
	}
	return (1);
}

int			ft_cd_last(t_envp *oldpwd, t_data *data)
{
	if (ft_strequ(data->input[1], "-"))
	{
		if (!oldpwd)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (0);
		}
		else
		{
			ft_strdel(&(data->input[1]));
			if (!(data->input[1] = ft_strdup(oldpwd->value)))
				ft_err_exit(data);
			ft_putendl(oldpwd->value);
		}
	}
	return (1);
}

void		ft_change_dir(t_data *data)
{
	t_envp	*curpwd;
	t_envp	*oldpwd;

	curpwd = ft_env_var_exist("PWD", data);
	oldpwd = ft_env_var_exist("OLDPWD", data);
	if (!(ft_cd_home(data)) || !(ft_cd_last(oldpwd, data)))
		return ;
	if (chdir(data->input[1]) != -1)
	{
		if (oldpwd && curpwd)
		{
			ft_strdel(&(oldpwd->value));
			if (!(oldpwd->value = ft_strdup(curpwd->value)))
				ft_err_exit(data);
		}
		if (curpwd)
		{
			ft_strdel(&(curpwd->value));
			if (!(curpwd->value = getcwd(NULL, 0)))
				ft_err_exit(data);
		}
	}
	else
		ft_putendl_fd("cd: Permission denied or No such file or directory", 2);
}
