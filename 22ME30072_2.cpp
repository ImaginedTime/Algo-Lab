/**************************************************
    Uday om srivastava, 22ME30072, Assignment 2
***************************************************/

#include <iostream>
using namespace std;


void print(int *a, int p, int* c, int len, int voters, int index)
{
    // counting the numeber of votes for the coalition
    int sum = 0;
    for(int i = 0; i < len - 1; i++)
    {
        if(c[i] - 1 >= index)
            a[c[i] - 1] = 0;
        sum += a[c[i] - 1];
    }

    // if the coalition gets less than or equal to 50% of the votes, they lose and hence we don't print that permutation
    if(sum <= voters / 2)
        return;
    
    // printing the permutations
    for(int i = 0; i < index; i++)
        cout << i + 1 << ": " << a[i] << "\t";
    
    // adding to it the neccessary amount of zeroes
    while(index < p)
    {
        cout << index + 1 << ": " << "0\t";
        index++;
    }

    cout << "\tTotal Votes for the Coalition: " << sum << endl;
}

void vote_dist(int v, int index, int p, int *a, int* c, int len, int voters)
{
    // I have considered 2 base cases, where one is when all the votes have been casted
    // and the other is when there are no more partied to be voted for


    // if all votes have been given, and others wil be filled out with zeroes
    if(v == 0)
    {
        print(a, p, c, len, voters, index);
        return;
    }

    // if we are at the last party to be voted, give all the remaining votes to the last party
    if(index == p - 1)
    {
        a[index++] = v;
        print(a, p, c, len, voters, index);

        return;
    }
    
    // first give v - i numbers of votes to the current party and then distribute the remaining i number of votes to the remaining parties
    for(int i = 0; i <= v; i++)
    {
        a[index] = v - i;
        vote_dist(i, index + 1, p, a, c, len, voters);
    }
}


int main()
{
    // taking the number of voters and parties as input
    int v, p;
    cout << "#Voters: ";
    cin >> v;
    cout << "#Parties: ";
    cin >> p;

    // stores the coalition that needs to be formed
    int *c = (int*)(malloc( p * sizeof(int) ));
    int len = 0;  // length of the coalition

    cout << endl << "Coalition: " << endl;

    // taking coalition as input, when we encounter -1, we stop
    do{
        cin >> c[len++];
    } while(c[len - 1] != -1);

    cout << endl;


    // an auxillary array to store the permutation, is 
    int *a = (int*)(malloc( p * sizeof(int) ));
    for(int i = 0; i < p; i++)
        a[i] = 0;

    vote_dist(v, 0, p, a, c, len, v);

    return 0;
}