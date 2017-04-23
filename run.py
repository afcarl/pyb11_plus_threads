import sys
sys.path.append('build/Debug')
import dummy
print(dummy.parallel_eval(lambda x: x+1.0, 3.4, 40))