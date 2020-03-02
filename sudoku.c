#include<stdio.h>
#include<conio.h>
#include<dos.h>
#define DIM 9
#define SAFE 1
#define NOTSAFE 0
#define WIDTH 3
#define HEIGHT 1
#define DIM 9
//shapes to draw
#define LT 218
#define HL 196
#define VL 179
#define RT 191
#define TT 194
#define BT 193
#define LST 195
#define RST 180
#define CROSS 197
#define SP 32
#define LB 192
#define RB 217


//if you want to change number ,modify here.
int grid[DIM][DIM]=
        {{3, 4, 0, 8, 2, 6, 0, 7, 1},
        {0, 0, 8, 0, 0, 0, 9, 0, 0},
        {7, 6, 0, 0, 9, 0, 0, 4, 3},
        {0, 8, 0, 1, 0, 2, 0, 3, 0},
        {0, 3, 0, 0, 0, 0, 0, 9, 5},
        {0, 7, 0, 9, 0, 4, 0, 1, 0},
        {8, 2, 0, 0, 4, 0, 0, 5, 9},
        {0, 0, 7, 0, 0, 0, 3, 0, 0},
        {4, 1, 0, 3, 8, 9, 0, 6, 2}};

int array[DIM][DIM];

//To draw a sudokubox
void drawbox()
{
  int br,bc,ctr,ctr1,ctr2;
  bc = ( 80  - ( DIM * ( WIDTH + 1 ) ) )  / 2;
  br = ( 25 - ( DIM * ( HEIGHT + 1) ) )  / 2;
  gotoxy(bc,br);
  printf("%c",LT);
  for( ctr1 =  0 ; ctr1 < DIM ; ctr1++ )
  {
     for( ctr= 0 ; ctr < WIDTH ; ctr++)
       printf("%c",HL);
       printf("%c",TT);
  }
  printf("\b%c",RT);
  for( ctr2 = 0 ; ctr2 < DIM ; ctr2++)
  {
  gotoxy(bc,++br);
  for( ctr1 = 0 ; ctr1 <= DIM ; ctr1++ )
  {
     printf("%c",VL);
     for( ctr = 0  ; ctr < WIDTH ; ctr++)
 printf(" ");
  }
  gotoxy(bc,++br);
  printf("%c",LST);
  for( ctr1 =  0 ; ctr1 < DIM ; ctr1++ )
  {
     for( ctr= 0 ; ctr < WIDTH ; ctr++)
       printf("%c",HL);
       printf("%c",CROSS);
  }
  printf("\b%c",RST);
  }
  gotoxy(bc,br);
  printf("%c",LB);
  for( ctr1 =  0 ; ctr1 < DIM ; ctr1++ )
  {
     for( ctr= 0 ; ctr < WIDTH ; ctr++)
       printf("%c",HL);
       printf("%c",BT);
  }
 printf("\b%c",RB);
}

void posfind()
{   int i,j;
    for(i=0;i<DIM;i++)
    {
 for(j=0;j<DIM;j++)
        {
     if(grid[i][j]!=0)
  array[i][j]=j;
     else
  array[i][j]=-1;
 }
    }
}

//checking the number is already placed in that row.
int checkhori(int row,int num){
 int r,c;
 for(r=row,c=0;c<9;c++){
     if(grid[r][c]==num) return NOTSAFE;}
 return SAFE;
}

//checking the number is already placed in that column.
int checkverti(int col,int num){
 int r,c;
 for(r=0,c=col;r<9;r++) {
   if(grid[r][c]==num)
         return NOTSAFE;
      }
 return SAFE;
}

//checking the number is already placed in that matrix.
int checkbox(int row,int col,int num)
{
    int r,c;
    for(r=0;r<3;r++)
    {
        for(c=0;c<3;c++)
        {
     if(grid[r+row][c+col]==num) return NOTSAFE;
 }
    }return  SAFE;
}

int issafe(int row,int col,int num)
{
    int r,c,i,rowb,colb;
    rowb=row-row%3;
    colb=col-col%3;
    if((checkverti(col,num)==SAFE)&&(checkbox(rowb,colb,num)==SAFE))
    return 1;
   return 0;
}

void placenumberinbox(int row , int col)
{
   int bc,br;
  // delay(100);
   bc = ( 80  - ( DIM * ( WIDTH + 1 ) ) )  / 2;
  br = ( 25 - ( DIM * ( HEIGHT + 1) ) )  / 2;
      bc += 2;
      br++;

   gotoxy( bc + ( WIDTH + 1) * col , br+(HEIGHT +1)*row);
   printf("%d",grid[row][col]);
}

void placegivennumber()
{    int row,col;
    for(row=0;row<DIM;row++)
  {
   for(col=0;col<DIM;col++)
   {
      placenumberinbox(row,col);
      }
  }
}

int arraycheck(int row, int num)
{    int count,c,trav;
    for(c=0;c<DIM,grid[row][c]!=num;c++);
    count=0;
    for(trav=0;trav<DIM;trav++)
    {
 if(array[row][trav]==c)
      count++;
    }
    return count;
}

//checking whether there is no place to place numbers.
int nomorenull(int row)
{
    int i,nomore=0;
    for(i=0;i<DIM;i++)
    {
 if(grid[row][i]!=0)
     nomore++;
    }
    return nomore;
}
void removenumberinbox(int row , int col)
{
   int bc,br;
   bc = ( 80  - ( DIM * ( WIDTH + 1 ) ) )  / 2;
  br = ( 25 - ( DIM * ( HEIGHT + 1) ) )  / 2;
      bc += 2;
      br++;

   gotoxy( bc + ( WIDTH + 1) * col , br+(HEIGHT +1)*row);
   printf("%d",grid[row][col]);
}

int removenumber(int row,int num )
{
    int i,j;
    for(i=0;i<9;i++)
    {
 if(grid[row][i]==num)
    { grid[row][i]=0;
      removenumberinbox(row,i);
     break;}
    }

    return i;
}

void sudokusolver()
{
    int row=0,col,num,safecol=0;
    for(num=1;num<=9;num++)
    {  row=safecol=0;
       for(row=row;row<DIM;row++)
 {
   for(col=safecol;col<DIM;col++)
   {
        if (grid[row][col]==0){
   if(checkhori(row,num)==NOTSAFE)
       break;
    else
       if(issafe(row,col,num)==SAFE){
      grid[row][col]=num;
    placenumberinbox(row,col);
    safecol=0;
    break;}}
   }//end of col for loop
  //backtracking
  if(nomorenull(row)!=9){
     if(col==9)
     {
       row--;
       if(row==-1)
   {
     row=8;
     num--;
   }
      while(row!=-1){
      if(arraycheck(row,num)!=1)
        {
        safecol=removenum(row,num);
        safecol+=1;
        row--;
        break;}
      else
        {row--;
  if(row==-1)
  {
   row=8;
   num--;
  }
        }}//end of while loop
  }}
}//end of row for loop
}//end of num for loop
}

int main()
{ int row,col;
 clrscr();
 drawbox();
 placegivennumber();
 sudokusolver();
 getch();
 return 0;
}