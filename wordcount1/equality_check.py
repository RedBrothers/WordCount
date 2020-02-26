import sys
import os
import numpy as np
from subprocess import Popen, PIPE


def main(N):
    config_dat =    "infile=../data/sample_1/data.zip\n" +\
                    "out_by_a=./res_a_{}.txt\n" +\
                    "out_by_n=./res_n_{}.txt\n" +\
                    "threads=4\n"
    res_by_a = []
    res_by_n = []

    times = []
    for i in range(N):
        filename = 'config_{}.dat'.format(i)

        with open(filename, 'w') as f:
            f.write(config_dat.format(i, i))
        p = Popen(
            ['./wordcount {}'.format(filename)],
            shell=True,
            stdout=PIPE,
            stdin=PIPE
        )
        (output, err) = p.communicate()
        p.kill()
        os.remove(filename)
        output = output.decode("utf-8")
        time_i = output.split('\n')[-2].split()[-2]
        times.append(time_i)

        res_a_file = './res_a_{}.txt'.format(i)
        res_n_file = './res_n_{}.txt'.format(i)

        with open(res_a_file, 'r') as f:
            res_by_a.append(f.read())
        os.remove(res_a_file)

        with open(res_n_file, 'r') as f:
            res_by_n.append(f.read())
        os.remove(res_n_file)

        if i > 1:
            if res_by_a[i] != res_by_a[i - 1]:
                print('./res_a_{}.txt and ./res_a_{}.txt are NOT EQUAL'.format(i, i - 1))
                exit(1)
            if res_by_n[i] != res_by_n[i - 1]:
                print('./res_a_{}.txt and ./res_a_{}.txt are NOT EQUAL'.format(i, i - 1))
                exit(1) # 130207, 125058
    times = np.array(times)
    print("OK")
    best_it = np.argmin(times)
    print("Best iteration - {}, {} seconds".format(best_it, times[best_it]))

def usage():
    print ("Usage: python3 test.py [num_of_run]")
    exit(0)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        usage()

    N = int(sys.argv[1])
    main(N)
