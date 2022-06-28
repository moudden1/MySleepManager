#! /bin/sh

# echo $1

# execute python script
python3 quickstart.py

# send signal to PID
kill -SIGUSR1 $1
