-module(test_multicore).

-define(LEN,10000000).
-define(CPU,8).

worker(I,J,Pid,Sum)->
	if
		I>=J->
			Pid ! Sum;
		true->
			worker(I+1,J,Pid,I+I+1)
	end.

run()->
	lists:foreach(fun(I)->
			WorkerCount = ?LEN div ?CPU,
			Start=I*WorkerCount,
			Fin=(I+1)*WorkerCount,
			spawn(?MODULE,worker,[Start,Fin,self(),0])
		end,lists:seq(1,?CPU)),
	
	lists:foreach(fun(_)->
				receive
					Any->
						io:format("received result:~p~n",Any)
		end,lists:seq(1,?CPU)).

