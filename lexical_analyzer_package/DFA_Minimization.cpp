#include "DFA_Minimization.h"


DFA_Minimization::DFA_Minimization(vector < vector < DFA_State > > DFA )
{
    //ctor
    this ->DFA_Copy = DFA;

}

vector< vector <int> > DFA_Minimization:: minimize (vector < DFA_State > newStates)
{
    vector < vector <DFA_State> > sets ;
    // add final and not final to sets vector
    vector <DFA_State> acceptance ;
    vector <DFA_State> nonacceptance;
    map <int, int> stateSet;
    int counter = 2;

    for (int i =0 ; i< newStates.size();i++)
    {
        if (newStates[i].is_final())
        {
            acceptance.push_back(newStates[i]);
            stateSet.insert(pair<char,int>(newStates[i].get_state_number(), 0));
        }else
        {
            nonacceptance.push_back(newStates[i]);
            stateSet.insert(pair<char,int>(newStates[i].get_state_number(), 1));
        }
    }

    sets.push_back(acceptance);
    sets.push_back(nonacceptance);

    bool f = true;

    while(f)
    {
        f = false;
        int setCount = sets.size();
        for(int i = 0 ; i < setCount ; i++)
        {
            for(int j = 0 ; j < sets[0].size() ; j++)
            {
                vector <DFA_State> cur;
                cur.push_back(sets[0][j]);
                int first_state =sets[0][j].get_state_number();
                stateSet[first_state] = counter;

                for(int k = j+1 ; k < sets[0].size() ; k++)
                {
                    int second_state = sets[0][k].get_state_number();
                    bool check = true;
                    for(int l = 0 ; l < DFA_Copy[0].size() ; l++)
                    {
                        if(stateSet[DFA_Copy[first_state][l].get_state_number()] != stateSet[DFA_Copy[second_state][l].get_state_number()])
                            check =false;
                    }
                    if (check)
                    {
                        cur.push_back(sets[0][k]);
                        sets[0].erase(sets[0].begin() + k);
                        stateSet[second_state] = counter;
                        k--;
                    }
                    else
                        f=true;
                }
                sets.push_back(cur);
                sets[0].erase(sets[0].begin() + j);
                j--;
                counter++;
            }
            sets.erase(sets.begin());
        }
    }

    map <int, int> rootState;
   vector < vector <int> > MDFA ;

    for(int i = 0 ; i < sets.size() ; i++)
        for(int j = 0 ; j < sets[i].size() ; j++)
            rootState.insert(pair<int, int> (sets[i][j].get_state_number(), sets[i][0].get_state_number()));


    for(int i = 0 ; i < DFA_Copy.size() ; i++)
    {
        vector <int > row ;
        for(int j = 0 ; j < DFA_Copy[i].size() ; j++)
        {
            int state = DFA_Copy[i][j].get_state_number();
            if (state==-1)
                row.push_back(-1);
            else
                row.push_back(rootState[state]);

        }
        MDFA.push_back(row);

    }
   return MDFA;
}
DFA_Minimization::~DFA_Minimization()
{
    //dtor
}
