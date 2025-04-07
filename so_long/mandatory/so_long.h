/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpozniak <vpozniak@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:39:36 by vpozniak          #+#    #+#             */
/*   Updated: 2025/04/07 19:22:55 by vpozniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifdef __APPLE__ // macOS platform
#  include "so_long_mac.h"
# elif defined(__linux__) // Linux platform
#  include "so_long_linux.h"
# endif

#endif // SO_LONG_H