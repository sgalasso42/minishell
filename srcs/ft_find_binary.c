/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:56:13 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 14:12:39 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_is_absolute(t_data *data)
{
	char	*path;

	if (!access(data->input[0], F_OK))
	{
		if (!(path = ft_strdup(data->input[0])))
			ft_err_exit(data);
		return (path);
	}
	return (0);
}

void	ft_err_find_bin_exit(char *path, char **tab_path, t_data *data)
{
	free(path);
	if (tab_path)
		ft_free_tab(tab_path);
	ft_err_exit(data);
}

char	*ft_test_path(int i, char *path, char **tab_path, t_data *data)
{
	if (!(path = ft_strjoin(tab_path[i], "/")))
		ft_err_find_bin_exit(path, tab_path, data);
	if (!(path = ft_strjoin_free(path, data->input[0])))
		ft_err_find_bin_exit(path, tab_path, data);
	if (!access(path, F_OK))
	{
		ft_free_tab(tab_path);
		return (path);
	}
	free(path);
	return (0);
}

char	*ft_find_binary(t_data *data)
{
	t_envp	*env_path;
	char	**tab_path;
	char	*path;
	int		i;

	if (!data->input[0])
		return (0);
	if ((path = ft_is_absolute(data)))
		return (path);
	if (!(env_path = ft_env_var_exist("PATH", data)))
		return (0);
	if (!(tab_path = ft_strsplit(env_path->value, ':')))
		ft_err_find_bin_exit(path, 0, data);
	i = 0;
	while (tab_path[i])
	{
		if ((path = ft_test_path(i, path, tab_path, data)))
			return (path);
		i++;
	}
	ft_free_tab(tab_path);
	return (0);
}
