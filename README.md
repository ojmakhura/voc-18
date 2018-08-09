# dataset
This project contains the object counting dataset. The videos directory
contains the videos used in testing. The truth directory contains the 
black and white frames for each video. The white dots on the video 
represents the location of the objects being counted. They are read by 
the vocount executable to for comparison with the counting algorithm. 

## code
extract_count.py - Read the truth count from binary images and save them
in an lmdb database.

extract_frames.py - Read a data video and extract the video frames. This
file relies on opncv to read the video file

lmdbtest.[c,cpp] - Samples of how to read the lmdb databases

## videos
Contains the video files for different object classes

## truth-binary
Contains the binary images for each frame in the video. It is first 
organised by the object classes and then each video is represented by
a directory that contains the binary files.

## truth-lmdb
LMDB database files organised by the object classes.
