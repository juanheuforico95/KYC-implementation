#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<cassert>
#include<iomanip>
using namespace std;

#define MAX 100
#define for(i,a,b) for(i=a;i<b; i++)
string gram[MAX][MAX];
string dpr[MAX];
int p,production_numbers;
inline string concatenador( string input1, string input2)   {
    int i;
    string r=input1;
    for(i,0,input2.length())
        if(r.find(input2[i]) > r.length())
            r+=input2[i];
    return (r);
}
inline void dividir(string a) {
    int i;
    p=0;
    while(a.length())
    {
        i=a.find("|");
        if(i>a.length())
        {
            dpr[p++] = a;
            a="";
        }
        else
        {
            dpr[p++] = a.substr(0,i);
            a=a.substr(i+1,a.length());
        }
    }
}

inline int lch(string a)  {
    if(a.length()==1 && a[0]>='A' && a[0]<='Z')
        return 1;
    return 0;
}

inline int rch(string a)   {
    if (a.length() == 1 && a[0]>='a' && a[0] <='z')
        return 1;
    if (a.length()==2 && a[0]>='A' && a[0]<='Z' && a[1]>='A' && a[1]<='Z' )
        return 1;
    return 0;
}

inline string producciones(string p){
    int j,k;
    string r="";
    for(j,0,production_numbers)
    {
        k=1;
        while(gram[j][k] != "")
        {
            if(gram[j][k] == p)
            {
                r=concatenador(r,gram[j][0]);
            }
            k++;
        }
    }
    return r;
}

inline string convinar(string a, string b)  {
    int i,j;
    string pri=a,re="";
    for(i,0,a.length())
        for(j,0,b.length())
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+producciones(pri);
        }
    return re;
}
int pos=0;
int main()
{
    string input;
    int i,pt,j,l,k;
    string a,str,r,pr,start;
    cout<<"\nVariable inicial= ";
    cin >> start;
    cout<<"\nNumero de producciones= ";
    cin >> production_numbers;
    cout <<  "\n Ingrese las producciones de la siguiente forma: ";
    cout <<  "\n S==AB, A==a,B==b\n";

    for(i,0,production_numbers)
    {
        cin >> a;
        pt=a.find("==");
        gram[i][0] = a.substr(0,pt);
        if (lch(gram[i][0]) == 0)
        {
            cout<<"\nLa gramatica no esta en forma de Chomsky\n";
            abort();
        }
        a = a.substr(pt+2, a.length());
        dividir(a);
        for(j,0,p)
        {
            gram[i][j+1]=dpr[j];
            if (rch(dpr[j]) == 0)
            {
                cout<<"\nLa gramatica no esta en forma de Chomsky";
                abort();
            }
        }
    }
    string matrix[MAX][MAX],st;
    cout<<"\nIngresa la cadena w ";
    cin >> str;
    for(i,0,str.length())
    {
        r="";
        st = "";
        st+=str[i];
        for(j,0,production_numbers)
        {
            k=1;
            while(gram[j][k] != "")
            {
                if(gram[j][k] == st)
                {
                    r=concatenador(r,gram[j][0]);
                }
                k++;
            }
        }
        matrix[i][i]=r;
    }
    int ii,kk;
    for(k,1,str.length())
    {
        for(j,k,str.length())
        {
            r="";
            for(l,j-k,j)
            {
                pr = convinar(matrix[j-k][l],matrix[l+1][j]);
                r = concatenador(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }

    cout<<input;
    int f=0;
    for(i,0,start.length())
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())
            {
            cout<<"El string puede ser generado.\n";
              return 0;

        }
        cout<<"no se pudo formar el string\n";



    return 0;
}
