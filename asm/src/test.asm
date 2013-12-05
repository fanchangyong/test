assume cs:codesg

codesg segment

	mov ax,cs
	mov ds,ax

	mov ax,0020h
	mov es,ax
	mov bx,0
	mov cx, offset e

	s:
		mov al,[bx]
		mov es:[bx],al
		inc bx
		loop s

	e:
		mov ax,4c00h
		int 21h


codesg ends

end
