import subprocess
import time

subprocess.run(['g++-10', '-std=c++20', '-O3', '-Wno-unused-result', 'main.cc'])
now = time.time()
subprocess.run(['./a.out < ./../in.txt'], shell=True)
print("Execution time : {:.7f}".format(time.time() - now))