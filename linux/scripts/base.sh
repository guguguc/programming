#!/usr/bin/sh

pskill()
{
  local pid
  # --invert-match
  pid=$(ps -ax | grep $1 | grep -v grep | awk '{ print $1 }')
  echo "kiling $1 (process $pd)..."
  kill -9 $pid
}

pskill $1
