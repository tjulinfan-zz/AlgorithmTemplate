//用法 求a关于b的逆元——x
long long extend_gcd(long long a, long long b)
{
    if (b == 0)
    {
        x = 1; y = 0;
        return a;
    }
    long long gcd = extend_gcd(b, a % b);
    long long t = x;
    x = y; y = t - a / b * y;
    return gcd;
}
