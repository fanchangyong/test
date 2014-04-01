-module(abc).
-include_lib("eunit/include/eunit.hrl").

basic_test()->
	?assert(1==1).

second_test()->
	?assert(1==2).
