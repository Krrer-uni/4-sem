
function RSA_crt(x, p, q, dp, dq, qi)
    yp::BigInt = powermod(parse(BigInt, x),parse(BigInt,dp),parse(BigInt,p))
    yq::BigInt = powermod(parse(BigInt, x),parse(BigInt,dq),parse(BigInt,q))
    return mod(yp +(yp-yq)*parse(BigInt,qi)*parse(BigInt,q), parse(BigInt,q)*parse(BigInt,p))
end

println(RSA_crt(ARGS[1],ARGS[2],ARGS[3],ARGS[4],ARGS[5],ARGS[6]))