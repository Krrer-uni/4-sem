
using Statistics
using Base64
using BitConverter


function pad(string)
    e = replace(replace(string,"-" => "+"),"_"=>"/")
    char_diff = mod(4 - mod(length(e),4),4)
    for i = 1:char_diff
        e = e * "="
    end
    return e
end

function RSA(x, N, e)
    return powermod(x,e,N)
end


n = 0
e = 0

io = open(ARGS[2], "r") do io
    lines = readlines(io) 
    words = [split(line,": ") for line in lines]
    
    n = chop(words[3][2], head = 1, tail = 2)
    e = chop(words[4][2], head = 1, tail = 2)
    n = pad(n)
    e = pad(e)
    global e = to_big(base64decode(e))
    global n = to_big(base64decode(n))
end

println(RSA(parse(BigInt,ARGS[1]), n ,e))