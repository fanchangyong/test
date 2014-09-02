#!/usr/bin/env dtrace -s

#pragma D option quiet

BEGIN
{
	printf("Tracing,press control-c to end...\n");
}

pid$target::malloc:entry
{
	@["malloc calls"] = count();
	ustack();
}

pid$target::free:entry
{
	@["free calls"] = count();
}
