INITIAL_INPUT = 0

STATES = { 0,true,ds,d0,dq,da,db,end,g0, halt } 	# you dont have to mention halt

PRODUCTIONS {
0 0 0 n halt ;           # end of while loop
0 1 1 n true ;           # here link to rest of while loop
true * * n ds ;
ds 1 B r d0 ;      		 # write a Blank on the 1 we are going to delete
d0 1 1 r d0 ;
d0 0 0 r d0 ;
d0 B B l dq ;			# go till end of input on tape
dq 1 B l da ;
dq 0 B l db ;
da 1 1 l da ;
da 0 1 l db ;
da B 1 r end ;
db 0 0 l db ;
db 1 0 l da ;
db B 0 r end ;
end * * l g0 ;
g0 1 1 l g0 ;
g0 0 0 l g0 ;
g0 B B r 0 ;
} 



