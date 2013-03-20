from __future__ import division
from collections import Counter
import numpy
from pylab import *

def the_bytes(filename="binary_output.dat"):
    f = open(filename).read()
    return (ord(c) for c in f)

if __name__ == "__main__":
    c = [0]*256
    for byte in the_bytes():
        c[byte] += 1

    print max(c)
    print min(c)
    print numpy.average(c)
    print numpy.std(c)
    hist(list(the_bytes()))
    show()
