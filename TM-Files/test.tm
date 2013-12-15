INITIAL_INPUT=0 

STATES = {14_while_1_0,14_while_1_1,14_while_1_while,14_while_1_trueStart,14_while_1_true,12Decr1_0,12Decr1_1,12Decr1_s,12Decr1_d0,12Decr1_d1,12Decr1_d2,12Decr1_d3,12Decr1_end,12Decr1_halt,13Incr2_0,13Incr2_1,13Incr2_2,13Incr2_3,13Incr2_4,13Incr2_5,13Incr2_halt,14_while_1_end,14_while_1_gotoStart,14_while_1_halt,halt} 

PRODUCTIONS { 
14_while_1_0 1 1 r 14_while_1_0 ;
14_while_1_0 0 0 r 14_while_1_1 ;
14_while_1_1 * * n 14_while_1_while ;
14_while_1_while 0 0 n 14_while_1_gotoStart ;
14_while_1_while 1 1 n 14_while_1_trueStart ;
14_while_1_trueStart 1 1 l 14_while_1_trueStart ;
14_while_1_trueStart 0 0 l 14_while_1_trueStart ;
14_while_1_trueStart _ _ r 14_while_1_true ;
14_while_1_true * * n 12Decr1_0 ;
12Decr1_0 1 1 r 12Decr1_0 ;
12Decr1_0 0 0 r 12Decr1_1 ;
12Decr1_1 * * n 12Decr1_s ;
12Decr1_s 1 _ r 12Decr1_d0 ;
12Decr1_d0 1 1 r 12Decr1_d0 ;
12Decr1_d0 0 0 r 12Decr1_d0 ;
12Decr1_d0 _ _ l 12Decr1_d1 ;
12Decr1_d1 1 _ l 12Decr1_d2 ;
12Decr1_d1 0 _ l 12Decr1_d3 ;
12Decr1_d2 1 1 l 12Decr1_d2 ;
12Decr1_d2 0 1 l 12Decr1_d3 ;
12Decr1_d2 _ 1 n 12Decr1_end ;
12Decr1_d3 1 0 l 12Decr1_d2 ;
12Decr1_d3 0 0 l 12Decr1_d3 ;
12Decr1_d3 _ 0 n 12Decr1_end ;
12Decr1_end 1 1 l 12Decr1_end ;
12Decr1_end 0 0 l 12Decr1_end ;
12Decr1_end _ _ r 12Decr1_halt ;
12Decr1_halt * * n 13Incr2_0 ;
13Incr2_0 1 1 r 13Incr2_0 ;
13Incr2_0 0 0 r 13Incr2_1 ;
13Incr2_1 1 1 r 13Incr2_1 ;
13Incr2_1 0 0 r 13Incr2_2 ;
13Incr2_2 1 1 r 13Incr2_3 ;
13Incr2_2 0 1 r 13Incr2_4 ;
13Incr2_2 _ _ n 13Incr2_5 ;
13Incr2_3 1 1 r 13Incr2_3 ;
13Incr2_3 0 1 r 13Incr2_4 ;
13Incr2_3 _ 1 n 13Incr2_5 ;
13Incr2_4 1 0 r 13Incr2_3 ;
13Incr2_4 0 0 r 13Incr2_4 ;
13Incr2_4 _ 0 n 13Incr2_5 ;
13Incr2_5 1 1 l 13Incr2_5 ;
13Incr2_5 0 0 l 13Incr2_5 ;
13Incr2_5 _ _ r 13Incr2_halt ;
13Incr2_halt * * n 14_while_1_end ;
14_while_1_end * * n 14_while_1_0 ;
14_while_1_gotoStart 1 1 l 14_while_1_gotoStart ;
14_while_1_gotoStart 0 0 l 14_while_1_gotoStart ;
14_while_1_gotoStart _ _ r 14_while_1_halt ;
14_while_1_halt * * n halt ;
}
