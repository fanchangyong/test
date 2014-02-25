-module(test).

-compile(export_all).

-export([run/0]).

-define(LEN,2000000).
-define(ETS_NAME,ets_name).
-define(TUPLE_LEN,20).

run()->
	test_ets().

test_ets()->
	ets:new(?ETS_NAME,[named_table,set]),
	insert_ets_step(?ETS_NAME,?LEN,?TUPLE_LEN),
	erlang:statistics(wall_clock),
	R=ets:match_object(?ETS_NAME,{'_',2,2,2,2}),
	io:format("result:~p~n",[R]),
	{_,T}=erlang:statistics(wall_clock),
	io:format("T:~p~n",[T]).

insert_ets_step(Ets,0,Len)->
	nothing;
insert_ets_step(Ets,I,Len)->
	insert_ets(Ets,I,Len),
	insert_ets_step(Ets,I-1,Len).


insert_ets(Ets,I,Len)->
	L=lists:map(fun(_)->
								I
						end,lists:seq(1,Len)),
	ets:insert(Ets,list_to_tuple(L)).
	

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
	ets:new(t_ets,[set,named_table]),
	I=1,
	step(?LEN,ets,insert,[t_ets,{I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I}]),
	erlang:statistics(wall_clock),
	%lists:foreach(fun(_)->
										%ets:lookup(t_ets,?LEN,1)end,
								%erlang:garbage_collect(),
								%lists:seq(1,200000000)),
	I=1,
	step(1,ets,lookup,[t_ets,1]),
	{_,T}=erlang:statistics(wall_clock),
	io:format("T:~p~n",[T]).

step(0,_,_,_)->
		nothing;
step(I,Module,Fun,Arg)->
	erlang:apply(Module,Fun,[t_ets,{I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I,I}]),
	step(I-1,Module,Fun,Arg).

