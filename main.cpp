#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

void print_matrix(char Playfair_matrix[][5]);
void enter_letters(char Playfair_matrix[][5]);
void enter_key(char Playfair_matrix[][5], char key[],int p);
int search_letters(char Playfair_matrix[][5],char letter);
void encryption(char encryption_msg[][2],char Playfair_matrix[][5],char planText_RS[],char matrix[][2],int m);
void decryption(char encryption_msg[][2],char Playfair_matrix[][5],int m);
void message(char planText_RS[],char matrix[][2],int& m);
void row_col(char Playfair_matrix[][5],char letter,char letter2,int& i1,int& j1,int& i2,int& j2);
int menu();


int main()
{
   int j=0,chose,n=0,m=0,z=0;
   char Playfair_matrix[5][5];
   char planText[1000],planText_RS[1000];
   for(int d=0;d<5;d++)
   {
       for(int a=0;a<5;a++)
       {
           Playfair_matrix[d][a]=' ';
       }
   }
   cout<<"-----Play Fair Cipher-----"<<endl<<endl;
   cout<<"ENTER plan Text : ";
   for(int i=0;i<1000;i++)
   {
       planText[i]=' ';
   }
   cin.getline(planText,999);
   while((isalpha(planText[z])) || (planText[z]==' '))
    {
        n++;
        z++;
    }
    z=0;
   cout<<endl<<endl<<"plan Text after space remove : ";
   for(int i=0;i<n;i++)
   {
       if(isalpha(planText[i]))
       {
           planText_RS[j]=planText[i];
           j++;
       }
   }
   for(int i=0;i<j;i++)
   {
       if(isalpha(planText_RS[i]))
       {
           cout<<planText_RS[i];
       }
   }
   cout<<endl<<"message for encryption is    : ";
    while(isalpha(planText_RS[z]))
    {
        m++;
        z++;
    }
    if((m%2)!=0)
    {
        m++;
    }
    m=m/2;
    char matrix[100][2];
    for(int i=0;i<100;i++)
    {
        matrix[i][0]=' ';
        matrix[i][1]=' ';
    }
    message(planText_RS,matrix,m);
    for(int i=0;i<m;i++)
    {
        cout<<matrix[i][0]<<matrix[i][1]<<' ';
    }
   cout<<endl<<endl;;
   char encryption_msg[m][2];
   while((chose=menu())!=3)
   {
       switch(chose)
       {
           case 1:
                encryption(encryption_msg,Playfair_matrix,planText,matrix,m);break;
           case 2:
                decryption(encryption_msg,Playfair_matrix,m);break;
       }
   }
   return 0;
}


void message(char planText_RS[],char matrix[][2],int& m)
{
    int z=0,k=0,n=0;
    bool flag=false,flag2=false ;
    while(isalpha(planText_RS[z]))
    {
        n++;
        z++;
    }
    if((n%2)!=0)
    {
        flag2=true;
        n++;
    }
    for(int i=0;i<(n/2);i++)
    {
        for(int j=0;j<2;j++)
        {
           if(planText_RS[k]== planText_RS[k+1])
           {
               matrix[i][j]=planText_RS[k];
               matrix[i][j+1]='x';
               k++;
               j=j+2;
               m++;
               flag=true;
           }
           else
           {
               matrix[i][j]=planText_RS[k];
               matrix[i][j+1]=planText_RS[k+1];
               k=k+2;
               j=j+2;

           }
        }
    }
    if((flag2==true)&&(flag==false))
    {
        matrix[m-1][1]='x';
    }
    if((flag2==false)&&(flag==true))
    {
        matrix[m-1][0]=planText_RS[z-1];
        matrix[m-1][1]='x';
    }
}


void encryption(char encryption_msg[][2],char Playfair_matrix[][5],char planText_RS[],char matrix[][2],int m)
{
   char key[30];
   int p,i1,j1,i2,j2;
   cout<<"ENTER Key : ";
   cin>>key;
   p = strlen(key);
   enter_key(Playfair_matrix,key,p);
   enter_letters(Playfair_matrix);
   print_matrix(Playfair_matrix);

   for(int i=0;i<m;i++)
   {
      row_col(Playfair_matrix,matrix[i][0],matrix[i][1],i1,j1,i2,j2);
      if(i1==i2)
      {
          if((j1+1)== 5)
          {
              j1=0;
              encryption_msg[i][0]= Playfair_matrix[i1][j1];
              encryption_msg[i][1]= Playfair_matrix[i2][j2+1];
          }
          else if((j2+1)== 5)
          {
              j2=0;
              encryption_msg[i][0]= Playfair_matrix[i1][j1+1];
              encryption_msg[i][1]= Playfair_matrix[i2][j2];
          }
          else
          {
             encryption_msg[i][0]= Playfair_matrix[i1][j1+1];
             encryption_msg[i][1]= Playfair_matrix[i2][j2+1];
          }
      }
      else if(j1==j2)
      {
          if((i1+1)== 5)
          {
              i1=0;
              encryption_msg[i][0]= Playfair_matrix[i1][j1];
              encryption_msg[i][1]= Playfair_matrix[i2+1][j2];
          }
          else if((i2+1)== 5)
          {
              i2=0;
              encryption_msg[i][0]= Playfair_matrix[i1+1][j1];
              encryption_msg[i][1]= Playfair_matrix[i2][j2];
          }
          else
          {
              encryption_msg[i][0]= Playfair_matrix[i1+1][j1];
              encryption_msg[i][1]= Playfair_matrix[i2+1][j2];
          }
      }
      else
      {
          encryption_msg[i][0]= Playfair_matrix[i1][j2];
          encryption_msg[i][1]= Playfair_matrix[i2][j1];
      }
   }
   cout<<endl;
    for(int i=0;i<m;i++)
   {
       cout<<matrix[i][0]<<matrix[i][1]<<'='<<encryption_msg[i][0]<<encryption_msg[i][1]<<"  ";
   }
   cout<<endl<<endl<<endl<<"Encryption msg is : ";
   for(int i=0;i<m;i++)
   {
       cout<<encryption_msg[i][0]<<encryption_msg[i][1];
   }
   cout<<endl<<endl;
}


