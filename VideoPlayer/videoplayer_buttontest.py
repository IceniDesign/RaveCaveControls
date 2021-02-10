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
GPIO.setup(17, GPIO.IN, pull_up_down=GPIO.PUD_UP) #YELLOW #1
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP) #RED #2
GPIO.setup(24, GPIO.IN, pull_up_down=GPIO.PUD_UP) #WHITE #Quit
GPIO.setup(27, GPIO.IN, pull_up_down=GPIO.PUD_UP) #BLUE #3
GPIO.setup(22, GPIO.IN, pull_up_down=GPIO.PUD_UP) #GREEN #4
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP) #BLACK #5
     
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
        print("Yellow")
    elif button2 == False: #ElseIf button2 is pressed...   
        print("Red")
    elif button3 == False: #ElseIf button2 is pressed...
        print("Blue")
    elif button4 == False: #ElseIf button2 is pressed...  
        print("Green")    
    elif button5 == False: #ElseIf button2 is pressed...
        print("Black")
    elif button6 == False:
        print("White")

