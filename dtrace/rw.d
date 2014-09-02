syscall::read:entry,
syscall::write:entry,
syscall::write_nocancel:entry
/pid == $1/
{
	printf("%s(%d, 0x%x, %4d)", probefunc, arg0, arg1, arg2);
}

syscall::read:return,
syscall::write:return
/pid == $1/
{
	printf("\t\t = %d\n", arg1);
}
