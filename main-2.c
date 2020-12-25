#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int i=0, size=50000,j=0,l,s=0,n=0;
struct keyvalue
{
    char* key;
    char* value;
    struct keyvalue* next;
};
struct maillon
{
    char* att;
    struct maillon* nexte;
};
int calculehash(char *ch)//CETTE FONCTION RENVOIE UN INDICE POUR CHAQUE ATTRIBUT
{
    int codehash=0;
    int indice=0,k=0;
    for( k=0; k<strlen(ch); k++)
    {
        codehash=ch[k];
        indice=indice+codehash;

    }
    indice=indice%50;
    return indice;
}

// char ch1[]="dahb";
void inserthash(struct maillon hashh[],char *ch,int k)//INSERTION DE CHAQUE ATTRIBUT DANS LE TAB DE HACHAGE
{
    if(hashh[k].att=='\0')
    {
        hashh[k].att= strdup(ch);
    }
    else
    {
        int t=0;
        t=strcmp(ch,hashh[k].att);
        if(t==0)
        {
            struct maillon *ptr2;
            struct maillon *ptr3;
            ptr2=&hashh[k];
            ptr3=(struct maillon*)malloc(sizeof(struct maillon*));
            ptr3->att=strdup(ch);
            ptr3->nexte=NULL;
            while(ptr2->nexte != NULL)
            {
                ptr2 = ptr2->nexte;
            }
            ptr2->nexte=ptr3;
        }
        else
        {

            k=0;
            while(hashh[k].att!='\0')
                k++;

        }
        hashh[k].att=strdup(ch);
        t=0;
    }
}
void nbroccurence(struct maillon hashh[])//CALCULE DE NOMBRE D'occurence de chaque attribut
{
    int t=0,p=0;
    for(t=0; t<50; t++)
    {
        if( hashh[t].att!='\0')
        {
            struct maillon *tempe ;
            tempe=&hashh[t];
            p++;

            while(tempe->nexte!=NULL)
            {
                tempe=tempe->nexte;
                p++;
            }
            printf("l'attribut  %s est repete %d fois\n",hashh[t].att,p);

        }
        p=0;
    }
}

void insert(struct keyvalue hashtable[],char *ch,char *ch1,int k)//inserer chaque objet dans un tab se structure
{


    if(hashtable[k].key=='\0')
    {
        hashtable[k].key= strdup(ch);
        hashtable[k].value= strdup(ch1);
        hashtable[k].next='\0';

    }
    else
    {
        struct keyvalue *ptr;
        struct keyvalue *ptr1;
        ptr1=&hashtable[k];
        ptr=(struct keyvalue*)malloc(sizeof(struct keyvalue*));

        ptr->key=strdup(ch);
        ptr->value=strdup(ch1);
        ptr->next=NULL;
        while(ptr1->next != NULL)
        {
            ptr1 = ptr1->next;
        }
        ptr1->next=ptr;


    }
}

void afficher(struct keyvalue hashtable[],int s)//affichage des objets
{
    for(j=0; j<s; j++)
    {
        printf("%s\t",hashtable[j].key);
        //printf("\t%s\t",hashtable[j].value);

        struct keyvalue *temp ;
        temp=&hashtable[j];

        while(temp->next!=NULL)
        {
            temp=temp->next;
            printf("%s\t",temp->key);
            printf("\t");
           // printf("\t%s",temp->value);


        }
        printf("\n");
    }
}
int main()
{
     clock_t temps;
     srand(time(NULL));
    int n=0,sizee=50;
    char fileContent[200000];
    char ch[40];
    char ch1[40];
    struct maillon hashh[sizee];//tab de type maillon
    struct keyvalue hashtable[size];//tab de type keyvalue

    do//initialisation de tableau d' objets
    {
        hashtable[i].next=NULL;
        hashtable[i].key='\0';

        i++;
    }
    while(i < size);
    do//initialisation du tableau d'occurence
    {
        hashh[n].att='\0';
        hashh[n].nexte=NULL;
        n++;
    }
    while(n<sizee);

    FILE *f;
    int j=0,i=0,k=0,m=0,p=0,s=0,indice=0;
    char c;
    int index=0;
    f = fopen("txt.txt", "rt");
    int v=0;

    while((c = fgetc(f)) != EOF)
    {
        if(c=='}')v++;

        fileContent[index] = c;
        index++;
        fileContent[index] = '\0';
    }
    while(c != EOF);
    printf("le nombre d'objet est %d",v);
    // printf("%d",index);
    index=0;
    while(fileContent[index]!='\0')
    {
        if (fileContent[index]=='"')
        {
            i=1;
        }
        if (fileContent[index+1]==':')
        {
            i=0;
        }

        while(i)
        {
            index++;
            ch[k]=fileContent[index];
            if(fileContent[index+1]=='"')
            {
                i=0;
            }
            k++;

            if(!i)
            {

                ch[k]='\0';
                indice=calculehash(ch);//calcule de l' indice pour chaque attribut
                inserthash(hashh,ch,indice);//inserer ce attribut dans le tab de hachage
                indice=0;

                k=0;
            }

        }


        if(fileContent[index]==':')
        {
            j=1;
        }
        while(j)
        {
            index++;
            if(fileContent[index]=='"')
            {
                m=1 ;
            }
            if(fileContent[index+1]=='"')
            {
                m=0 ;
            }

            while(m)
            {

                index++;

                ch1[p]=fileContent[index];
                if(fileContent[index]=='"')
                {
                    m=0;
                    p--;
                }

                p++;
                if(!m)
                {
                    ch1[p]='\0';
                    insert(hashtable,ch,ch1,s);//inserer l' attribut et son valeur dans le tableau
                    p=0;

                }
                j=0;

            }
        }
        if(fileContent[index]=='}')s++;//pour connaitre la fin de l'objet
        index++;
    }
    printf("\n");
    printf("SALUT!\n");
   // afficher(hashtable,s);//affichage des objets
    nbroccurence(hashh);//nbre d'occurence de chaque attribuut
    printf("MERCI!\n");
    temps=clock();

     printf("Bravo !\nTu as mis %f secondes a trouver les nombre.\n", (double) temps/CLOCKS_PER_SEC);
    return 0;
}


