#!/usr/sbin/dtrace -s

/*
 * trace-addon-latency.d: Run this script as:
 *
 *     dtrace -s trace-addon-latency.d -p PID
 *
 * to trace the latency of asynchronous operations kicked off by all add-ons in
 * the node process PID.  NOTE: this will instrument all native functions in all
 * add-ons, which can have a noticeable performance impact, depending on the
 * add-on.
 */

pid$target::uv_queue_work:entry
{
    callers[arg1] = ucaller;
	donefunc[arg1] = arg3;
	starttime[arg1] = timestamp;
}

pid$target:*.node::entry
/donefunc[arg0]/
{
	@[ufunc(callers[arg0])] = quantize(timestamp - starttime[arg0]);
	callers[arg0] = 0;
	starttime[arg0] = 0;
	donefunc[arg0] = 0;
}