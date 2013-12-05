-module(test).

-export([run/0]).

-define(LEN,100).

run()->
	timer().

timer()->
	Pid=spawn(fun()->
				timer:apply_interval(1000,io,format,["timer,now:~p~n",[calendar:local_time()]])
		end),
	io:format("Pid:~p~n",[Pid]).

l()->
	L=lists:map(fun(I)->{I,I}end,lists:seq(1,?LEN)),
	%timer:tc(lists,keyfind,[?LEN,1,L]).
	erlang:statistics(wall_clock),
	lists:foreach(fun(_)->lists:keyfind(?LEN,1,L) end,lists:seq(1,10000000)),
	{_,T}=erlang:statistics(wall_clock),
	io:format("list time:~p~n",[T]).
	

ets()->
	ets:new(t_ets,[named_table]),
	lists:foreach(fun(I)->
		ets:insert(t_ets,{I,I})
	end,lists:seq(1,?LEN)),
	erlang:statistics(wall_clock),
	lists:foreach(fun(_)->ets:lookup(t_ets,?LEN)end,lists:seq(1,10000000)),
	{_,T}=erlang:statistics(wall_clock),
	io:format("ets time:~p~n",[T]).


