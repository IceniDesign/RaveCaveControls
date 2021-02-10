# My thinking here is to open the second video BEFORE closing the first and then cleaning up.

#import the needed libraries
import os
import sys
import time
import subprocess

#Setup movie locations
movie1 = ("/home/pi/Videos/Loop_Videos/Space4_240.mp4")
movie2 = ("/home/pi/Videos/Loop_Videos/Clouds3_240.mp4")

#and off we go...
os.system('killall omxplayer.bin') #kill OMX in case it is already running

#Play video 1
Clouds = subprocess.Popen(['omxplayer', '--layer', '1', movie2],stdin=subprocess.PIPE) #Load the 1st video
time.sleep(10)

#Play video 2
# Higher numbered layers appear on top
Space = subprocess.Popen(['omxplayer', '--layer', '2', movie1],stdin=subprocess.PIPE) #Load the 2nd video

#Kill video 1
time.sleep(5)
Clouds.stdin.write('q')
Clouds.stdin.flush()

#Kill video 2
time.sleep(5)
Space.stdin.write('q')
Space.stdin.flush()
