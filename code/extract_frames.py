import sys
import numpy as np
import cv2
import os

options = {}
vidName = ''

for i in range(1, len(sys.argv)):
    arg = sys.argv[i]
    _arg = arg.split('=')
    opt = _arg[0][1:]
    
    if opt[0] == '-':
        opt = opt[1:]
    
    if opt == 'v' or opt == 'video':
        pathList = _arg[1].split('/')
        vidName = pathList[-1].split('.')[0]
        options['v'] = _arg[1]
    else:
        options[opt] = _arg[1]

if vidName == '':
    print("Please provide video file name by using -v=filename or -video=filename")
    quit()

if 'o' not in options.keys():
    print("Please provide frame output folder using -o=out")
    quit()

vidFile = options['v']
print("Video:", vidFile)

outFolder = options['o'] + "/" + vidName
print("Will print frames to", outFolder)

if not os.path.exists(outFolder):
    os.makedirs(outFolder)

cap = cv2.VideoCapture(vidFile)

frameCount = 0
ret, frame = cap.read()
while ret:
    
    #frame = cv2.normalize(frame, 0, 200, cv2.NORM_MINMAX);
    
    if cv2.waitKey(1) & 0xFF == ord('q') or not ret:
        break
    
    frameCount += 1
    cv2.imshow('frame', frame)
    frameName = outFolder + "/" + str(frameCount) + " " + "frame.jpg"
    cv2.imwrite(frameName, frame)
    ret, frame = cap.read()

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
