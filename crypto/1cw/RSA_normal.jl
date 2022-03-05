using Statistics

function RSA(x, N, e)
    return powermod(parse(BigInt, x),parse(BigInt,e),parse(BigInt,N))
end


function RSA_crt(x, p, q, dp, dq, qi)
    yp::BigInt = powermod(parse(BigInt, x),parse(BigInt,dp),parse(BigInt,p))
    yq::BigInt = powermod(parse(BigInt, x),parse(BigInt,dq),parse(BigInt,q))
    return yp +(yp-yq)*qi*q
end


println(RSA(ARGS[1], ARGS[2],ARGS[3]))