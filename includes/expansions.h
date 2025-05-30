/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrleroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:00:55 by chrleroy          #+#    #+#             */
/*   Updated: 2025/05/30 13:09:18 by chrleroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "structures.h"

// Standard keys as defined by Bash
# define DKCT 10

typedef enum special_keys
{
	DSTRI,
	DAROI,
	DHASI,
	DEXTI,
	DHYPI,
	DPIDI,
	DCIDI,
	DNMEI,
	DLSTI,
	DIFSI,
	DKCTI,
}	t_keys;

# define SPE_EXP_CHAR "*@#?-$!"

# define DSTR "$*"
# define DARO "$@"
# define DHAS "$#"
# define DEXT "$?"
# define DHYP "$-"
# define DPID "$$"
# define DCID "$!"
# define DNME "$0"
# define DLST "$_"
# define DIFS "$IFS"


# define VSTR ""
# define VARO ""
# define VHAS ""
# define VEXT "0"
# define VHYP "--posix"
# define VPID "SHELLS PID"
# define VCID "LAST JOBS PID"
# define VNME "MINISLAY"
# define VLST "JSP"
# define VIFS " 	\n"

# define ISTR "$*="
# define IARO "$@="
# define IHAS "$#="
# define IEXT "$?=0"
# define IHYP "$-=--posix"
# define IPID "$$="
# define ICID "$!=0"
# define INME "$0="
# define ILST "$_="
# define IIFS "$IFS= 	\n"

# define DNUL ""

#endif
