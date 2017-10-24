#include<string>
#include<cassert>
#include<iomanip>
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

#define MAX 100

#define for(i,a,b) for(i=a;i<b; i++)

string gramatica[MAX][MAX];
string dpr[MAX];
int p,numero_producciones;       //numero_producciones-> numero de producciones

inline string concat( string a, string b)   //Concatena solamente a las no terminales
{
    int i;
    string r=a;
    for(i,0,b.length())
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}

inline int lchomsky(string a)   //Revisa si el lado izquierdo de la gramatica esta en forma normal
{
    if(a.length()==1 && a[0]>='A' && a[0]<='Z')
        return 1;
    return 0;
}

inline void break_gramatica(string a)    //Separa el lado derecho de la gramaticaatica agregada
{
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

inline string buscar_produccion(string p) //Regresa un string concatenado de variables que pueden producir el string p
{
    int j,k;
    string r="";
    for(j,0,numero_producciones)
    {
        k=1;
        while(gramatica[j][k] != "")
        {
            if(gramatica[j][k] == p)
            {
                r=concat(r,gramatica[j][0]);
            }
            k++;
        }
    }
    return r;
}

inline int rchomsky(string a)   //Revisa si el lado derecho de la gramatica esta en forma normal
{
    if (a.length() == 1 && a[0]>='a' && a[0] <='z')
        return 1;
    if (a.length()==2 && a[0]>='A' && a[0]<='Z' && a[1]>='A' && a[1]<='Z' )
        return 1;
    return 0;
}



inline string gen_comb(string a, string b)  //Crea las cmbinaciones desde a y b. Ejemplo: BA * AB = {BA, BB, AA, BB}
{
    int i,j;
    string pri=a,re="";
    for(i,0,a.length())
        for(j,0,b.length())
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+buscar_produccion(pri);     //Revisa si las producciones generadas pueden ser creadas o no.
        }
    return re;
}

int pos=0;


int main()
{
    string input;

    int i,pt,j,l,k;
    string a,str,r,pr,start;
    cout<<"\nBienvenido al programaticaa que implementa el algoritmo KYC.\n ";
    //cout<<choice;
    cout<<"\nSi tiene dudas de como funciona este codigo porfavor ver el README.\n ";
    cout<<"\nIngrese la Variable Inicial: ";
    cin >> start;
    cout<<"\nIngrese numero de producciones: ";
    cin >> numero_producciones;
    for(i,0,numero_producciones)
    {
        cin >> a;
        pt=a.find("->");
        gramatica[i][0] = a.substr(0,pt);
        if (lchomsky(gramatica[i][0]) == 0)
        {
            cout<<"\nLa gramaticaatica no esta en forma de Chomsky\n";
            abort();
        }
        a = a.substr(pt+2, a.length());
        break_gramatica(a);
        for(j,0,p)
        {
            gramatica[i][j+1]=dpr[j];
            if (rchomsky(dpr[j]) == 0)
            {
                cout<<"\nLa gramaticaatica no esta en forma de Chomsky";
                abort();
            }
        }
    }
    string matrix[MAX][MAX],st;
    int choice=0;
    do{
    cout<<"\nIngrese el string a ser revisado, ejemplo: [baaba]: ";
    cin >> str;
    for(i,0,str.length())       //Asigna los valores a la diagnal principal de la matriz.
    {
        r="";
        st = "";
        st+=str[i];
        for(j,0,numero_producciones)
        {
            k=1;
            while(gramatica[j][k] != "")
            {
                if(gramatica[j][k] == st)
                {
                    r=concat(r,gramatica[j][0]);
                }
                k++;
            }
        }
        matrix[i][i]=r;
    }
    int ii,kk;
    for(k,1,str.length())       //Asigna los valores a la parte superor de la matriz.
    {
        for(j,k,str.length())
        {
            r="";
            for(l,j-k,j)
            {
                pr = gen_comb(matrix[j-k][l],matrix[l+1][j]);
                r = concat(r,pr);
            }
            matrix[j-k][j] = r;
        }
    }

    for(i,0,str.length())   //Imprime la matriz.
    {
        k=0;
        l=str.length()-i-1;
        for(j,l,str.length())
        {
            cout<<setw(5)<<matrix[k++][j]<<" ";
        }
        cout<<endl;
    }
    cout<<input;
    int f=0;
    for(i,0,start.length())
        if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())   //Revisa si el ultimo elemento de la primera fila contiene una variable inicial (S).
        {
            cout<<"El string puede ser generado.\n";
            cout<<"\nDesea continuar con las mismas producciones? ";
            cin >> input;
            //cout<<input;


        }
    cout<<"El string no puede ser generado.\n";
    cout<<"\nDesea continuar con las mismas producciones? ";
        cin >> input;

    }while(input.compare("yes")!=0);
    return 0;
}
