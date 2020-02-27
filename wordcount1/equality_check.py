import sys
import os
import numpy as np
from subprocess import Popen, PIPE


def usage():
    print ("Usage: python3 test.py [num_of_run]")
    exit(0)


def main():
    if len(sys.argv) != 2:
        usage()

    N = int(sys.argv[1])
    res_by_a = []
    res_by_n = []

    times = []
    for i in range(N):
        p = Popen(
            ['./wordcount'],
            shell=True,
            stdout=PIPE,
            stdin=PIPE
        )
        (output, err) = p.communicate()
        p.kill()
        output = output.decode("utf-8")
        time = output.split()[-2]
        times.append(float(time))

        res_a_file = './res_a.txt'
        res_n_file = './res_n.txt'

        with open(res_a_file, 'r') as f:
            res_by_a.append(f.read())
        os.remove(res_a_file)

        with open(res_n_file, 'r') as f:
            res_by_n.append(f.read())
        os.remove(res_n_file)

        if i > 1:
            if res_by_a[i] != res_by_a[i - 1]:
                print(f'./res_a_{i}.txt and ./res_a_{i-1}.txt are NOT EQUAL')
                exit(1)
            if res_by_n[i] != res_by_n[i - 1]:
                print(f'./res_n_{i}.txt and ./res_n_{i-1}.txt are NOT EQUAL')
                exit(1) # 130207, 125058

    print("OK")
    best_it = np.argmin(times)
    print(f"Best iteration: {best_it}, ellapsed time: {times[best_it]:.3f} seconds")


if __name__ == "__main__":
    main()
