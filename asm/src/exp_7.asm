assume cs:codesg,ds:datasg,ss:stacksg

stacksg segment
	db 32 dup(0)
stacksg ends

datasg segment
	db '1975','1976','1977', '1978', '1979', '1980', '1981', '1982', '1983', '1984','1985','1986','1987','1988','1989','1990','1991','1992','1993','1994','1995'
	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514,345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226,11542,14430,15257,17800
datasg ends

table segment
	db 21 dup('year summ ne ?? ')
table ends

codesg segment
	start:
		mov ax,stacksg
		mov ss,ax
		mov sp,32
		mov ax,datasg
		mov ds,ax
		mov ax,table
		mov es,ax

; COPY YEAR DATA
		mov cx,21
		mov bx,0
		mov bp,0
		s:
			push cx
			mov cx,4
			mov si,0
			s0:
				mov ah,[bx]
				mov byte ptr es:[bp+si],ah
				inc bx
				inc si
			loop s0
			pop cx
			add bp,10h
		loop s

; COPY INCOME DATA
		mov cx,21
		mov bx,84
		mov bp,0
		s1:
			mov ax,[bx]	
			mov word ptr es:[bp+5],ax
			add bx,2
			mov ax,[bx]
			mov word ptr es:[bp+7],ax
			add bx,2
			add bp,10h
		loop s1

; COPY MEMBER COUNT
		mov cx,21
		mov bx,168
		mov bp,0
		s2:
			mov ax,[bx]
			mov word ptr es:[bp+10],ax
			add bx,2
			add bp,10h
		loop s2
	
; COPY AVERAGE INCOME
		mov cx,21
		mov bx,84
		mov bp,0
		mov si,168
		s3:
			mov ax,[bx]	
			mov dx,[bx+2]
			div word ptr [si]
			mov es:[bp+13],ax
			add bp,10h
			add bx,4
			add si,2
		loop s3

		mov ax,4c00h
		int 21h
codesg ends


end start
