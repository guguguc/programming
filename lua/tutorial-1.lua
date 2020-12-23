-- basic type
tb = {["name"] = "sam", x = 1, 0; [30] = 10}
print(tb["name"], tb.x, tb[1], tb[30])

-- function
function is_alpha(ch)
    return ("a" <= ch and ch <= "z")
           or ("A" <= ch and ch <= "Z")
end

function is_digit(ch)
    return ch >= "0" and ch <= "9"
end

function count_word(filename)
    local fp = io.open(filename, "r")
    local cnt = 0
    local last_space = true
    local ch
    repeat
        ch = fp:read(1)
        if  ch == " " or ch == "    " or ch == "\n" then
            last_space = true
        else
            if last_space then
                last_space = false
                cnt = cnt + 1
            end
        end
    until not ch
    fp:close()
    return cnt
end

