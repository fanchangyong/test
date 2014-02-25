assume cs:codesg,ss:stacksg,ds:datasg

stacksg segment
	dw 0,0,0,0,0,0,0,0
stacksg ends

datasg segment
	db '1. display      '
	db '2. brows        '
	db '3. replace      '
	db '4. modify       '
datasg ends

codesg segment
	start:
		mov ax,[ax]
codesg ends

end start
