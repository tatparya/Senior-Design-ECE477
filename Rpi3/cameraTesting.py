#! /usr/bin/env python3.4

from picamera import PiCamera
from picamera.array import PiRGBArray
from time import sleep
import numpy as np
import cv2
from cv2 import *
import imutils
from pyimagesearch.colorlabeler import ColorLabeler
from scipy.spatial import distance as dist
from collections import OrderedDict
import argparse
import cv2.cv
from PIL import Image
import numpy
import json
import os
import sys
import time
import serial
import RPi.GPIO as GPIO


def cameraFunc():
    cam = cv2.VideoCapture(0)

    #cam = PiCamera()
    #cam.resolution(640, 480)
    #cam.framerate = 32
    #rawCapture = PiRGBArray(cam, size=(640, 480))

    cv2.namedWindow('RubeCube', cv2.WINDOW_AUTOSIZE)

    img_counter=0

    while True:
    #for frame in cam.capture_continuous(rawCapture, format="bgr", use_video_port=True):
        ret, frame = cam.read()
        centerX = int(cam.get(3)) / 2
        centerY = int(cam.get(4)) / 2

        cubeSize = 100
        spacing = 40

        
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2  * 3 + spacing ), centerY - ( cubeSize / 2 * 3 + spacing ) ), ( centerX - ( cubeSize / 2 + spacing ), centerY - ( cubeSize / 2 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2 ), centerY - ( cubeSize / 2 * 3 + spacing ) ), ( centerX + ( cubeSize / 2 ), centerY - ( cubeSize / 2 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX + ( cubeSize / 2 + spacing ), centerY - ( cubeSize / 2 * 3 + spacing ) ), ( centerX + ( cubeSize / 2 * 3 + spacing ), centerY - ( cubeSize / 2 + spacing ) ), ( 0, 255, 0 ), 3 )

        cv2.rectangle( frame, ( centerX - ( cubeSize / 2  * 3 + spacing ), centerY - ( cubeSize / 2 ) ), ( centerX - ( cubeSize / 2 + spacing ), centerY + ( cubeSize / 2 ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2 ), centerY - ( cubeSize / 2 ) ), ( centerX + ( cubeSize / 2 ), centerY + ( cubeSize / 2 ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX + ( cubeSize / 2 + spacing ), centerY - ( cubeSize / 2 ) ), ( centerX + ( cubeSize / 2 * 3 + spacing ), centerY + ( cubeSize / 2 ) ), ( 0, 255, 0 ), 3 )

        cv2.rectangle( frame, ( centerX - ( cubeSize / 2  * 3 + spacing ), centerY + ( cubeSize / 2 + spacing ) ), ( centerX - ( cubeSize / 2 + spacing ), centerY + ( cubeSize / 2 * 3 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2 ), centerY + ( cubeSize / 2 + spacing ) ), ( centerX + ( cubeSize / 2 ), centerY + ( cubeSize / 2 * 3 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX + ( cubeSize / 2 + spacing ), centerY + ( cubeSize / 2 + spacing ) ), ( centerX + ( cubeSize / 2 * 3 + spacing ), centerY + ( cubeSize / 2 * 3 + spacing ) ), ( 0, 255, 0 ), 3 )


        cv2.imshow('RubeCube', frame)
        if not ret:
            break
        k = cv2.waitKey(1) & 0xFF

        if k%256 == 27:
            print("Escape Key Hit, Closing!")
            break
        elif k%256 == 32:
            img_name = "cube_face_new_new_{}.jpg".format(img_counter)
            cv2.imwrite(img_name, frame)
            print("{} written!!!".format(img_name))
            img_counter += 1
    cam.release()
    return centerX, centerY, cubeSize, spacing
    cv2.destroyAllWindows()

def cdetect2(centerX, centerY, cnt, total_list_nums):
    image = cv2.imread("cube_face_new_new_{}.jpg".format(cnt))

    #values = [image[x-25:x+25, y-165:y-115], image[x-165:x-115, y-165:y-115], image[x+115:x+165, y-165:y-115], image[x-25:x+25, y-25:y+25], image[x-165:x-115, y-25:y+25], image[x+115:x+165, y-25:y+25], image[x-25:x+25, y+115:y+165], image[x-165:x-115, y+115:y+165], image[x+115:x+165, y+115:y+165]]
    cubeSize = 100
    spacing = 40
    #values = [image[x-25:x+25, y-165:y-115], image[x-165:x-115, y-165:y-115], image[x+115:x+165, y-165:y-115], image[x-25:x+25, y-25:y+25], image[x-165:x-115, y-25:y+25], image[x+115:x+165, y-25:y+25], image[x-25:x+25, y+115:y+165], image[x-165:x-115, y+115:y+165], image[x+115:x+165, y+115:y+165]]
    values = [image[(centerY - ( cubeSize / 2 * 3 + spacing )):(centerY - ( cubeSize / 2 + spacing )), (centerX - ( cubeSize / 2  * 3 + spacing )):(centerX - ( cubeSize / 2 + spacing ))],
              image[(centerY - ( cubeSize / 2 * 3 + spacing )):(centerY - ( cubeSize / 2 + spacing )), (centerX - ( cubeSize / 2 )):(centerX + ( cubeSize / 2 ))],
              image[(centerY - ( cubeSize / 2 * 3 + spacing )):(centerY - ( cubeSize / 2 + spacing )), (centerX + ( cubeSize / 2 + spacing )):(centerX + ( cubeSize / 2 * 3 + spacing ))],
              image[(centerY - ( cubeSize / 2 )):(centerY + ( cubeSize / 2 )), (centerX - ( cubeSize / 2  * 3 + spacing )):(centerX - ( cubeSize / 2 + spacing ))],
              image[(centerY - ( cubeSize / 2 )):(centerY + ( cubeSize / 2 )), (centerX - ( cubeSize / 2 )):(centerX + ( cubeSize / 2 ))],
              image[(centerY - ( cubeSize / 2 )):(centerY + ( cubeSize / 2 )), (centerX + ( cubeSize / 2 + spacing )):(centerX + ( cubeSize / 2 * 3 + spacing ))],
              image[(centerY + ( cubeSize / 2 + spacing )):(centerY + ( cubeSize / 2 * 3 + spacing )), (centerX - ( cubeSize / 2  * 3 + spacing )):(centerX - ( cubeSize / 2 + spacing ))],
              image[(centerY + ( cubeSize / 2 + spacing )):(centerY + ( cubeSize / 2 * 3 + spacing )), (centerX - ( cubeSize / 2 )):(centerX + ( cubeSize / 2 ))],
              image[(centerY + ( cubeSize / 2 + spacing )):(centerY + ( cubeSize / 2 * 3 + spacing )), (centerX + ( cubeSize / 2 + spacing )):(centerX + ( cubeSize / 2 * 3 + spacing ))]]

    outputNamesArray = [[], [], []]
    list_nums = [[], [], []]
    count = 0

    cv2.namedWindow('RubeCube', cv2.WINDOW_AUTOSIZE)


    for val in values:
        
        image = val
        resized = imutils.resize(image, width=300)
        ratio = image.shape[0] / float(resized.shape[0])

        #cv2.imshow("Image", image)
        #cv2.waitKey(0)

        blurred = cv2.GaussianBlur(resized, (5, 5), 0)
        gray = cv2.cvtColor(blurred, cv2.COLOR_BGR2GRAY)
        lab = cv2.cvtColor(blurred, cv2.COLOR_BGR2LAB)
        thresh = cv2.threshold(gray, 60, 255, cv2.THRESH_BINARY)[1]

        cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[0] if imutils.is_cv2() else cnts[1]

        #cv2.drawContours(image, cnts, -1, (0, 255, 0), 3)
        #print cnts

        cl = ColorLabeler()
        #c = cnts
        c = cnts[0]
        #for c in cnts:
        M = cv2.moments(c)
        if M["m00"] != 0:
            cX = int((M["m10"] / M["m00"]) * ratio)
            cY = int((M["m01"] / M["m00"]) * ratio)
        else:
            cX = int((M["m10"] / 1) * ratio)
            cY = int((M["m01"] / 1) * ratio)

        color, mean, minDist = cl.label(lab, c)

        #print "MEAN : " 
        #print mean
        #print "Orange : " 
        #print cl.lab[1]
        #print "Red : " 
        #print cl.lab[2]
        #print "Min Dist : "
        #print minDist
        #print color
        #print type(color)

        if color == "red" and mean[0] > 105:
            color = "orange"

        if color == "orange" and mean[0] > 160:
            color = "yellow"

        if color == "white" and mean[0] <= 175:
            color = "blue"

        #if color == "green" and mean[0] >= 175:
        #    color = "yellow"

        #if color == "green":
        #    print "MEAN : " 
        #    print mean
        #    print "Green : " 
        #    print cl.lab[0]
        #    print "Yellow : " 
        #    print cl.lab[5]
        #    print "Min Dist : "
        #    print minDist
        
        #if color == "orange":
        #    print "MEAN : " 
        #    print mean
        #    print "Orange : " 
        #    print cl.lab[1]
        #    print "Yellow : " 
        #    print cl.lab[5]
        #    print "Min Dist : "
        #    print minDist
        
        c = c.astype("float")
        c *= ratio
        c = c.astype("int")
        text = "{}".format(color)

        #cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
        cv2.putText(image, text, (10, 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)

        #cv2.imshow("Image", image)
        #cv2.waitKey(0)

        outputNamesArray[count/3].append(text)

        if text == "blue":
            list_nums[count/3].append(0)
        elif text == "orange":
            list_nums[count/3].append(1)
        elif text == "green":
            list_nums[count/3].append(2)
        elif text == "red":
            list_nums[count/3].append(3)
        elif text == "white":
            list_nums[count/3].append(4)
        elif text == "yellow":
            list_nums[count/3].append(5)
        
        count += 1
        #print count

    #cv2.imshow("RubeCube",im)
    #cv2.imwrite("extracted.jpg", im)
    #cv2.waitKey()
    cv2.destroyAllWindows()

    print ( outputNamesArray)

    total_list_nums.append(list_nums)
    
    return total_list_nums
def callcdetect2(x, y):
    total_list_nums = []
    cnt = 0
    total_list_nums = cdetect2(x, y, cnt, total_list_nums)
    cnt = 1
    total_list_nums = cdetect2(x, y, cnt, total_list_nums)
    cnt = 2
    total_list_nums = cdetect2(x, y, cnt, total_list_nums)
    cnt = 3
    total_list_nums = cdetect2(x, y, cnt, total_list_nums)
    cnt = 4
    total_list_nums = cdetect2(x, y, cnt, total_list_nums)
    cnt = 5
    total_list_nums = cdetect2(x, y, cnt, total_list_nums)

    f = open('colorsOutput1.txt', 'w')
    
    for item in total_list_nums:
        f.write(str(item) + "\n")

def godOrNot(final_nums_list):
    ser = serial.Serial(port='/dev/ttyS0',baudrate = 115200,parity=serial.PARITY_NONE,stopbits=serial.STOPBITS_ONE,bytesize=serial.EIGHTBITS,timeout=0)

    motor_array = np.asarray(final_nums_list) #np.random.randint(1,7, size=(6, 3, 3))
    print(motor_array[:][:][:])
    flat_array = motor_array.flatten()
    count=0
    time.sleep(1)
    ser.write(str(0).encode())
    time.sleep(1)
    time.sleep(1)
    for i in flat_array:
        #print (i)
        count=count+1
        ser.write(str(i).encode())
        time.sleep(1)
    ser.close()

   
#x, y, cubeSize, spacing = cameraCalib()
#b_x1, b_x2, b_y1, b_y2, b_z1, b_z2, o_x1, o_x2, o_y1, o_y2, o_z1, o_z2, g_x1, g_x2, g_y1, g_y2, g_z1, g_z2, r_x1, r_x2, r_y1, r_y2, r_z1, r_z2, w_x1, w_x2, w_y1, w_y2, w_z1, w_z2, y_x1, y_x2, y_y1, y_y2, y_z1, y_z2 = callCalib(x, y)
#print b_x1, b_x2, b_y1, b_y2, b_z1, b_z2, o_x1, o_x2, o_y1, o_y2, o_z1, o_z2, g_x1, g_x2, g_y1, g_y2, g_z1, g_z2, r_x1, r_x2, r_y1, r_y2, r_z1, r_z2, w_x1, w_x2, w_y1, w_y2, w_z1, w_z2, y_x1, y_x2, y_y1, y_y2, y_z1, y_z2

#cdetectCalib(x, y)

#b_x, b_y, b_z, o_x, o_y, o_z, g_x, g_y, g_z, r_x, r_y, r_z, w_x, w_y, w_z, y_x, y_y, y_z = callCalib_new(x, y, cubeSize, spacing)
#print b_x, b_y, b_z, o_x, o_y, o_z, g_x, g_y, g_z, r_x, r_y, r_z, w_x, w_y, w_z, y_x, y_y, y_z


GPIO.setmode(GPIO.BCM)

GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)

god = GPIO.input(18)

#while True:
if (god):
    print("GOD MODE ON !!!")
    print (god)
    x, y, cubeSize, spacing = cameraFunc()
    callcdetect2(x, y)

    print ("Please ensure the color output, and edit as necessary.")

    done = raw_input('Enter 1 when you are done: ')
    time.sleep(0.3)

    
            
else:
    print("GOD MODE OFF :( ")
    print (god)
    x, y, cubeSize, spacing = cameraFunc()
    callcdetect2(x, y)

    print ("Please ensure the color output, and edit as necessary.")

    done = raw_input('Enter 1 when you are done: ')

    f1 = open('colorsOutput1.txt', 'r')

    final_nums_list = []
    for line in f1:
        f_nums_list = [[], [], []]
        cnt = 0
        for c in line:
            if c >= '0' and c <= '5':
                c_i = int(c)
                f_nums_list[cnt/3].append(c_i)
                cnt += 1
        final_nums_list.append(f_nums_list)

    print (final_nums_list)
            
    godOrNot(final_nums_list)
    time.sleep(0.3)

