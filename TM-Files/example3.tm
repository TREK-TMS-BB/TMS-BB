INITIAL_INPUT = 00001100		# A string of symbols (letters and numbers)

STATES = { 0, 1, 2, 3} # you dont have to mention halt	1st state is considered to be the startState

PRODUCTIONS {
0 0 X r 1 ;			# <CURRENT STATE> <READ SYMBOL> <WRITE SYMBOL> <MOVE> <NEXT STATE>
0 Y Y r 3 ;			# * stands for any symbol 
1 0 0 r 1 ;			# B stands for the blank on the tape
1 1 Y l 2 ;
1 Y Y r 1 ;

2 0 0 l 2 ;
2 X X r 0 ;
2 Y Y l 2 ;
3 Y Y r 3 ;
3 B B r halt ;		# halt is the accept state of the Turing machine. 
}

