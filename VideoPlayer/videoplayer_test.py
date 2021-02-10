#import the needed libraries
import os
import sys
from subprocess import Popen

#Setup movie locations
movie1 = ("/home/pi/Videos/Loop_Videos/Clouds3_240.mp4")
omx = Popen(['omxplayer', '--win', '100,100,400,400', movie1])