#Working and featuring a debug mode to allow troubleshooting.
#Debug mode put the video playback into a window rather than fullscreen
#Set the IceniDebug Variable to True to enable Debug Mode

#Run from CLI using "sudo python /home/Pi/Documents/videoplayer.py
#OR to run from an IDE add the following after each OMX PIPE ",encoding='utf8'"

#Exit the script using CTRL+C

#Added a 6th button as we don't need the exit button anymore.

#import the needed libraries
import os
import sys
import time
import subprocess
import RPi.GPIO as GPIO

#Set GPIO pin format
GPIO.setmode(GPIO.BCM)

#Setup the GPIO buttons
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP) #YELLOW #1
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP) #RED #2
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP) #WHITE #Quit
GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_UP) #BLUE #3
GPIO.setup(22, GPIO.IN, pull_up_down=GPIO.PUD_UP) #GREEN #4
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP) #BLACK #5

#VARIABLES
IceniDebug = True #If this is set to true video playback will be in a window not fullscreen
WinSize = '600,100,900,400' #Size of video playback when debugging - x1,y1,x2,y2

movie1 = ("/home/pi/Videos/Loop_Videos/Desert_1mexsOOHBSA_240p.mp4")
movie2 = ("/home/pi/Videos/Loop_Videos/Sunset_A9cHouJRGsU_240p.mp4")
movie3 = ("/home/pi/Videos/Loop_Videos/Fish_A2WqvBVCUJQ_360p.mp4")
movie4 = ("/home/pi/Videos/Loop_Videos/Clouds_0_jNjpVxUt0_240p.mp4")
movie5 = ("/home/pi/Videos/Loop_Videos/Space_u9TuAZHeziw_240p.mp4")
movie6 = ("/home/pi/Videos/Loop_Videos/LavaHall_0vcQInJglsE_240p.mp4")

Layer = 1 #Initial layer value, this needs to be presented as a string not a variable, higher numbers on top

#Define them early so we can try and kill them even if they aren't running
OMX1 = '' 
OMX1_active = False
OMX2 = ''
OMX2_active = False
OMX3 = ''
OMX3_active = False
OMX4 = ''
OMX4_active = False
OMX5 = ''
OMX5_active = False
OMX6 = ''
OMX6_active = False

###########  and off we go ##########

#kill OMX in case it is already running
os.system('killall omxplayer.bin') 

#Start with flying through space
OMX5_active = True
if IceniDebug == True:
    #Play movie5 in a window
    OMX5 = subprocess.Popen(['omxplayer', '--loop', '--win', WinSize, '--layer', str(Layer), movie5],stdin=subprocess.PIPE) #Load the 1st video
else:
    #Play movie5 fullscreen
    OMX5 = subprocess.Popen(['omxplayer', '--loop', '--layer', str(Layer), movie5],stdin=subprocess.PIPE) #Load the 1st video
           
