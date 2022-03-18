using Printf

k = [40, 56, 90, 128, 256]

function t(k) 
    return (BigInt)(2^k / 10^6)
end

for n in k
    @printf("%d %d\n",n, t(n))
end