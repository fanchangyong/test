assume cs:codesg

datasg segment
	db 'welcome to masm!'
datasg ends

codesg segment
	start:
		mov ax,datasg
		mov ds,ax

		mov ax,0b800h
		mov es,ax

		mov cx,10h
		mov bx,0
		mov bp,1920
	s:
		mov al,[bx]
		mov ah,011011010b
		mov es:[bp+60],ax
		inc bx
		add bp,2
		loop s

		mov cx,10h
		mov bx,0
		mov bp,2080
	s1:
		mov al,[bx]
		mov ah,011001010B
		mov es:[bp+60],ax
		inc bx
		add bp,2
		loop s1

		mov cx,10h
		mov bx,0
		mov bp,2240
	s2:
		mov al,[bx]
		mov ah,011110001B
		mov es:[bp+60],ax
		inc bx
		add bp,2
		loop s2

		mov ax,4c00h
		int 21h

codesg ends

end start
