/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 20:55:58 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:47:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lst_len(t_data *data)
{
	t_envp	*start;
	int		i;

	i = 0;
	start = data->envp;
	while (data->envp)
	{
		data->envp = data->envp->next;
		i++;
	}
	data->envp = start;
	return (i);
}

t_envp	*ft_env_var_exist(char *name, t_data *data)
{
	t_envp		*start;
	t_envp		*ret;

	start = data->envp;
	while (data->envp)
	{
		if (ft_strequ(name, data->envp->name))
		{
			ret = data->envp;
			data->envp = start;
			return (ret);
		}
		data->envp = data->envp->next;
	}
	data->envp = start;
	return (0);
}

int		ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_tabjoin_free(char **tab, char *str)
{
	char	**new;
	int		i;

	i = 0;
	if (!(new = (char **)ft_memalloc(sizeof(char *) * (ft_tablen(tab) + 2))))
		return (0);
	while (tab[i])
	{
		if (!(new[i] = ft_strdup(tab[i])))
		{
			ft_free_tab(new);
			return (0);
		}
		i++;
	}
	if (!(new[i] = ft_strdup(str)))
	{
		ft_free_tab(new);
		return (0);
	}
	ft_free_tab(tab);
	return (new);
}
