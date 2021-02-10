#This script works but there is a big lag between one video closing and another opening which exposes the desktop

#import the needed libraries
import RPi.GPIO as GPIO
import os
import sys
from subprocess import Popen

#Set GPIO pin format
GPIO.setmode(GPIO.BCM)

#Setup the GPIO buttons
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP) #YELLOW
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP) #RED
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP) #WHITE

#Setup movie locations
movie1 = ("/home/pi/Videos/Loop_Videos/Space1.mp4")
movie2 = ("/home/pi/Videos/Loop_Videos/Clouds_FlyThrough.mp4")

#Set variables
input_state1 = True
input_state2 = True
quit_video = True

#and off we go...
os.system('killall omxplayer.bin') #kill OMX if it is running
omx = Popen(['omxplayer', '--loop', movie1]) #Load the default video

while True:
    #Read states of the inputs
    input_state1 = GPIO.input(17)
    input_state2 = GPIO.input(18)
    quit_video = GPIO.input(24)

    #If GPIO(17) is shorted to ground
    if input_state1 == False:
        os.system('killall omxplayer.bin')
        omx = Popen(['omxplayer', '--loop', movie1])

    #If GPIO(18) is shorted to ground
    elif input_state2 == False:
        os.system('killall omxplayer.bin')
        omx = Popen(['omxplayer', '--loop', movie2])
                
    #If GPIO(24) is shorted to ground
    if quit_video == False:
        os.system('killall omxplayer.bin')
        exit()
        
        


