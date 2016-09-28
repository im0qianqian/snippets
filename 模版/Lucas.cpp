typedef __int64 LL;

LL exp_mod(LL a, LL b, LL p)
{
    LL res = 1;
    while(b != 0)
    {
        if(b&1) res = (res * a) % p;
        a = (a*a) % p;
        b >>= 1;
    }
    return res;
}

LL Comb(LL a, LL b, LL p)
{
    if(a < b)return 0;
    if(a == b)return 1;
    if(b > a - b)b = a - b;

    LL ans = 1, ca = 1, cb = 1;
    for(LL i = 0; i < b; ++i)
    {
        ca = (ca * (a - i))%p;
        cb = (cb * (b - i))%p;
    }
    ans = (ca*exp_mod(cb, p - 2, p)) % p;
    return ans;
}

LL Lucas(int n, int m, int p)
{
    LL ans = 1;

    while(n&&m&&ans)
    {
        ans = (ans*Comb(n%p, m%p, p)) % p;
        n /= p;
        m /= p;
    }
    return ans;
}
