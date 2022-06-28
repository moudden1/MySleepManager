#! /bin/sh

# echo $1

# execute python script
python3 quickstart.py

sleep 2

# send signal to PID
kill -SIGUSR1 $1
