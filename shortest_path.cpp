#include<fstream>
using namespace std;
#define size(x) sizeof(x)/sizeof(x[0])

bool ifnotPresent(int arr[],int elem)
{
    int size  = size(arr);
    for(int i=0;i<size;i++)
    {
        if(arr[i] == elem)
            return false;
    }
    return true;
}
int shortest_path(int src,int dest)
{
    int nV,nE;
    ofstream  fout;
    ifstream fin("graph.txt");
    fin>>nV>>nE;
    if(src>nV-1 ||dest>nV-1)
        return 0;
    //create 2d array to store the vertices with there weights
    int V[nV][nV];

    //initiate array with all zero
    for(int i=0;i<nV;i++)
    {
        for(int j=0;j<nV;j++)
        {
            V[i][j] = 0;
        }
    }
    //accepting city names
    
    int vA,vB,weight; //temp variable for getting values
    
    //filling graph into matrix
    for(int i =0;i<nE;i++)
    {
        fin>>vA>>vB>>weight;
        V[vA][vB] = V[vB][vA] = weight; 
    }

    int count=0;
    int neg[nV];//array to store permanent set//switched to queue
    neg[count++]=src;
    
    
    int index,minWeight,distance=0;
    
    //algo starts
    
    
    while(src!=dest)
    {
        minWeight=0;
        for(int i =0;i<nV;i++)
        {
            if(V[src][i]!=0)
            {
                if(i == dest)
                {
                    minWeight = V[src][i];
                    index = i;
                    break;
                }
                if(ifnotPresent(neg,i))
                {
                    if(V[src][i]<minWeight || minWeight == 0)
                    {
                        minWeight = V[src][i];
                        index = i;
                    }
                }                
            }
        }
        //update index to neg array 
        src = index;
        neg[count++] = src;
        distance+=minWeight;


    }
    fin.close();
    //writting result to file
    fout.open("result");
    fout<<count<<"\n";
    for(int i=0;i<count;i++)
        fout<<neg[i]<<"\n";
    fout<<distance<<"\n";
    fout.close();
    return 1;
}