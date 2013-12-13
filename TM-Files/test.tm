INITIAL_INPUT=0 

STATES = {0,1,s,d0,d1,d2,d3,end,halt} 

PRODUCTIONS { 
0 1 1 r 0 ;
0 0 0 r 1 ;
1 * * n s ;
s 1 _ r d0 ;
d0 1 1 r d0 ;
d0 0 0 r d0 ;
d0 _ _ l d1 ;
d1 1 _ l d2 ;
d1 0 _ l d3 ;
d2 1 1 l d2 ;
d2 0 1 l d3 ;
d2 _ 1 n end ;
d3 1 0 l d2 ;
d3 0 0 l d3 ;
d3 _ 0 n end ;
end 1 1 l end ;
end 0 0 l end ;
end _ _ r halt ;
}
