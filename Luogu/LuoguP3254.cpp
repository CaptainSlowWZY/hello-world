// Luogu P3254
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int MAXV = 430, MAXE = 41000, INF = 0x7f7f7f7f;

struct Edge {
	int to, capt, next;
} E[MAXE << 1];

typedef int IntAr[MAXV];

int M, N, S, T, sumc, tote = 1;
IntAr last, cur, D; 

inline void add_edge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
}
bool max_flow();

int main() {
	scanf("%d%d", &M, &N);
	T = (S = M + N) + 1;
	for (int i = 0, num; i < M; i++) {
		scanf("%d", &num);
		sumc += num;
		add_edge(S, i, num);
	}
	for (int i = 0, num; i < N; i++) {
		scanf("%d", &num);
		add_edge(M + i, T, num);
		for (int j = 0; j < M; j++) add_edge(j, M + i, 1);
	}

	int ans = max_flow();
	printf("%d\n", ans);
	if (ans) {
		for (int i = 0; i < M; i++) {
			forto(i)
				if (!E[e].capt && E[e ^ 1].capt) printf("%d ", v - M + 1);
			putchar('\n');
		}
	}

	return 0;
}

bool build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	for (D[S] = 1, que.push(S); !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u)
			if (!D[v] && E[e].capt > 0) D[v] = D[u] + 1, que.push(v);
	}
	return D[T];
}

int dinic(int u, int flow) {
	if (u == T) return flow;
	int rem = flow;
	for (int &e = cur[u], v = E[e].to; e && rem > 0; v = E[e = E[e].next].to)
		if (D[v] == D[u] + 1 && E[e].capt > 0) {
			int delta = dinic(v, std::min(rem, E[e].capt));
			E[e].capt -= delta, E[e ^ 1].capt += delta, rem -= delta;
		}
	return flow - rem;
}

bool max_flow() {
	int sumf = 0;
	while (build()) {
		for (int i = 0; i <= T; i++) cur[i] = last[i];
		sumf += dinic(S, INF);
	}
	return sumf == sumc;
}
