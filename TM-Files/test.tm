INITIAL_INPUT=0 

STATES = {0,1,while,true,ds,d0,d1,d2,d3,dend,halt} 

PRODUCTIONS { 
0 1 1 r 0 ;
0 0 0 r 1 ;
1 * * n while ;
while 0 0 n halt ;
while 1 1 n true ;
true * * n ds ;
ds 1 _ r d0 ;
d0 1 1 r d0 ;
d0 0 0 r d0 ;
d0 _ _ l d1 ;
d1 1 _ l d2 ;
d1 0 _ l d3 ;
d2 1 1 l d2 ;
d2 0 1 l d3 ;
d2 _ 1 n dend ;
d3 1 0 l d2 ;
d3 0 0 l d3 ;
d3 _ 0 n dend ;
dend * * n while ;
}
