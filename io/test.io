#! /usr/local/bin/io

obj := Object clone

obj showCall := method(
	"sender is:" print ;
	call sender println;
	"type is:" print;
	call sender type println;
	"is lobby:" print;
	((call sender) == Lobby )println

	"target is:" print;
	call target println;

	"is obj:" print;
	(obj == call target) println

	"messgae is:" print
	(call message name) println
	"args is:" print
	(call message arguments) println
	"whatis isFalse:" print
	ifFalse(write("iffalse\n"))
	ifTrue(write("iffalse\n"))
)


unless := method(
	(
		call sender doMessage(call message argAt(0)))
		"iffalse:" print
		ifFalse type println
		ifFalse(
	 		call sender doMessage(call message argAt(1))
		) 
		ifTrue(
		 call sender doMessage(call message argAt(2))
	 )
	);

Object ancestors := method(
	prototype := self proto
	if(prototype != Object,
		writeln("Slot of ",prototype type ,"\n--------------"
		)

		prototype slotNames foreach(slotName,writeln(slotName))
		writeln
		prototype ancestors)
)

Animal := Object clone
Animal speak := method(
	"ambiguous animal noise " println
)

Duck := Animal clone
Duck speak := method(
	"quack" println
)

Duck walk := method(
	"waddle" println
)

disco := Duck clone
disco ancestors
