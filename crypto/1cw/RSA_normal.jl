using Statistics


function RSA(x, N, e)
    return powermod(x,e,N)
end

argsAsInt = [parse(BigInt,x) for x in ARGS]

println(RSA(argsAsInt[1], argsAsInt[2],argsAsInt[3]))