-module(test_link).

-compile(export_all).

%% 1.两个进程A/B,B进程调用了link(A),如果A调用了exit(normal),进程B不会有任何影响
%% 2.两个进程A/B,B进程调用了link(A),如果A调用了exit(Reason),Reason不为normal的情况下，又会分两种情况:
%% {{{
%% 	a. B进程调用了process_flag(trap_exit,true),那么B进程会收到{'EXIT',Pid,Reason}消息,B进程不会消亡.A进程正常死亡
%% 	b. B进程没有调用process_flag(trap_exit,true),那么B进程跟着消亡
%% }}}
%% 3.如果一个进程没有与其他进程link，它死亡将不会影响别人。
%% 4.如果一个进程是后台进程，死亡之后不会有打印。(Why???)

run()->
	io:format("Error handler of Main:~p~n",[process_info(self(),error_handler)]),
	spawn(fun()-> 
				io:format("My error handler:~p~n",[process_info(self(),error_handler)]),
				throw(norm) 
		end),
	spawn_link(fun test_other_dead/0).

test_other_dead()->
	register(master,self()),
	Pid=spawn(fun()->
					register(worker,self()),
					loop()
			end),
	process_flag(trap_exit,true),
	loop().


loop()->
	receive
		Any->
			io:format("Received :~p,in :~p~n",[Any,self()]),
			loop()
	end.
