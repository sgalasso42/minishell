/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_alias.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 22:57:52 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:47:13 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_tld_replace(int i, int j, t_data *data)
{
	t_envp	*home;
	char	*new_str;
	char	*endline;

	if (!(home = ft_env_var_exist("HOME", data)))
		return (0);
	if (!(new_str = ft_strsub(data->input[i], 0, j)))
		ft_err_exit(data);
	if (!(new_str = ft_strjoin_free(new_str, home->value)))
		ft_err_tld_exit(&new_str, 0, data);
	if (!(endline = ft_strsub(data->input[i], j + 1,
	ft_strlen(data->input[i]))))
		ft_err_tld_exit(&new_str, 0, data);
	if (!(new_str = ft_strjoin_free(new_str, endline)))
		ft_err_tld_exit(&new_str, &endline, data);
	ft_strdel(&endline);
	free(data->input[i]);
	data->input[i] = new_str;
	return (1);
}

void		ft_change_tld(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->input[i])
	{
		j = 0;
		while (data->input[i][j])
		{
			if (data->input[i][j] == '~')
			{
				if (!(ft_tld_replace(i, j, data)))
					return ;
				j = -1;
			}
			j++;
		}
		i++;
	}
}

int			ft_dlr_replace(int i, int j, int size, t_data *data)
{
	char	*var;
	t_envp	*name;
	char	*new_str;
	char	*endl;

	if (!(var = ft_strsub(data->input[i], j + 1, size - 1)))
		ft_err_exit(data);
	if (!(name = ft_env_var_exist(var, data)))
	{
		ft_strdel(&var);
		return ((data->input[i][j] = 0));
	}
	if (!(new_str = ft_strsub(data->input[i], 0, j)))
		ft_err_dlr_exit(&var, 0, 0, data);
	if (!(new_str = ft_strjoin_free(new_str, name->value)))
		ft_err_dlr_exit(&var, 0, &new_str, data);
	if (!(endl = ft_strsub(data->input[i], j + 1, ft_strlen(data->input[i]))))
		ft_err_dlr_exit(&var, 0, &new_str, data);
	if (!(new_str = ft_strjoin_free(new_str, endl + ft_strlen(var))))
		ft_err_dlr_exit(&var, &endl, &new_str, data);
	ft_strdel(&var);
	ft_strdel(&endl);
	free(data->input[i]);
	data->input[i] = new_str;
	return (1);
}

void		ft_change_dlr(t_data *data)
{
	int		i;
	int		j;
	int		temp;
	int		size;

	i = 0;
	while (data->input[i])
	{
		j = 0;
		while (data->input[i][j])
		{
			if (data->input[i][j] == '$')
			{
				size = 0;
				temp = j;
				while (data->input[i][j] && data->input[i][j++] != '/')
					size++;
				if (!(ft_dlr_replace(i, temp, size, data)))
					return ;
				j = -1;
			}
			j++;
		}
		i++;
	}
}
