#/bin/sh

# Ref: https://tldp.org/LDP/abs/html/string-manipulation.html

# Basic
# 1. String Length
# 2. Index
# 3. Substring exraction
# 4. Substring removal
# 5. Substring replacement

var="abcdefgchcde"
#    12345678

# =====================================================
# 1. String Length
# =====================================================
len=${#var}            #8
len=`expr length $len` #8

# =====================================================
# 2. Index
# =====================================================
# expr <target> <substr>
# Position in <target> of first char in <substr> that matches.
idx=`expr index "$var" def` #4

# =====================================================
# 3. Substring Extraction
# =====================================================
# 0-based indexing
# ${<var>:<start>}       # start > 0, beginning from left,  start -> end
# ${<var>:(<start>)}     # start < 0, beginning from right, start -> end
# ${<var>:<start>:<len>}
var1=${var:0} #abcdefgh
var2=${var:2:4}

# =====================================================
# 3. Substring Removal
# =====================================================
# forward removal
var3=${var#a*c}  # defgch : shortest match
var4=${var##a*c} # h      : longest  match
# backward removal
var5=${var%cde}  #  abcdefgch : shortest match
var5=${var%%cde}  # abcdefgch : longest  match

# =====================================================
# 4. Substring Replacement
# =====================================================
# 1. ${string/substring/replacement}  first match
# 2. ${string//substring/replacement} all match
# 3. ${string/#substring/replacement} front match
# 4. ${string/%substring/replacement} backend match
