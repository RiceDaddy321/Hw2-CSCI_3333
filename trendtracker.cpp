#include "trendtracker.h"

//the things will be initially sorted
Trendtracker::Trendtracker(string filename)
{
    ifstream f;
    string line = "";

    f.open(filename);

    while(getline(f, line))
    {
        Entry newEntry;
        newEntry.hashtag = line;
        newEntry.pop = 0;
        E.push_back(newEntry);

        if (S.size() < 3)
            S.push_back(E.size() - 1);

        line = "";
    }

    f.close();
}

int Trendtracker::size()
{
    return E.size();
}

void Trendtracker::tweeted(string ht)
{
    int index = search(ht);

    if(index == -1)
        return;

    E[index].pop++;

    //for getting the S vertex filled out
    switch (S.size())
    {
    case 0:
        S.push_back(index);
        break;
    case 1:
        //check if index in vector
        if (index == S[0])
            return;

        //otherwise add it to the vector
        S.push_back(index);
        if (E[S[0]].pop < E[S[1]].pop)
            swap(S[0], S[1]);
        break;
    case 2:
        //check if index in vector
        if (index == S[0] || index == S[1])
        {
            //verify that everything is in order
            if (E[S[0]].pop < E[S[1]].pop)
                swap(S[0], S[1]);

            return;
        }

        //otherwise add it to the vector
        S.push_back(index);
        if (E[S[1]].pop < E[S[2]].pop)
            swap(S[1], S[2]);
        if (E[S[0]].pop < E[S[1]].pop)
            swap(S[0], S[1]);
        break;
    case 3:
        //check if index in vector
        if (index == S[0] || index == S[1] || index == S[2])
        {
            //verify that everything is in order
            if (E[S[0]].pop < E[S[1]].pop)
                swap(S[0], S[1]);
            if (E[S[1]].pop < E[S[2]].pop)
                swap(S[1], S[2]);
            if (E[S[0]].pop < E[S[1]].pop)
                swap(S[0], S[1]);

            return;
        }

        //otherwise check if in the top three
        if (E[S[0]].pop < E[index].pop)
        {
            swap(S[0], S[2]);
            S[0] = index;
            swap(S[1], S[2]);

            return;
        }
        if (E[S[1]].pop < E[index].pop)
        {
            swap(S[1], S[2]);
            S[1] = index;

            return;
        }
        if (E[S[2]].pop < E[index].pop)
        {
            S[2] = index;
        }
        break;
    }
}

int Trendtracker::popularity(string name)
{
    int index = search(name);

    if(index == -1)
        return -1;

    return E[index].pop;
}

string Trendtracker::top_trend()
{
   return  E[S[0]].hashtag;
}

void Trendtracker::top_three_trends(vector<string> &T)
{
    T.clear();
    switch (T.size())
    {
    case 3:
        return;
        break;
    case 2:
        T.push_back(E[S[0]].hashtag);
        break;
    case 1:
        T.push_back(E[S[0]].hashtag);
        T.push_back(E[S[1]].hashtag);
        break;
    case 0:
        for(int i = 0; i < E.size() && i < 3; i++)
            T.push_back(E[S[i]].hashtag);
        break;
    }
}

int Trendtracker::search(string ht)
{
    int start = 0;
    int end = E.size()-1;
    while(start<=end)
    {
        int mid = start + (end-start)/2;
        
        if(E[mid].hashtag == ht)
            return mid;
        else if(E[mid].hashtag < ht)
            start = mid + 1;
        else
            end = mid - 1;
    }

    return -1;
}