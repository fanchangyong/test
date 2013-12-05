mkdir out
masm5\masm src\test.asm out\test.obj out\test.lst out\test.crf

masm5\link out\test.obj ;
