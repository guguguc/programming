-------------------------------------------------------------
-- 1. Variables and flow control
-------------------------------------------------------------

-- all numbers are double
num = 1

-- Immutable strings
s = 'hello'
t = "hello"
u = [[ Double brackets
       start and end
       multi-line strings.]]
t = nil

-- flow control
while num < 50 do
    num = num + 1
end

if num > 10 then
    print('over 10')
elseif s ~= 'hello' then
    io.write('not over 10')
else
    thisIsGlobal = 5
    local line = io.read()
    -- use .. to concatenate str
    print('winter is comming, ' .. line)
end

-- Undefined var return nil
foo = anUnkownVar

aBoolValue = false

-- 0 and '' are true
-- only nil and false are false
if not aBoolValue then print('not false') end

-- 'or' and 'and' are short-circuited
-- a ? b : c
ans = aBoolValue and 'yes' or 'no'

-- range for, include start and end
sum = 0
for i = 1, 100 do
    sum = sum + i
end

sum = 0
for j = 100, 1, -1 do sum = sum + j end

repeat
    print('ok')
    num = num - 1
until num == 0


-------------------------------------------------------------
-- 2. Function
-------------------------------------------------------------

function fib(n)
    if n < 2 then return n end
    return fib(n-1) + fib(n-2)
end

-- Closures and anonymous function
-- adder = functool.partical(add, x)
function adder(x)
    return function (y) return x + y end
end

x, y, z = 1, 2, 3, 5

function bar(a, b, c)
    print(a, b, c)
    return 1, 1, 2, 3, 5, 8
end

-- print "hello nil nil"
-- x and y both are 1
x, y = bar("hello")

-- functions are first-class
function f(x) return x * x end
f = function (x) return x * x end





