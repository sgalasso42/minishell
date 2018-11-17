/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:46:15 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 13:55:36 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_err_tld_exit(char **new_str, char **endline, t_data *data)
{
	ft_strdel(new_str);
	ft_strdel(endline);
	ft_err_exit(data);
}

void		ft_err_dlr_exit(char **var, char **end,
			char **new_str, t_data *data)
{
	ft_strdel(var);
	ft_strdel(end);
	ft_strdel(new_str);
	ft_err_exit(data);
}

void		ft_print_error(char *var, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	if (var)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
}

void		ft_err_exit(t_data *data)
{
	ft_free_data(data);
	ft_putendl("minishell: Error !");
	exit(EXIT_FAILURE);
}
