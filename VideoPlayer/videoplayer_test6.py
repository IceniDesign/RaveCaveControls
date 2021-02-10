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

#VARIABLES
movie1 = ("/home/pi/Videos/Loop_Videos/Space_u9TuAZHeziw_240p.mp4")
movie2 = ("/home/pi/Videos/Loop_Videos/Clouds_0_jNjpVxUt0_240p.mp4")
Layer = 1 #this needs to be presented as a string not a variable
OMX1 = '' #Define them early so we can try and kill them even if they aren't running
OMX1_active = False
OMX2 = '' #Define them early so we can try and kill them even if they aren't running
OMX2_active = False

#and off we go...
os.system('killall omxplayer.bin') #kill OMX in case it is already running
#Space = subprocess.Popen(['omxplayer', '--loop', '--win', '600,100,900,400', '--layer', str(Layer), movie2],stdin=subprocess.PIPE) #Load the 1st video
OMX1_active = True
OMX1 = subprocess.Popen(['omxplayer', '--loop', '--win', '600,100,900,400', '--layer', str(Layer), movie1],stdin=subprocess.PIPE) #Load the 1st video
        
while True:
    #Read states of the inputs
    button1 = GPIO.input(17)
    button2 = GPIO.input(18)
    quit_video = GPIO.input(24)

    #If GPIO(17) is shorted to ground
    if button1 == False: #If button1 is pressed...
        if OMX1_active == False: #And movie1 is not already running
            #Play movie1
            Layer = Layer + 1
            OMX1_active = True
            OMX1 = subprocess.Popen(['omxplayer', '--loop', '--win', '600,100,900,400', '--layer', str(Layer), movie1],stdin=subprocess.PIPE) #Load the 1st video
            time.sleep(5)
            if OMX2_active == True: #shutdown movie2 if it is playing
                OMX2.stdin.write('q')
                OMX2.stdin.flush()
                OMX2_active = False

    elif button2 == False: #ElseIf button2 is pressed...
        if OMX2_active == False: #And movie1 is not already running
            #Play movie2
            Layer = Layer + 1
            OMX2_active = True
            OMX2 = subprocess.Popen(['omxplayer', '--loop', '--win', '600,100,900,400', '--layer', str(Layer), movie2],stdin=subprocess.PIPE) #Load the 1st video
            time.sleep(5)
            if OMX1_active == True: #shutdown movie2 if it is playing
                OMX1.stdin.write('q')
                OMX1.stdin.flush()
                OMX1_active = False
                
    #If GPIO(24) is shorted to ground
    if quit_video == False:
        os.system('killall omxplayer.bin')
        exit()
