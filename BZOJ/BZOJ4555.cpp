// TJOI 2016 & HEOI 2016
#include <cstdio>
#include <algorithm>

typedef long long LL;
typedef LL LLAr[(1 << 18) + 10];

const int MOD = 998244353;

int n;
LLAr fac, inv, f, g, G;

LL FastPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}
void DFT(LL ar[], int n0);

int main() {
	scanf("%d", &n);

	fac[0] = 1;
	for (LL i = 1; i <= n; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[n] = FastPow(fac[n]);
	for (LL i = n - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;
	for (LL i = 0; i <= n; i++) f[i] = i & 1 ? -inv[i] : inv[i];
	g[0] = 1, g[1] = n + 1;
	for (LL i = 2; i <= n; i++) {
		g[i] = (FastPow(i, n + 1) - 1) * FastPow(i - 1) % MOD * inv[i] % MOD;
	}

	int l = 1;
	for (; l <= n + n + 2; l <<= 1);
	G[0] = 1, G[1] = FastPow(3, (MOD - 1) / l);
	for (int i = 2; i < l; i++) G[i] = G[i - 1] * G[1] % MOD;
	DFT(f, l);
	DFT(g, l);
	for (int i = 0; i < l; i++) (f[i] *= g[i]) %= MOD;
	for (int i = 0; i < l; i++) f[i] = (f[i] + MOD) % MOD;
	G[0] = 1, G[1] = FastPow(G[1]);
	for (int i = 2; i < l; i++) G[i] = G[i - 1] * G[1] % MOD;
	DFT(f, l);
	int invn = FastPow(l);	
	for (int i = 0; i < l; i++) (f[i] *= invn) %= MOD;

	LL ans = 0;
	{
		LL pw = 1, fac = 1;
		for (int i = 0; i <= n; i++) {
			(ans += pw * fac % MOD * f[i] % MOD) %= MOD;
			(pw <<= 1) %= MOD;
			(fac *= (i + 1)) %= MOD;
		}
	}
	ans = (ans + MOD) % MOD;
	printf("%lld\n", ans);
	return 0;
}

void BitReverse(LL ar[], int len) {
	for (int i = 0, j = 0; i < len; i++) {
		if (i > j) std::swap(ar[i], ar[j]);
		for (int l = len >> 1; (j ^= l) < l; l >>= 1);
	}
}

void DFT(LL ar[], int len) {	
	BitReverse(ar, len);
	for (int i = 2; i <= len; i <<= 1) {
		int m = i >> 1;
		for (int j = 0; j < len; j += i) {
			for (int k = 0; k < m; k++) {
				LL tmp = ar[j + m + k] * G[len / i * k] % MOD;
				ar[j + m + k] = (ar[j + k] - tmp) % MOD;
				(ar[j + k] += tmp) %= MOD;
			}
		}
	}
}
