import os
import platform

pf = platform.system()

if os.name == 'nt':
    print('on Windows')
elif os.name == 'posix':
    print('on Max or Linux')
    if pf == 'Windows':
        print('on Windows')
    elif pf == 'Darwin':
        print('on Mac')
    elif pf == 'Linux':
        print('on Linux')
       