#/usr/bin/sh

# grep --context=3 -r --line-number "hello$" ./
# grep -r --line-number "hello$" ./
grep -r --line-number "^hello" ./
