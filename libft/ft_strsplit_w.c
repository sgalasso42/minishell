/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_w.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:46:33 by sgalasso          #+#    #+#             */
/*   Updated: 2018/11/17 11:49:16 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbwords(char *str)
{
	int i;
	int cpt;

	i = 0;
	cpt = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != ' ' && str[i] != '\t')
			cpt++;
		else if (i != 0 && str[i] != ' ' && str[i] != '\t' &&
		(str[i - 1] == ' ' || str[i - 1] == '\t'))
			cpt++;
		i++;
	}
	return (cpt);
}

char			**ft_strsplit_w(char const *str)
{
	int		i;
	int		start;
	int		end;
	int		index;
	char	**dest;

	i = 0;
	index = 0;
	if (!str || !(dest = (char **)(malloc(sizeof(char *)
	* (ft_nbwords((char *)str) + 1)))))
		return (0);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
		end = i;
		if (end > start)
			if (!(dest[index++] = ft_strsub(str, start, end - start)))
				return (0);
	}
	dest[index] = 0;
	return (dest);
}
