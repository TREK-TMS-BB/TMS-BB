INITIAL_INPUT=0

STATES = {s,0,q,a,b} # you dont have to mention halt

PRODUCTIONS {
s 1 B r 0 ;      # write a Blank on the 1 we are going to delete
0 1 1 r 0 ;
0 0 0 r 0 ;
0 B B l q ;
q 1 B l a ;
q 0 B l b ;
a 1 1 l a ;
a 0 1 l b ;
a B 1 r halt ;
b 0 0 l b ;
b 1 0 l a ;
b B 0 r halt ;
}



