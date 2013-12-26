INITIAL_INPUT = 0 

STATES = { TM-Files/clear.tm_0,TM-Files/clear.tm_true,TM-Files/clear.tm_ds,TM-Files/clear.tm_d0,TM-Files/clear.tm_dq,TM-Files/clear.tm_da,TM-Files/clear.tm_db,TM-Files/clear.tm_end,TM-Files/clear.tm_g0,TM-Files/clear.tm_halt} 

PRODUCTIONS { 
TM-Files/clear.tm_0 0 0 2 TM-Files/clear.tm_halt ;
TM-Files/clear.tm_0 1 1 2 TM-Files/clear.tm_true ;
TM-Files/clear.tm_true * * 2 TM-Files/clear.tm_ds ;
TM-Files/clear.tm_ds 1 _ 1 TM-Files/clear.tm_d0 ;
TM-Files/clear.tm_d0 1 1 1 TM-Files/clear.tm_d0 ;
TM-Files/clear.tm_d0 0 0 1 TM-Files/clear.tm_d0 ;
TM-Files/clear.tm_d0 _ _ 0 TM-Files/clear.tm_dq ;
TM-Files/clear.tm_dq 1 _ 0 TM-Files/clear.tm_da ;
TM-Files/clear.tm_dq 0 _ 0 TM-Files/clear.tm_db ;
TM-Files/clear.tm_da 1 1 0 TM-Files/clear.tm_da ;
TM-Files/clear.tm_da 0 1 0 TM-Files/clear.tm_db ;
TM-Files/clear.tm_da _ 1 1 TM-Files/clear.tm_end ;
TM-Files/clear.tm_db 0 0 0 TM-Files/clear.tm_db ;
TM-Files/clear.tm_db 1 0 0 TM-Files/clear.tm_da ;
TM-Files/clear.tm_db _ 0 1 TM-Files/clear.tm_end ;
TM-Files/clear.tm_end * * 0 TM-Files/clear.tm_g0 ;
TM-Files/clear.tm_g0 1 1 0 TM-Files/clear.tm_g0 ;
TM-Files/clear.tm_g0 0 0 0 TM-Files/clear.tm_g0 ;
TM-Files/clear.tm_g0 _ _ 1 TM-Files/clear.tm_0 ;
}