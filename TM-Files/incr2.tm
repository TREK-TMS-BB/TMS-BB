INITIAL_INPUT=0

STATES = {gotoVar_0, gotoVar_halt, incr_0, incr_1, incr_2, incr_halt, gotoStart_0, gotoStart_halt, halt} 	

PRODUCTIONS {
gotoVar_0 1 1 r gotoVar_0 ;
gotoVar_0 0 0 r gotoVar_halt ;

gotoVar_halt * * n incr_0 ;

incr_0 1 1 r incr_1 ;
incr_0 0 1 r incr_2 ;
incr_0 B B r incr_halt ;
incr_1 1 1 r incr_1 ;
incr_1 0 1 r incr_2 ;
incr_1 B a r incr_halt ;
incr_2 0 0 r incr_2 ;
incr_2 1 0 r incr_1 ;
incr_2 B 0 n incr_halt ;

incr_halt * * n gotoStart_0 ;

gotoStart_0 1 1 l gotoStart_0 ;
gotoStart_0 0 0 l gotoStart_0 ;
gotoStart_0 B B r gotoStart_halt ;

gotoStart_halt * * n halt ;
} 



