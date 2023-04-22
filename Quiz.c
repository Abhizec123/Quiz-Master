// A mini Quiz Project where students can give a short Quiz Exam and Fairness of the Quiz is maintained by getting Random Questions by each student
// Students can also view their Friend's score
// How to run this Code??
// Ans  -> Open cmd and go to specific folder and then type the Command "Quiz Questions.DAT" and it's done
// Files needed to run this Program??
// >> Questions.DAT >> Answers.DAT >> Score.DAT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 10

char name[35];

void main(int argc,char *argv[])
{
    FILE    *fp,*fp1;
    char    s[150],ch;
    int     a[n],i,j=0,k,c,n1,p=1;

    system("cls");printf("\n");
    srand(time(0)); // Alternative of randomize() in gcc Compiler

    if(argc<2)
    {
        printf("\nToo Few Parameters");
        exit(0);
    }
    else if(argc>2)
    {
        printf("\nToo Many Parameters");
        exit(0);
    }

    fp=fopen(argv[1],"r");
    if(fp==NULL)
    {
        printf("\nFile Opening Error!");
        exit(0);
    }
    intro();system("cls");

    // Generating a Random Number
    fp1=fopen("Student.DAT","w");
    for(i=0;i<n;i++)
    {
        k=1;
        while(k==1)
        {
            n1=rand()%20+1; // Alternative of random() in gcc compiler
            k=search(a,j,n1); // Passing to a function to check whether it is already generated or not
        }
        a[j++]=n1;

        // Obtaining the String and Extracting Questions and Options from it
        c=0;
        while(fgets(s,150,fp)!=NULL)
        {
            if(c+1==n1)
            {
                printf("Question %d : ",p++);
                question(s);
                printf("\tYour Answer : ");
                ch=getche(); // Answering the Question
                fprintf(fp1,"%c\n",ch);
                printf("\n\n");
                break;
            }
            else
                c++;
        }
        rewind(fp);
    }
    fclose(fp);
    fclose(fp1);

    system("cls");
    printf("\nPress:\n1. To View Result\n2. To Exit\n\n");
    printf("Enter Your Choice : ");
    ch=getche();

    switch(ch)
    {
        case '1':
            result(a);
            break;
        case '2':
            exit(0);
    }
    printf("\n");
}
// Printing Intro
void intro()
{
    long int    r;

    printf("\n TECHNO MAIN SALT LAKE");
    printf("\n\n Computer Science And Engg");
    printf("\n Basic Aptitude Test");
    printf("\n Subject Code : BA-101");
    printf("\n Full Marks : %d",(2*n));
    printf("\n ---------------------------");

    printf("\n\n INSTRUCTION TO CANDIDATES : ");
    printf("\n\n 1. There are Total %d Questions in the Question Paper (2 Marks Each).",n);
    printf("\n 2. Attempt all the Questions.");
    printf("\n 3. You just need to type the Correct Option in SMALL letters (a/b/c/d).");
    printf("\n 4. You will just get only one attempt to type the Correct option");

    printf("\n\n\t\tEnter Your Name .........: ");
    gets(name);
    printf("\t\tEnter Your Roll Number ..: ");
    scanf("%ld",&r);

    printf("\n\t\t\tBEST OF LUCK!");
    printf("\n\t\t\t START EXAM");
    getche();
}
// Function to check whether the random number generated is already generated before
int search(int a[],int c,int n1)
{
    int i,f;

    f=0;
    for(i=0;i<c;i++)
    {
        if(n1==a[i])
        {
            f=1;
            break;
        }
    }
    return f;
}
// Printing Questions and Options
void question(char *s)
{
    char    s1[150];
    int     l,i,p,k=0;

    l=strlen(s);
    for(i=4;i<l;i++)
    {
        if(*(s+i)=='?')
        {
            s1[k++]='?';
            s1[k]='\0';
            p=i;
            break;
        }
        else
            s1[k++]=*(s+i);
    }
    printf("%s\n",s1); // Printing Questions
    printf("\n");

    k=0;
    for(i=p+2;i<=l;i++)
    {
        if((*(s+i)==32 && *(s+i+1)=='(') || i==l)
        {
            s1[k]='\0';
            printf("%s\n",s1); // Printing Options
            k=0;
        }
        else
            s1[k++]=*(s+i);
    }
}
// Printing Individuals result
void result(int a[])
{
    FILE    *fp1,*fp2,*fp3,*fp4;
    int     n1,c,c1=0,i=0,p=0;
    char    s[10],s1[150],r[10],p1[10],ch;

    fp1=fopen("Student.DAT","r");
    fp2=fopen("Answers.DAT","r");
    fp3=fopen("Questions.DAT","r");
    fp4=fopen("Score.DAT","a");

    printf("\n\nWrongly Answered Questions ->\n\n");
    while(fgets(r,10,fp1)!=NULL)
    {
        n1=a[i++];c=0;
        while(fgets(s,10,fp2)!=NULL && fgets(s1,150,fp3)!=NULL)
        {
            if(c+1==n1)
            {
                // Matching the answers
                if(r[0]==s[4])
                    p++;
                else if(r[0]!=s[4])
                {
                    question1(s1); // Function to print Wrong Attempted Questions
                    c1++;
                }
                break;
            }
            else
                c++;
        }
        rewind(fp2);rewind(fp3);
    }
    itoa(p*2,p1,10);// Converting the Integer Score to String p1
    fputs(name,fp4);
    fputs(" ",fp4);
    fputs(p1,fp4);
    fputs("\n",fp4);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    if(c1==0)
        printf("<<None>>\n");
    printf("\nCorrect Answer   : %d",p);
    printf("\nIncorrect Answer : %d",n-p);
    printf("\nMarks Secured    : %d out of %d",(2*p),(2*n));
    if((2*p)>=n)
        printf("\n\nREMARKS : PASS");
    else
        printf("\n\nREMARKS : FAIL");

    printf("\n\nDo you want to check your Friend's Score [Y/N]? ");
    ch=getche();

    if(ch=='Y' || ch=='y')
        score();
    else
        exit(0);
}
// Printing Wrongly Attempted Questions
void question1(char *s)
{
    char    s1[150];
    int     l,i,k=0;

    l=strlen(s);
    for(i=4;i<l;i++)
    {
        if(*(s+i)=='?')
        {
            s1[k++]='?';
            s1[k]='\0';
            break;
        }
        else
            s1[k++]=*(s+i);
    }
    printf(">> %s\n",s1); // Printing Questions
}
// Displaying Name & Score of all attendees
void score()
{
    FILE    *fp;
    char    nm[100],s1[35],s2[10];
    int     i,l,k;
    system("cls");printf("\n");

    fp=fopen("Score.DAT","r");

    printf("\tFRIEND'S - SCORE\n\t----------------\n\n");
    printf(" NAME\t\t\tPOINTS\n\n");
    while(fgets(nm,100,fp)!=NULL)
    {
        l=strlen(nm);k=0;
        for(i=0;i<l;i++)
        {
            if(nm[i]==32 && (nm[i+1]>=48 && nm[i+1]<=57))
            {
                s1[k]='\0';
                s2[0]=nm[l-3];
                s2[1]=nm[l-2];
                s2[3]='\0';
                printf(" %-25s%3d\n",s1,atoi(s2));
                break;
            }
            else
                s1[k++]=nm[i];
        }
    }
    fclose(fp);
    printf("\n << PRESS ANY KEY TO EXIT >>");
    getch();
}
