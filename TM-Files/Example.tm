INITIAL_INPUT= 00001100		# A string of symbols (letters and numbers)

STATES= { 0, 1, 2, 3x, 3y, 4y, 7} # you dont have to mention halt	1st state is considered to be the startState

PRODUCTIONS {
0 B B r 1 ;			# <CURRENT STATE> <READ SYMBOL> <WRITE SYMBOL> <MOVE> <NEXT STATE>
0 * * r 0 ;			# * stands for any symbol 
1 B B l 2 ;			# B stands for the blank on the tape
1 * * r 1 ;
2 0 B l 3x ;
2 1 B l 3y ;
2 B B l 7 ;
3x B B l 4x ;
3x * * l halt ;		# halt is the accept state of the Turing machine. 
}

