assume cs:codesg,ds:datasg,ss:stacksg

stacksg segment
	db 32 dup(0)
stacksg ends

datasg segment
	db 'ibm             '
	db 'dec             '
	db 'dos             '
	db 'vax             '
datasg ends

codesg segment
	start:
		mov ax,datasg
		mov ds,ax
		
		mov cx,6
		mov bx,0
		s:
			push cx	
			mov cx,3
			mov si,0
			s0:
				mov al,[bx+si]
				and al,11011111b
				mov [bx+si],al
				inc si
				loop s0
			pop cx
			add bx,16
		loop s
codesg ends

end start