try: #wrapped in a try loop so we can quit with a keyboard press if needed.       
    while True:
        #Read states of the inputs
        button1 = GPIO.input(17) #Yellow
        button2 = GPIO.input(18) #Red
        button3 = GPIO.input(27) #Blue
        button4 = GPIO.input(22) #Green
        button5 = GPIO.input(23) #Black
        button6 = GPIO.input(24) #White

        #If GPIO(17) is shorted to ground
        if button1 == False: #If button1 is pressed...
            if OMX1_active == False: #And movie1 is not already running
                #Play movie1
                Layer = Layer + 1
                OMX1_active = True
                print("Button Pressed - Yellow")
                print("Flying to the Desert planet.")
                if IceniDebug == True:
                    #Play movie1 in a window
                    OMX1 = subprocess.Popen(['omxplayer', '--loop', '--win', WinSize, '--layer', str(Layer), movie1],stdin=subprocess.PIPE)
                else:
                    #Play movie1 fullscreen
                    OMX1 = subprocess.Popen(['omxplayer', '--loop', '--layer', str(Layer), movie1],stdin=subprocess.PIPE)
                time.sleep(5)
                if OMX2_active == True: #shutdown movie2 if it is playing
                    OMX2.stdin.write('q')
                    OMX2.stdin.flush()
                    OMX2_active = False
                if OMX3_active == True: #shutdown movie3 if it is playing
                    OMX3.stdin.write('q')
                    OMX3.stdin.flush()
                    OMX3_active = False
                if OMX4_active == True: #shutdown movie4 if it is playing
                    OMX4.stdin.write('q')
                    OMX4.stdin.flush()
                    OMX4_active = False
                if OMX5_active == True: #shutdown movie5 if it is playing
                    OMX5.stdin.write('q')
                    OMX5.stdin.flush()
                    OMX5_active = False
                if OMX6_active == True: #shutdown movie6 if it is playing
                    OMX6.stdin.write('q')
                    OMX6.stdin.flush()
                    OMX6_active = False

        elif button2 == False: #ElseIf button2 is pressed...
            if OMX2_active == False: #And movie1 is not already running
                #Play movie2
                Layer = Layer + 1
                OMX2_active = True
                print("Button Pressed - Red")
                print("Flying to the Sunset planet.")
                if IceniDebug == True:
                    #Play movie2 in a window
                    OMX2 = subprocess.Popen(['omxplayer', '--loop', '--win', WinSize, '--layer', str(Layer), movie2],stdin=subprocess.PIPE)
                else:
                    #Play movie2 fullscreen
                    OMX2 = subprocess.Popen(['omxplayer', '--loop', '--layer', str(Layer), movie2],stdin=subprocess.PIPE)
                time.sleep(5)
                if OMX1_active == True: #shutdown movie1 if it is playing
                    OMX1.stdin.write('q')
                    OMX1.stdin.flush()
                    OMX1_active = False
                if OMX3_active == True: #shutdown movie3 if it is playing
                    OMX3.stdin.write('q')
                    OMX3.stdin.flush()
                    OMX3_active = False
                if OMX4_active == True: #shutdown movie4 if it is playing
                    OMX4.stdin.write('q')
                    OMX4.stdin.flush()
                    OMX4_active = False
                if OMX5_active == True: #shutdown movie5 if it is playing
                    OMX5.stdin.write('q')
                    OMX5.stdin.flush()
                    OMX5_active = False
                if OMX6_active == True: #shutdown movie6 if it is playing
                    OMX6.stdin.write('q')
                    OMX6.stdin.flush()
                    OMX6_active = False
                    
        elif button3 == False: #ElseIf button2 is pressed...
            if OMX3_active == False: #And movie1 is not already running
                #Play movie2
                Layer = Layer + 1
                OMX3_active = True
                print("Button Pressed - Blue")
                print("Flying to the Ocean planet.")
                if IceniDebug == True:
                    #Play movie5 in a window
                    OMX3 = subprocess.Popen(['omxplayer', '--loop', '--win', WinSize, '--layer', str(Layer), movie3],stdin=subprocess.PIPE) #Load the 1st video
                else:
                    #Play movie5 fullscreen
                    OMX3 = subprocess.Popen(['omxplayer', '--loop', '--layer', str(Layer), movie3],stdin=subprocess.PIPE) #Load the 1st video
                time.sleep(5)
                if OMX1_active == True: #shutdown movie1 if it is playing
                    OMX1.stdin.write('q')
                    OMX1.stdin.flush()
                    OMX1_active = False
                if OMX2_active == True: #shutdown movie2 if it is playing
                    OMX2.stdin.write('q')
                    OMX2.stdin.flush()
                    OMX2_active = False
                if OMX4_active == True: #shutdown movie4 if it is playing
                    OMX4.stdin.write('q')
                    OMX4.stdin.flush()
                    OMX4_active = False
                if OMX5_active == True: #shutdown movie5 if it is playing
                    OMX5.stdin.write('q')
                    OMX5.stdin.flush()
                    OMX5_active = False
                if OMX6_active == True: #shutdown movie6 if it is playing
                    OMX6.stdin.write('q')
                    OMX6.stdin.flush()
                    OMX6_active = False
                    
        elif button4 == False: #ElseIf button2 is pressed...
            if OMX4_active == False: #And movie1 is not already running
                #Play movie2
                Layer = Layer + 1
                OMX4_active = True
                print("Button Pressed - Green")
                print("Flying to the Cloud planet.")
                if IceniDebug == True:
                    #Play movie4 in a window
                    OMX4 = subprocess.Popen(['omxplayer', '--loop', '--win', WinSize, '--layer', str(Layer), movie4],stdin=subprocess.PIPE)
                else:
                    #Play movie5 fullscreen
                    OMX4 = subprocess.Popen(['omxplayer', '--loop', '--layer', str(Layer), movie4],stdin=subprocess.PIPE)
                time.sleep(5)
                if OMX1_active == True: #shutdown movie1 if it is playing
                    OMX1.stdin.write('q')
                    OMX1.stdin.flush()
                    OMX1_active = False
                if OMX2_active == True: #shutdown movie2 if it is playing
                    OMX2.stdin.write('q')
                    OMX2.stdin.flush()
                    OMX2_active = False
                if OMX3_active == True: #shutdown movie3 if it is playing
                    OMX3.stdin.write('q')
                    OMX3.stdin.flush()
                    OMX3_active = False
                if OMX5_active == True: #shutdown movie5 if it is playing
                    OMX5.stdin.write('q')
                    OMX5.stdin.flush()
                    OMX5_active = False
                if OMX6_active == True: #shutdown movie6 if it is playing
                    OMX6.stdin.write('q')
                    OMX6.stdin.flush()
                    OMX6_active = False
                    
        elif button5 == False: #ElseIf button2 is pressed...
            if OMX5_active == False: #And movie1 is not already running
                #Play movie5
                Layer = Layer + 1
                OMX5_active = True
                print("Button Pressed - Black")
                print("Returning to Orbit.")
                if IceniDebug == True:
                    #Play movie5 in a window
                    OMX5 = subprocess.Popen(['omxplayer', '--loop', '--win', WinSize, '--layer', str(Layer), movie5],stdin=subprocess.PIPE)
                else:
                    #Play movie5 fullscreen
                    OMX5 = subprocess.Popen(['omxplayer', '--loop', '--layer', str(Layer), movie5],stdin=subprocess.PIPE)
                time.sleep(5)
                if OMX1_active == True: #shutdown movie1 if it is playing
                    OMX1.stdin.write('q')
                    OMX1.stdin.flush()
                    OMX1_active = False
                if OMX2_active == True: #shutdown movie2 if it is playing
                    OMX2.stdin.write('q')
                    OMX2.stdin.flush()
                    OMX2_active = False
                if OMX3_active == True: #shutdown movie3 if it is playing
                    OMX3.stdin.write('q')
                    OMX3.stdin.flush()
                    OMX3_active = False
                if OMX4_active == True: #shutdown movie4 if it is playing
                    OMX4.stdin.write('q')
                    OMX4.stdin.flush()
                    OMX4_active = False
                if OMX6_active == True: #shutdown movie6 if it is playing
                    OMX6.stdin.write('q')
                    OMX6.stdin.flush()
                    OMX6_active = False
                    
        #If GPIO(24) is shorted to ground
        if button6 == False:
            if OMX6_active == False: #And movie6 is not already running
                #Play movie6
                Layer = Layer + 1
                OMX6_active = True
                print("Button Pressed - White")
                print("Spacestation Docking and Repairs.")
                if IceniDebug == True:
                    #Load video 6 in a window
                    OMX6 = subprocess.Popen(['omxplayer', '--loop', '--win', WinSize, '--layer', str(Layer), movie6],stdin=subprocess.PIPE) 
                else: 
                    #Load video6 fullscreen
                    OMX6 = subprocess.Popen(['omxplayer', '--loop', '--layer', str(Layer), movie6],stdin=subprocess.PIPE)
                time.sleep(5)
                if OMX1_active == True: #shutdown movie1 if it is playing
                    OMX1.stdin.write('q')
                    OMX1.stdin.flush()
                    OMX1_active = False
                if OMX2_active == True: #shutdown movie2 if it is playing
                    OMX2.stdin.write('q')
                    OMX2.stdin.flush()
                    OMX2_active = False
                if OMX3_active == True: #shutdown movie3 if it is playing
                    OMX3.stdin.write('q')
                    OMX3.stdin.flush()
                    OMX3_active = False
                if OMX4_active == True: #shutdown movie4 if it is playing
                    OMX4.stdin.write('q')
                    OMX4.stdin.flush()
                    OMX4_active = False
                if OMX5_active == True: #shutdown movie5 if it is playing
                    OMX5.stdin.write('q')
                    OMX5.stdin.flush()
                    OMX5_active = False

#Killing with a keyboard press.
except KeyboardInterrupt:
    print("Mission Aborted!")
    print("Enter desktop using:")
    print("sudo startx")
    os.system('killall omxplayer.bin')
    pass