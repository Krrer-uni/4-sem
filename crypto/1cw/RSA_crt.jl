
function RSA_crt(x, p, q, dp, dq, qi)
    yp::BigInt = powermod(x,dp,p)
    yq::BigInt = powermod(x,dq,q)
    return mod(yq +(yp-yq)*qi*q, p*q)
end

argsint = [parse(BigInt,x) for x in ARGS]
println(argsint)

# println(RSA_crt(ARGS[1],ARGS[2],ARGS[3],ARGS[4],ARGS[5],ARGS[6]))
println(RSA_crt(argsint[1],argsint[2],argsint[3],argsint[4],argsint[5],argsint[6]))