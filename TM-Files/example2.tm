INITIAL_INPUT = 00001100		# A string of symbols (letters and numbers)

STATES = { 0, 1} # you dont have to mention halt	1st state is considered to be the startState

PRODUCTIONS {
0 B B l 1 ;			# <CURRENT STATE> <READ SYMBOL> <WRITE SYMBOL> <MOVE> <NEXT STATE>
0 0 1 r 0 ;			# * stands for any symbol 
0 1 0 r 0 ;
1 B B r halt ;			# B stands for the blank on the tape
}

