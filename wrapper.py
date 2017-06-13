from time import strftime, gmtime

import numpy as np
import os, push

step   = 6E-09
nsteps = int(1E+4)

def stamp():
    '''Returns GMT timestamp'''
    return strftime("%H%M%S", gmtime())

if __name__ == '__main__':
    if 'data' not in os.listdir('.'):
        os.mkdir('data')

    savedir = 'data/%s/' % stamp()
    os.mkdir(savedir)

    my_track = push.track('pbar')
    my_track.leapfrog(step, nsteps, '%strack.bin' % savedir)
