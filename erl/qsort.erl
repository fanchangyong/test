-module(qsort).

-compile(export_all).

part(_,[],R)->
	R;
part(Pivot,[H|T],{Less,Equal,Greater})->
	if
		Pivot<H->
			part(Pivot,T,{[H|Less],Equal,Greater});
		Pivot>H->
			part(Pivot,T,{Less,Equal,[H|Greater]});
		true->
			part(Pivot,T,{Less,[H|Equal],Greater})
	end.

qsort([H|T])->
	{Less,Equal,Greater}=part(H,T,{[],[H],[]}),
	qsort(Less)++Equal++qsort(Greater);
qsort([])->
	[].

test()->
		Arr=qsort([5,4,3,2,1]),
		io:format("Arr:~p~n",[Arr]).
