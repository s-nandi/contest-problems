//line sweep (parallel - times and events)
//http://codeforces.com/contest/912/problem/C

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long

struct event
{
    int time;
    int healthUpdate;
    int enemy;
    int setTime;
    bool forced;

    bool operator < (event o) const
    {
        if (time != o.time) return time < o.time;
        if (forced != o.forced) return forced;

        return healthUpdate < o.healthUpdate;
    }
};

ll bounty, increase;
int damage;
vector <event> events;
set <int> checkTimes;

vector <int> maxHealth;
vector <int> regen;
vector <int> startHealth;

int timeToKill(int currHealth, int regen, int threshold)
{
    return (threshold - currHealth) / regen;
}

void insertEvent(int time, int enemy, int health)
{
    events.push_back({time, health, enemy, time, true});
    if (health <= damage and maxHealth[enemy] > damage and regen[enemy] > 0)
    {
        int ttk = timeToKill(health, regen[enemy], damage);
        events.push_back({time + ttk + 1, damage + 1, enemy, time, false});
        checkTimes.insert(time + ttk);
    }
    else
    {
        checkTimes.insert(time - 1);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;
    cin>>bounty>>increase>>damage;

    maxHealth.resize(n);
    startHealth.resize(n);
    regen.resize(n);

    for (int i = 0; i < n; i++)
    {
        int s;
        cin>>maxHealth[i]>>startHealth[i]>>regen[i];
        insertEvent(0, i, startHealth[i]);
    }

    for (int i = 0; i < m; i++)
    {
        int time, enemy, health;
        cin>>time>>enemy>>health;
        --enemy;
        insertEvent(time, enemy, health);
    }

    sort(events.begin(), events.end());

    int lastTime = events[events.size() - 1].time + 1;
    checkTimes.insert(0);
    checkTimes.insert(lastTime);

    set <int> killable;
    vector <int> latestEvent(n, -1);

    int currEvent = 0;
    ll best = 0;
    for (int currTime: checkTimes)
    {
        while (currEvent < events.size() and events[currEvent].time <= currTime)
        {
            event curr = events[currEvent++];

            if (curr.forced)
            {
                latestEvent[curr.enemy] = curr.time;
            }
            else if (curr.setTime < latestEvent[curr.enemy])
            {
                continue;
            }

            if (curr.healthUpdate <= damage)
            {
                killable.insert(curr.enemy);
            }
            else
            {
                killable.erase(curr.enemy);
            }
        }

        best = max(best, (ll) killable.size() * (bounty + currTime * increase));
    }

    if (killable.size() > 0 and increase > 0)
    {
        cout<<-1<<'\n';
    }
    else
    {
        cout<<best<<'\n';
    }

    return 0;
}
