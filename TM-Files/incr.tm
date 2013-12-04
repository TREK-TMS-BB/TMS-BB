INITIAL_INPUT=0

STATES = {0,a,b} # you dont have to mention halt

PRODUCTIONS {
0 1 1 r a ;
0 0 1 r b ;
0 B B r halt ;
a 1 1 r a ;
a 0 1 r b ;
a B 1 r halt ;
b 0 0 r b ;
b 1 0 r a ;
b B 0 r halt ;
}



