using Statistics
using Base64
using BitConverter
P = 0
Q = 0
DP = 0
DQ = 0
QI = 0

function pad(string)
    e = replace(replace(string,"-" => "+"),"_"=>"/")
    char_diff = mod(4 - mod(length(e),4),4)
    for i = 1:char_diff
        e = e * "="
    end
    return e
end

function RSA_crt(x, p, q, dp, dq, qi)
    yp::BigInt = powermod(x,dp,p)
    yq::BigInt = powermod(x,dq,q)
    return mod(yq +(yp-yq)*qi*q, p*q)
end

io = open(ARGS[2], "r") do io
    lines = readlines(io) 
    words = [split(line,": ") for line in lines]
    
    global P = to_big(base64decode(pad(chop(words[6][2], head = 1, tail = 2))))
    global Q = to_big(base64decode(pad(chop(words[7][2], head = 1, tail = 2))))
    global DP = to_big(base64decode(pad(chop(words[8][2], head = 1, tail = 2))))
    global DQ = to_big(base64decode(pad(chop(words[9][2], head = 1, tail = 2))))
    global QI = to_big(base64decode(pad(chop(words[10][2], head = 1, tail = 2))))
end


println(RSA_crt(parse(BigInt, ARGS[1]),P,Q,DP,DQ,QI))