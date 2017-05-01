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
    #   Init camera
    cam = cv2.VideoCapture(0)
    cv2.namedWindow('RubeCube', cv2.WINDOW_AUTOSIZE)

    img_counter=0

    #   Camera feed
    while True:
        #   Get camera frame
        ret, frame = cam.read()

        #   Set centers
        centerX = int(cam.get(3)) / 2
        centerY = int(cam.get(4)) / 2

        cubeSize = 100
        spacing = 40

        #   Set green boxes
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2  * 3 + spacing ), centerY - ( cubeSize / 2 * 3 + spacing ) ), ( centerX - ( cubeSize / 2 + spacing ), centerY - ( cubeSize / 2 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2 ), centerY - ( cubeSize / 2 * 3 + spacing ) ), ( centerX + ( cubeSize / 2 ), centerY - ( cubeSize / 2 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX + ( cubeSize / 2 + spacing ), centerY - ( cubeSize / 2 * 3 + spacing ) ), ( centerX + ( cubeSize / 2 * 3 + spacing ), centerY - ( cubeSize / 2 + spacing ) ), ( 0, 255, 0 ), 3 )

        cv2.rectangle( frame, ( centerX - ( cubeSize / 2  * 3 + spacing ), centerY - ( cubeSize / 2 ) ), ( centerX - ( cubeSize / 2 + spacing ), centerY + ( cubeSize / 2 ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2 ), centerY - ( cubeSize / 2 ) ), ( centerX + ( cubeSize / 2 ), centerY + ( cubeSize / 2 ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX + ( cubeSize / 2 + spacing ), centerY - ( cubeSize / 2 ) ), ( centerX + ( cubeSize / 2 * 3 + spacing ), centerY + ( cubeSize / 2 ) ), ( 0, 255, 0 ), 3 )

        cv2.rectangle( frame, ( centerX - ( cubeSize / 2  * 3 + spacing ), centerY + ( cubeSize / 2 + spacing ) ), ( centerX - ( cubeSize / 2 + spacing ), centerY + ( cubeSize / 2 * 3 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX - ( cubeSize / 2 ), centerY + ( cubeSize / 2 + spacing ) ), ( centerX + ( cubeSize / 2 ), centerY + ( cubeSize / 2 * 3 + spacing ) ), ( 0, 255, 0 ), 3 )
        cv2.rectangle( frame, ( centerX + ( cubeSize / 2 + spacing ), centerY + ( cubeSize / 2 + spacing ) ), ( centerX + ( cubeSize / 2 * 3 + spacing ), centerY + ( cubeSize / 2 * 3 + spacing ) ), ( 0, 255, 0 ), 3 )

        #   Show camera feed
        cv2.imshow('RubeCube', frame)

        #   Exit sequence
        if not ret:
            break
        
        k = cv2.waitKey(1) & 0xFF

        #   Exit on escape key
        if k%256 == 27:
            print("Escape Key Hit, Closing!")
            break
        #   Take picture on space key
        elif k%256 == 32:
            img_name = "cube_face_new_new_{}.jpg".format(img_counter)
            cv2.imwrite(img_name, frame)
            print("{} written!!!".format(img_name))
            img_counter += 1

    #   Close camera and windows
    cam.release()
    return centerX, centerY, cubeSize, spacing
    cv2.destroyAllWindows()

def colorDetector(centerX, centerY, cnt, total_list_nums):
    image = cv2.imread("cube_face_new_new_{}.jpg".format(cnt))
    cubeSize = 100
    spacing = 40
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
    
def main():
    cameraFunc()

if __name__ == "__main__":
    main()
