# Working but still set to different parts of the screen for troubleshooting

#import the needed libraries
import os
import sys
import time
import subprocess
import RPi.GPIO as GPIO

#Set GPIO pin format
GPIO.setmode(GPIO.BCM)

#Setup the GPIO buttons
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP) #YELLOW
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP) #RED
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP) #WHITE

#Setup movie locations
movie1 = ("/home/pi/Videos/Loop_Videos/Clouds3_240.mp4")
movie2 = ("/home/pi/Videos/Loop_Videos/Space4_240.mp4")

Clouds = '' #Define them early so we can kill them even if they aren't running
Space = '' #Define them early so we can kill them even if they aren't running

#and off we go...
os.system('killall omxplayer.bin') #kill OMX in case it is already running
Space = subprocess.Popen(['omxplayer', '--loop', '--win', '600,100,900,400', '--layer', '1', movie2],stdin=subprocess.PIPE) #Load the 1st video
        
while True:
    #Read states of the inputs
    input_state1 = GPIO.input(17)
    input_state2 = GPIO.input(18)
    quit_video = GPIO.input(24)

    #If GPIO(17) is shorted to ground
    if input_state1 == False:
        #Play video 1
        Clouds = subprocess.Popen(['omxplayer', '--loop', '--win', '100,100,400,400', '--layer', '2', movie1],stdin=subprocess.PIPE) #Load the 1st video
        time.sleep(5)
        Space.stdin.write('q')
        Space.stdin.flush()


    #If GPIO(18) is shorted to ground
    elif input_state2 == False:
        #Play video 1
        Space = subprocess.Popen(['omxplayer', '--loop', '--win', '600,100,900,400', '--layer', '3', movie2],stdin=subprocess.PIPE) #Load the 1st video
        time.sleep(5)
        Clouds.stdin.write('q')
        Clouds.stdin.flush()
                
    #If GPIO(24) is shorted to ground
    if quit_video == False:
        os.system('killall omxplayer.bin')
        exit()
