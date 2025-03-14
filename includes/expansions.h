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

# define DNUL ""

#endif
