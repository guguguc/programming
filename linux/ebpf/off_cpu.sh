#/usr/bin/bash

# for ((; ; ))
# do
    # pid=`pidof a.out`
pid=$1
# if [ "$pid" != "" ]
#then
/usr/share/bcc/tools/cpudist -O -p $pid
#    break
#fi
# done
