#!/bin/bash
#
# Use this shell script to compile (if necessary) your code and then execute it. Below is an example of what might be found in this file if your program was written in Python
#
#python ./src/sessionization.py ./input/log.csv ./input/inactivity_period.txt ./output/sessionization.txt
chmod a+x /home/q/insight_project/src/insight2.cpp
chmod a+x /home/q/insight_project/output/
chmod a+x /home/q/insight_project/insight_testsuite/temp/
cd "/home/q/insight_project/src/" && g++ insight2.cpp -o insight2 && "/home/q/insight_project/src/"insight2
