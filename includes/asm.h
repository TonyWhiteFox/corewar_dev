/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 09:36:51 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/02/29 19:18:00 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "mlx.h"
# include "math.h"
# include <pthread.h>
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define CHAMP_EXP ".s"
# define CHAMP_COUNT_ERROR "Please indicate the name of one champion\n"
# define EXTENSION_ERROR "Champion file must be with the extension \".s\"\n"

#endif
