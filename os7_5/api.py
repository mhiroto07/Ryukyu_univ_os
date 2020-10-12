import sys
import select

def readline(inputs,timeout):
    readable,_ ,_ =  select.select([inputs], [], [], timeout)
    if len(readable) == 0:
        print ('timed out')
    elif len(readable) == 1:
        readline = inputs.readline().strip()
        print('readable is',readline)
        if (readline.isdecimal()):
            square = int(readline) ** 2
            print('the square of',readline,'is',square)
         
timeout = 5 
readline(sys.stdin,timeout)
