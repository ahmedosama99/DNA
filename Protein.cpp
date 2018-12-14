#include "Protein.h"
#include "DNA.h"
#include "RNA.h"
#include "Sequence.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
string A[]= {"Hormon", "Enzyme", "TF", "Cellular_Function"};
Protein:: Protein()
{
    seq = new char;
    type=TF;
}
Protein::Protein (char*a , Protein_Type atype)
{
    seq = new char;
    strcpy(seq,a);
    type=atype;
}
Protein::~Protein()
{
    delete []seq;
}
void Protein:: Print()
{
    cout<<seq<<endl;
}
DNA& Protein::GetDNAStrandsEncodingMe(const DNA & bigDNA)
{
    CodonsTable t;
    DNA  dna;
    DNA d;
    RNA r;
    Protein p;
    string dn="";
    t.LoadCodonsFromFile();
    for(int i = 0; i <=strlen(bigDNA.seq) - strlen(seq)*3 ; i++)
    {
        char* temp = new char[strlen(seq)*3+1];
        temp[strlen(seq)*3+1] = '\0';
        for(int j = 0; j < strlen(seq)* 3; j++)
        {
            temp[j] = bigDNA.seq[i+j];
        }
        d.seq=new char[50];
        strcpy(d.seq,temp);
        delete []temp;
        r=d.ConvertToRNA();
        p=r.ConvertToProtein(t);
        if(p==*this)
        {
            for(int g = 0 ; g <strlen(d.seq); g++)
            {
                dn+=d.seq[g];
            }
            i+=2;
        }
    }
    strcpy(dna.seq,dn.c_str());
    return dna;
}
istream&operator >> (istream &input,Protein & ob)
{
    input>>ob.seq;
    for(int i =0 ; i <strlen(ob.seq) ; i++ )
    {
        if(ob.seq[i]!='K'&&ob.seq[i]!='N'&&ob.seq[i]!='T'&&ob.seq[i]!='R'&&ob.seq[i]!='S'&&ob.seq[i]!='I'&&ob.seq[i]!='M'&&ob.seq[i]!='Q'&&ob.seq[i]!='H'&&ob.seq[i]!='P'&&ob.seq[i]!='L'&&ob.seq[i]!='E'&&ob.seq[i]!='D'&&ob.seq[i]!='A'&&ob.seq[i]!='G'&&ob.seq[i]!='V'&&ob.seq[i]!='Y'&&ob.seq[i]!='C'&&ob.seq[i]!='W'&&ob.seq[i]!='F')
        {
            Protein ::err2 er2;
            throw er2;
        }
    }

    int c=0;
    cout<<"1-Hormon\n2-Enzyme\n3-TF\n4-Cellular_Function\n";
    input>>c;
    if(c==1)
        ob.type=Hormon;
    if(c==2)
        ob.type=Enzyme;
    if(c==3)
        ob.type==TF;
    if(c==4)
        ob.type==Cellular_Function;
    return input;
}
ostream&operator << (ostream &output,Protein & ob)
{
    output<<ob.seq<<endl;
    output<<"the sequence type: "<<A[ob.type-1]<<endl;
    return output;
}
bool Protein ::operator == (Protein otherProtein)
{
    if(strcmp(seq,otherProtein.seq)==0)
        return 1;
    else
        return 0;
}
bool Protein ::operator !=(Protein otherProtein)
{
    if(strcmp(seq,otherProtein.seq)!=0)
        return 0;
    else
        return 1;
}
Protein Protein :: operator +(Protein otherProtein)
{
    Protein Protein3;
    strcpy(Protein3.seq,seq);
    strcat(Protein3.seq,otherProtein.seq);
    return Protein3;
}
