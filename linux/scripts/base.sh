#!/usr/bin/sh

# use this to disable ctrl+s lock terminal[signaling senders to stop input]
# terminal driver responses fo locking scroll screen
# stty -ixon

fe()
{
	if [ -f $1 ]
	then
		echo "$1 file has already existed!"
	else
		echo "$1 file doesn't exist"
	fi
}

de()
{
	if [ -d $1 ]
	then
		echo "$1 dir has already existed!"
	else
		echo "$1 dir doesn't exist"
	fi
}

pskill()
{
	local pid
	# --invert-match
	pid=$(ps -ax | grep $1 | grep -v grep | awk '{ print $1 }')
	echo "kiling $1 (process $pd)..."
	kill -9 $pid
}

de $1
