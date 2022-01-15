#!/bin/sh

function r1() {
    cd /tmp
    ls -0 2>&1 2>/tmp/err2.log
}

r1