void decryption(char encryption_msg[][2],char Playfair_matrix[][5],int m)
{
    int i1,j1,i2,j2;
    cout<<endl<<endl<<"Encryption msg is : ";
   for(int i=0;i<m;i++)
   {
       cout<<encryption_msg[i][0]<<encryption_msg[i][1];
   }
    cout<<endl<<endl<<"plan Text msg is : ";
    for(int i=0;i<m;i++)
   {
      row_col(Playfair_matrix,encryption_msg[i][0],encryption_msg[i][1],i1,j1,i2,j2);
      if(i1==i2)
      {
          if((j1-1)== -1)
          {
              j1=4;
              cout<<Playfair_matrix[i1][j1];
              cout<<Playfair_matrix[i2][j2-1];
          }
          else if((j2-1)== -1)
          {
              j2=4;
              cout<<Playfair_matrix[i1][j1-1];
              cout<<Playfair_matrix[i2][j2];
          }
          else
          {
             cout<<Playfair_matrix[i1][j1-1];
             cout<<Playfair_matrix[i2][j2-1];
          }
      }
      else if(j1==j2)
      {
          if((i1-1)== -1)
          {
              i1=4;
              cout<<Playfair_matrix[i1][j1];
              cout<<Playfair_matrix[i2-1][j2];
          }
          else if((i2-1)== -1)
          {
              i2=4;
              cout<<Playfair_matrix[i1-1][j1];
              cout<<Playfair_matrix[i2][j2];
          }
          else
          {
              cout<<Playfair_matrix[i1-1][j1];
              cout<<Playfair_matrix[i2-1][j2];
          }
      }
      else
      {
          cout<<Playfair_matrix[i1][j2];
          cout<<Playfair_matrix[i2][j1];
      }
   }
   cout<<endl<<endl;
}


void row_col(char Playfair_matrix[][5],char letter,char letter2,int& i1,int& j1,int& i2,int& j2)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(Playfair_matrix[i][j]==letter)
            {
                i1= i;
                j1= j;
            }
            if(Playfair_matrix[i][j]==letter2)
            {
                i2= i;
                j2= j;
            }
        }
    }
}


int menu()
{
    int choice;
        cout<<"             {  menu }              "<<endl;
        cout<<" ------  enter 1 for encryption  -------"<<endl;
        cout<<" ------  enter 2 for decryption  -------"<<endl;
        cout<<" ------  enter 3 to exit         -------"<<endl;
    cin>>choice;
    return(choice);
}


int search_letters(char Playfair_matrix[][5],char letter)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(Playfair_matrix[i][j]==letter)
            {
                return 0;
            }
            if(Playfair_matrix[i][j]==' ')
            {
                Playfair_matrix[i][j]=letter;
                return 1;
            }
        }
    }

}


void enter_letters(char Playfair_matrix[][5])
{
    int l=0;
    char letters[]="abcdefghiklmnopqrstuvwxyz";
    while(l<25)
    {
        if((search_letters(Playfair_matrix,letters[l]))==0)
        {

        }
        l++;
    }
}


void enter_key(char Playfair_matrix[][5], char key[], int p)
{
   int k=0;
   for(int i=0;i<5;i++)
   {
      for(int j=0;j<5;j++)
      {
        if(k==p)
        {
            return;
        }
        if((search_letters(Playfair_matrix,key[k]))==0){ k++;}
        else
        {
            k++;
        }
      }
    }
}


void print_matrix(char Playfair_matrix[][5])
{
   for(int i=0;i<5;i++)
   {
      for(int j=0;j<5;j++)
      {
          if(Playfair_matrix[i][j]=='i')
          {
              cout<<"i/j"<<' ';
          }
          else
          {
              cout<<' '<<Playfair_matrix[i][j]<<"  ";
          }
      }
      cout<<endl;
   }
}
