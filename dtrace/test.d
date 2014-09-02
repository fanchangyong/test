#!/usr/sbin/dtrace -s

#pragma D option quiet

profile-997hz
/arg0/
{
	@[func(caller),func(arg0)] = count();
}

tick-5sec
{
	trunc(@,10);
	printf("%-24s %-32s %-8s\n","CALLER","FUNCTION","COUNT");
	printa("%-24a %-32a %-@8d\n",@);
	exit(0);
}
