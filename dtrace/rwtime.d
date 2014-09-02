syscall::read:entry,
syscall::write_nocancel:entry
/pid == $1/
{
	ts[probefunc] = timestamp;
}

syscall::read:return,
syscall::write_nocancel:return
/pid == $1 && ts[probefunc] != 0/
{
	printf("%s %d nsecs\n", probefunc,timestamp - ts[probefunc]);
}
