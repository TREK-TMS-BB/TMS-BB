INITIAL_INPUT=0 

STATES = {0,1,2,3,4,wr0,goS,halt} 

PRODUCTIONS { 
0 * * n 1 ;
1 0 0 n wr0 ;
1 1 Y r 2 ;
2 0 0 r 2 ;
2 1 1 r 2 ;
2 _ 1 l 3 ;
3 0 0 l 3 ;
3 1 1 l 3 ;
3 Y 1 r 1 ;
wr0 0 0 r wr0 ;
wr0 1 1 r wr0 ;
wr0 _ 0 n goS ;
goS 0 0 l goS ;
goS 1 1 l goS ;
goS _ _ r halt ;
}
