/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:47:39 by fmol              #+#    #+#             */
/*   Updated: 2025/02/05 18:23:46 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H
# ifdef __LINUX__
#  define KEY_UP 113
#  define KEY_DOWN 101
#  define KEY_LEFT 97
#  define KEY_RIGHT 100
#  define KEY_FORWARD 119
#  define KEY_BACK 115
#  define KEY_ZOOMIN 114
#  define KEY_ZOOMOUT 116
#  define KEY_YAW_R 105
#  define KEY_YAW_L 112
#  define KEY_PITCH_UP 108
#  define KEY_PITCH_DOWN 111
#  define KEY_ROLL_R 59
#  define KEY_ROLL_L 107
#  define KEY_SAVE 122
#  define KEY_ESC 65307
# elif defined(__DARWIN__)
#  define KEY_UP 12
#  define KEY_DOWN 14
#  define KEY_LEFT 0
#  define KEY_RIGHT 2
#  define KEY_FORWARD 13
#  define KEY_BACK 1
#  define KEY_ZOOMIN 15
#  define KEY_ZOOMOUT 17
#  define KEY_YAW_R 34
#  define KEY_YAW_L 35
#  define KEY_PITCH_UP 37
#  define KEY_PITCH_DOWN 31
#  define KEY_ROLL_R 41
#  define KEY_ROLL_L 40
#  define KEY_SAVE 6
#  define KEY_ESC 53
# endif

#endif // KEYCODES_H