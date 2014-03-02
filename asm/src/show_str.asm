assume cs:codesg,ds:datasg

datasg segment
	db 'Welcome to masm!',0
datasg ends

stacksg segment
	db 32 dup(0)
stacksg ends

codesg segment
	start:
		
		mov ax,datasg
		mov ds,ax
		mov ax,stacksg
		mov ss,ax
		mov sp,32

		mov dh,8
		mov dl,3
		mov cl,2
		mov si,0
		call show_str
		
		mov ax,4c00h
		int 21h


	show_str:

		mov di,0
		mov al,160
		mul dh
		add di,ax
		mov al,2
		mul dl
		add di,ax

		mov ax,0b800h
		mov es,ax

		mov bl,cl
	s:
		mov ch,0
		mov cl,[si]
		mov es:[di],cl
		mov es:[di+1],bl
		
		jcxz ok

		add di,2
		inc si

		loop s

	ok:
		ret

codesg ends


end start
