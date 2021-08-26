// This program assumes that your screen brightness goes from 0 to 96000



// gcc setbl.c ; doas chown root:root a.out ; doas chmod 4755 a.out
// ./a.out [n]

/*
#!/bin/sh
# 96000 to 0
echo $1 > /sys/class/backlight/intel_backlight/brightness
*/




#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main
(int argc, char ** argv)
{
	int len = 0, i;
	char out [6] = {0};
	if (argc <= 1)
	{
		printf ("no number supplied");
		return 0;
	}
	setuid (0);
	FILE * filep = fopen ("/sys/class/backlight/intel_backlight/brightness", "w");
	while (argv [1] [len] != 0) // strlen, "50" -> 2
		++len;
	if (len > 2) // if there are three or more digits, do it normally
		fputs (argv[1], filep);
	else // append three '0' to number.  This can result in "0000", which could be a problem, but isn't in my case.  Also, in my case, writing something that is not a number doesn't change anything.
	{ // and who else will use this?
		for (i = 0; i < len; ++i)
			out [i] = argv [1] [i];
		while (i < len + 3)
			out [i] = '0', ++i;
		fputs (out, filep);
	}
	fclose (filep);
	return 0;
}
