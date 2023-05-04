#include <bits/stdc++.h>
using namespace std;

string num[11] = {"+![]", "+!![]", "+!![]+!![]", "+!![]+!![]+!![]", "+!![]+!![]+!![]+!![]", "+!![]+!![]+!![]+!![]+!![]", "+!![]+!![]+!![]+!![]+!![]+!![]", "+!![]+[+![]]-!![]-!![]-!![]", "+!![]+[+![]]-!![]-!![]", "+!![]+[+![]]-!![]"};

vector<string> s(1010);
vector<int> v(1010);

int main(void)
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int i, j, a, b, c;
    cout << num[0] << "\n";
    for(i=1;i<1000;i++)
    {
        string t = "";
        a = i/100;
        b = (i/10)%10;
        c = i%10;
        if(a)
        {
            t += num[a];
        }
        if(b)
        {
            if(a) t += "+[" + num[b] + "]";
            else t += num[b];
        }
        else
        {
            if(a) t += "+[" + num[0] + "]";
        }
        if(c)
        {
            if(a || b) t += "+[" + num[c] + "]";
            else t += num[c];
        }
        else
        {
            if(a || b) t += "+[" + num[0] + "]";
        }
        if((a || b) && (t + "-[]").size() <= 75)
        {
            s[i] = t;
            v[i] = 1;
        }
        else if((!(a || b)) && t.size() <= 75)
        {
            s[i] = t;
        }
        else
        {
            int mn = 1987654321;
            string tmp;
            for(j=2;j<=floor(sqrt(i));j++)
            {
                if(!(i % j))
                {
                    t = "[" + s[i/j] + "]*[" + s[j] + "]";
                    if(mn > t.size())
                    {
                        mn = t.size();
                        tmp = t;
                    }
                }
            }
            if(mn <= 75)
            {
                s[i] = tmp;
            }
        }
    }
    for(i=1;i<1000;i++)
    {
        if(s[i].size() < 2)
        {
            int chk = 0;
            for(j=-6;j<0;j++)
            {
                if(s[i+j].size() < 2) continue;
                string p = "-[]" + num[-j];
                p = s[i+j] + p;
                if(p.size() <= 75)
                {
                    chk = 1;
                    s[i] = p;
                    break;
                }
            }
            if(!chk)
            {
                for(j=1;j<=5;j++)
                {
                    if(s[i+j].size() < 2) continue;
                    string p = "";
                    for(int k=0;k<j;k++)
                    {
                        p += "-!![]";
                    }
                    p = s[i+j] + p;
                    if(p.size() <= 75)
                    {
                        s[i] = p;
                        break;
                    }
                }
            }
        }
    }
    for(i=1;i<1000;i++)
    {
        cout << s[i] << (v[i] ? "-[]" : "") << "\n";
    }
    cout << "+!![]+[+![]]+[+![]]+[+![]]-[]\n";
}