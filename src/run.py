import subprocess


subprocess.run(['g++-10', '-std=c++20', '-O3', '-Wno-unused-result', 'main.cc'])
subprocess.run(['./a.out < ./../in.txt'], shell=True)