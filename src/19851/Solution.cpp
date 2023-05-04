#include <bits/stdc++.h>
using namespace std;

typedef struct Node
{
    int n, mx, mn, lazy;
}Node;

vector<Node> v(4040404);
string st;

Node merge(Node& l, Node& r)
{
    return {l.n + r.n, max(l.mx, l.n + r.mx), min(l.mn, l.n + r.mn), 0};
}

void init(int s, int e, int i)
{
    if(s == e)
    {
        if(st[s-1] == '(')
        {
            v[i].n = v[i].mx = v[i].mn = 1;
        }
        else
        {
            v[i].n = v[i].mx = v[i].mn = -1;
        }
        v[i].lazy = 0;
        return;
    }
    int m = (s+e) >> 1;
    init(s, m, i*2);
    init(m+1, e, i*2+1);
    v[i] = merge(v[i*2], v[i*2+1]);
}

void lp(int s, int e, int i)
{
    if(!v[i].lazy) return;
    v[i].n *= -1;
    v[i].mx *= -1;
    v[i].mn *= -1;
    swap(v[i].mx, v[i].mn);
    if(s != e)
    {
        v[i*2].lazy = !v[i*2].lazy;
        v[i*2+1].lazy = !v[i*2+1].lazy;
    }
    v[i].lazy = 0;
}

void update(int s, int e, int i, int l, int r)
{
    lp(s, e, i);
    if(r < s || e < l) return;
    if(l <= s && e <= r)
    {
        v[i].lazy = !v[i].lazy;
        lp(s, e, i);
        return;
    }
    int m = (s+e) >> 1;
    update(s, m, i*2, l, r);
    update(m+1, e, i*2+1, l, r);
    v[i] = merge(v[i*2], v[i*2+1]);
}

Node query(int s, int e, int i, int l, int r)
{
    lp(s, e, i);
    if(r < s || e < l) return {0, 0, 0, 0};
    if(l <= s && e <= r)
    {
        return v[i];
    }
    int m = (s+e) >> 1;
    auto t1 = query(s, m, i*2, l, r);
    auto t2 = query(m+1, e, i*2+1, l, r);
    return merge(t1, t2);
}

int main(void)
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, i, q, a, b, c;
    cin >> n;
    cin >> st;
    init(1, n, 1);
    cin >> q;
    while(q--)
    {
        cin >> a >> b >> c;
        if(a%2)
        {
            update(1, n, 1, b, c);
        }
        else
        {
            auto t = query(1, n, 1, b, c);
            int ans = abs(t.n - 2*min(0, t.mn));
            cout << ans+(c-b+1) << "\n";
        }
    }
}