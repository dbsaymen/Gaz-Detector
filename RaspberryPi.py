#!/usr/bin/env python
import RPi.GPIO as GPIO
import time
import json
import urllib3
import smtplib

Buzzer = 11    # pin11



def setup(pin):
    global BuzzerPin
    BuzzerPin = pin
    GPIO.setmode(GPIO.BOARD)       
    GPIO.setup(BuzzerPin, GPIO.OUT)
    GPIO.output(BuzzerPin, GPIO.HIGH)

def on():
    GPIO.output(BuzzerPin, GPIO.HIGH)

def off():
    GPIO.output(BuzzerPin, GPIO.LOW)

def beep(x):
    on()
    time.sleep(x)
    off()
    time.sleep(x)

def destroy():
    GPIO.output(BuzzerPin, GPIO.HIGH)
    GPIO.cleanup()
   
if __name__ == '__main__':     
    setup(Buzzer)
    http =urllib3.PoolManager()
    url="http://192.168.10.127/"
    off()
    try:
        while(True):
            resp= http.request("GET", url)
            time.sleep(0.5)
            data=resp.data
            json_data=json.loads(data.decode("utf-8"))
            print(json_data)
            floatval= float(json_data["data"])
            print(floatval)
            if (floatval>1.9):
                on()
              
            else:
               off()
            time.sleep(2)
    except KeyboardInterrupt: 
        destroy()



