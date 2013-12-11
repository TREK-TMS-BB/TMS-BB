INITIAL_INPUT=0 

STATES = {TM-Files/incr2.tm_gotoVar_0,TM-Files/incr2.tm_gotoVar_halt,TM-Files/incr2.tm_incr_0,TM-Files/incr2.tm_incr_1,TM-Files/incr2.tm_incr_2,TM-Files/incr2.tm_incr_halt,TM-Files/incr2.tm_gotoStart_0,TM-Files/incr2.tm_gotoStart_halt,TM-Files/incr2.tm_halt,TM-Files/decr.tm_s,TM-Files/decr.tm_0,TM-Files/decr.tm_q,TM-Files/decr.tm_a,TM-Files/decr.tm_b,TM-Files/decr.tm_halt,halt} 

PRODUCTIONS { 
TM-Files/incr2.tm_gotoVar_0 1 1 r TM-Files/incr2.tm_gotoVar_0 ;
TM-Files/incr2.tm_gotoVar_0 0 0 r TM-Files/incr2.tm_gotoVar_halt ;
TM-Files/incr2.tm_gotoVar_halt * * n TM-Files/incr2.tm_incr_0 ;
TM-Files/incr2.tm_incr_0 1 1 r TM-Files/incr2.tm_incr_1 ;
TM-Files/incr2.tm_incr_0 0 1 r TM-Files/incr2.tm_incr_2 ;
TM-Files/incr2.tm_incr_0 _ _ r TM-Files/incr2.tm_incr_halt ;
TM-Files/incr2.tm_incr_1 1 1 r TM-Files/incr2.tm_incr_1 ;
TM-Files/incr2.tm_incr_1 0 1 r TM-Files/incr2.tm_incr_2 ;
TM-Files/incr2.tm_incr_1 _ a r TM-Files/incr2.tm_incr_halt ;
TM-Files/incr2.tm_incr_2 0 0 r TM-Files/incr2.tm_incr_2 ;
TM-Files/incr2.tm_incr_2 1 0 r TM-Files/incr2.tm_incr_1 ;
TM-Files/incr2.tm_incr_2 _ 0 n TM-Files/incr2.tm_incr_halt ;
TM-Files/incr2.tm_incr_halt * * n TM-Files/incr2.tm_gotoStart_0 ;
TM-Files/incr2.tm_gotoStart_0 1 1 l TM-Files/incr2.tm_gotoStart_0 ;
TM-Files/incr2.tm_gotoStart_0 0 0 l TM-Files/incr2.tm_gotoStart_0 ;
TM-Files/incr2.tm_gotoStart_0 _ _ r TM-Files/incr2.tm_gotoStart_halt ;
TM-Files/incr2.tm_gotoStart_halt * * n TM-Files/incr2.tm_halt ;
TM-Files/incr2.tm_halt * * n TM-Files/decr.tm_s ;
TM-Files/decr.tm_s 1 _ r TM-Files/decr.tm_0 ;
TM-Files/decr.tm_0 1 1 r TM-Files/decr.tm_0 ;
TM-Files/decr.tm_0 0 0 r TM-Files/decr.tm_0 ;
TM-Files/decr.tm_0 _ _ l TM-Files/decr.tm_q ;
TM-Files/decr.tm_q 1 _ l TM-Files/decr.tm_a ;
TM-Files/decr.tm_q 0 _ l TM-Files/decr.tm_b ;
TM-Files/decr.tm_a 1 1 l TM-Files/decr.tm_a ;
TM-Files/decr.tm_a 0 1 l TM-Files/decr.tm_b ;
TM-Files/decr.tm_a _ 1 n TM-Files/decr.tm_halt ;
TM-Files/decr.tm_b 0 0 l TM-Files/decr.tm_b ;
TM-Files/decr.tm_b 1 0 l TM-Files/decr.tm_a ;
TM-Files/decr.tm_b _ 0 n TM-Files/decr.tm_halt ;
TM-Files/decr.tm_halt * * n halt ;
}