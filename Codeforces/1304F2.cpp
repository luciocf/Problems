// Codeforces 1304F2 - Animal Observation (hard version)
// Lúcio Cardoso

#include <bits/stdc++.h>

#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

const int maxn = 55;
const int maxm = 2e4+10;

struct Maxqueue
{
	deque<pii> dq;
	int l, r;

	void init(void)
	{
		dq.clear();
		l = r = 0;
	}

	void push(int x)
	{
		while (dq.size() && dq.back().ff <= x)
			dq.pop_back();

		dq.push_back({x, r++});
	}

	void pop(void)
	{
		if (dq.size() && dq.front().ss == l)
			dq.pop_front();

		++l;
	}

	int mx(void)
	{
		return dq.front().ff;
	}
};

int n, m, k;

int a[maxn][maxm];
int soma[maxn][maxm];

int dp[maxn][maxm];
int pref[maxn][maxm], suf[maxn][maxm];

int main(void)
{
	scanf("%d %d %d", &n, &m, &k);

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);

			soma[i][j] = soma[i][j-1]+a[i][j];
		}
	}

	for (int i = 1; i <= m; i++)
		pref[n+1][i] = max(pref[n+1][i-1], soma[n][i]-soma[n][max(0, i-k)]);
	for (int i = m; i >= 1; i--)
		suf[n+1][i] = max(suf[n+1][i+1], soma[n][min(m, i+k-1)]-soma[n][i-1]);

	for (int i = n; i >= 1; i--)
	{
		Maxqueue mq1, mq2;

		mq1.init(); mq2.init();

		for (int j = 1; j <= k; j++)
		{
			int a = (j+k-1 > m ? 0 : soma[i][j+k-1]);
			int b = soma[i+1][min(m, j+k-1)]-soma[i+1][j-1];

			mq1.push(a + b + dp[i+1][j]);
		}

		for (int j = 1; j <= k; j++)
		{
			int a = (j-k+1 < 1 ? 0 : -soma[i][j-k]);
			int b = soma[i+1][j]-soma[i+1][max(0, j-k)];

			mq2.push(a + b + dp[i+1][max(1, j-k+1)]);
		}

		for (int j = 1; j <= m; j++)
		{
			dp[i][j] = max(pref[i+1][j-1], suf[i+1][j+k]);

			if (j+k-1 > m)
				dp[i][j] = max(dp[i][j], mq1.mx());
			else
				dp[i][j] = max(dp[i][j], mq1.mx() - soma[i][j+k-1]);
			
			dp[i][j] = max(dp[i][j], mq2.mx() + soma[i][j-1]);

			int l = j+k;

			if (l <= m)
			{
				int a = (l+k-1 > m ? 0 : soma[i][l+k-1]);
				int b = soma[i+1][min(m, l+k-1)]-soma[i+1][l-1];

				mq1.push(a + b + dp[i+1][l]);

				a = (l-k+1 < 1 ? 0 : -soma[i][l-k]);
				b = soma[i+1][l]-soma[i+1][max(0, l-k)];

				mq2.push(a + b + dp[i+1][max(1, l-k+1)]);
			}

			mq1.pop(); mq2.pop();
		}

		for (int j = 1; j <= m; j++)
		{
			int a = soma[i][j] - soma[i][max(0, j-k)];
			int b = soma[i-1][j] - soma[i-1][max(0, j-k)];

			pref[i][j] = max(pref[i][j-1], dp[i][max(1, j-k+1)] + a + b);
		}

		for (int j = m; j >= 1; j--)
		{
			int a = soma[i][min(m, j+k-1)] - soma[i][j-1];
			int b = soma[i-1][min(m, j+k-1)] - soma[i-1][j-1];

			suf[i][j] = max(suf[i][j+1], dp[i][j] + a + b);
		}
	}

	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		int a = soma[1][min(m, i+k-1)]-soma[1][i-1];
		int b = soma[2][min(m, i+k-1)]-soma[2][i-1];

		ans = max(ans, dp[2][i] + a + b);
	}

	printf("%d\n", ans);
}
