#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
#include <cmath>

using namespace std;

void display(vector<vector<int>> *V)
{
    for (vector<int> i : *V)
    {
        for (int j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

// {{6, 0, 0, 0, 0, 0, 0, 2, 7},
//  {2, 0, 7, 0, 0, 0, 6, 0, 9},
//  {0, 0, 9, 0, 0, 0, 0, 5, 0},
//  {0, 0, 6, 0, 5, 0, 4, 0, 0},
//  {4, 0, 1, 0, 0, 2, 7, 0, 5},
//  {0, 0, 0, 0, 0, 0, 0, 0, 0},
//  {1, 5, 0, 7, 0, 0, 0, 0, 0},
//  {0, 0, 4, 0, 9, 3, 0, 7, 0},
//  {9, 7, 0, 4, 0, 0, 0, 3, 1}};
int getBoxNumber(int i, int j)
{
    int I = floor(i / 3);
    int J = floor(j / 3);
    return (3 * I) + J;
}

bool backTrack(vector<unordered_set<int>> *Vertical, vector<unordered_set<int>> *Horizontal, vector<unordered_set<int>> *Box, map<array<int, 2>, int> *numbers, vector<vector<int>> *result, int vacancies, map<array<int, 2>, int>::iterator itr)
{
    if (vacancies == 0)
    {
        for (auto num : *numbers)
        {
            int i = num.first[0];
            int j = num.first[1];
            int n = num.second;
            result->at(i)[j] = n;
        }
        return true;
    }
    if (itr == numbers->end())
    {
        return false;
    }
    int i = itr->first[0];
    int j = itr->first[1];
    for (int k = 1; k <= 9; k++)
    {
        if (Vertical->at(j).find(k) != Vertical->at(j).end())
        {
            continue;
        }
        if (Horizontal->at(i).find(k) != Horizontal->at(i).end())
        {
            continue;
        }
        if (Box->at(getBoxNumber(i, j)).find(k) != Box->at(getBoxNumber(i, j)).end())
        {
            continue;
        }
        itr->second = k;
        Horizontal->at(i).insert(k);
        Vertical->at(j).insert(k);
        Box->at(getBoxNumber(i, j)).insert(k);

        itr++;
        if (backTrack(Vertical, Horizontal, Box, numbers, result, vacancies - 1, itr))
        {
            return true;
        }
        itr--;

        Vertical->at(j).erase(k);
        Horizontal->at(i).erase(k);
        Box->at(getBoxNumber(i, j)).erase(k);
        itr->second = -1;
    }
    return false;
}

bool solve(vector<vector<int>> *result, vector<vector<int>> *grid)
{
    vector<unordered_set<int>> Vertical(grid->size());
    vector<unordered_set<int>> Horizontal(grid->size());
    vector<unordered_set<int>> Box(grid->size());

    map<array<int, 2>, int> numbers;

    int vacancies = 0;
    for (int i = 0; i < grid->size(); i++)
    {
        for (int j = 0; j < grid->at(i).size(); j++)
        {
            if (grid->at(i)[j] == 0)
            {
                numbers[{i, j}] = -1;
                vacancies++;
                continue;
            }
            Horizontal[i].insert(grid->at(i)[j]);
            Vertical[j].insert(grid->at(i)[j]);
            Box[getBoxNumber(i, j)].insert(grid->at(i)[j]);
        }
    }
    *result = *grid;
    return backTrack(&Vertical, &Horizontal, &Box, &numbers, result, vacancies, numbers.begin());
}

int main()
{
    vector<vector<int>> grid = {{6, 0, 0, 0, 0, 0, 0, 2, 7},
                                {2, 0, 7, 0, 0, 0, 6, 0, 9},
                                {0, 0, 9, 0, 0, 0, 0, 5, 0},
                                {0, 0, 6, 0, 5, 0, 4, 0, 0},
                                {4, 0, 1, 0, 0, 2, 7, 0, 5},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {1, 5, 0, 7, 0, 0, 0, 0, 0},
                                {0, 0, 4, 0, 9, 3, 0, 7, 0},
                                {9, 7, 0, 4, 0, 0, 0, 3, 1}};

    vector<vector<int>> result;
    solve(&result, &grid);
    display(&result);
    return 0;
}