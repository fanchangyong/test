assume cs:codesg,ss:stacksg,ds:datasg

stacksg segment
	dw 0,0,0,0,0,0,0,0
stacksg ends

datasg segment
	db 'BaSiC'
	db 'iNfOrMaTiOn'
datasg ends

codesg segment
	start:
		mov ax,datasg
		mov ds,ax

		mov cx,5
		mov bx,0
		s:
			mov al,[bx+0]	
			and al,11011111b	
			mov [bx+0],al
			mov al,[bx+5]
			or al,00100000b
			mov [bx+5],al
			inc bx
			loop s
codesg ends

end start
