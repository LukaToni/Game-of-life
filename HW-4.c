#include <stdio.h>
#include <stdlib.h>


//zive celice
int x_live[1000];
int y_live[1000];
int alive_cell_num;

//neig_Xe celice (zive+njeni sosedi)
int all_X[8000];
int all_Y[8000];
int i_of_cell[8000];
int alive_cell, i, j;

int neig_X[8]={-1,-1 , -1,  0, 1,  1, 1, 0}; //sosedje
int neig_Y[8]={-1, 0,   1,  1, 1,  0, -1, -1};

int isAlive(int v, int s)
{
	for(i=0; i<alive_cell_num; i++)
		{
			if(x_live[i]==v)
			{
				if(y_live[i]==s)
				{
					return (1);
				}
			}
		}
return (0);
}
int inTabel(int v, int s)
{
	for(i=0; i<alive_cell; i++)
	{
		if(all_X[i]==v)
		{
			if(all_Y[i]==s)
			{
				return (1);
			}
		}
	}
return 0;
}

void neig_XeCel()
{
alive_cell=0;
int i, j;
	for(i=0; i<alive_cell_num; i++)
	{
		for(j=0; j<8; j++){ //8 sosedov
			if(isAlive(x_live[i]+neig_X[j],y_live[i]+neig_Y[j])==1)
			{ //sosed je ziv
				continue;
			}
			if(inTabel(x_live[i]+neig_X[j],y_live[i]+neig_Y[j])==1)
			{ // vpisan sosed
				continue;
			}
			else
			{ // èe ni sosed ziv ga daj v tabelo
				all_X[alive_cell] = x_live[i]+neig_X[j];
				all_Y[alive_cell] = y_live[i]+neig_Y[j];
				i_of_cell[alive_cell] = 0;
				alive_cell++;
			}
		}
		
	all_X[alive_cell] = x_live[i]; //zivo v tabelo neig_Xeh
	all_Y[alive_cell] = y_live[i];
	i_of_cell[alive_cell] = 1;
	alive_cell++;
	}
}

int stanjeCel(int v, int s)
{
int i;
	for(i=0; i<alive_cell; i++)
	{
		if(all_X[i]==v)
		{
			if(all_Y[i]==s)
			{
				return (i_of_cell[i]);
			}
		}
	}
return (0);
}

int num_of_neig(int v, int s)
{
int num_neigh=0, i, j;
	for(i=0; i<8; i++)
	{
		for(j=0; j<alive_cell; j++)
		{
			if(all_X[j]==(v+neig_X[i]))
			{
				if(all_Y[j]==(s+neig_Y[i]))
				{
					if(i_of_cell[j]==1)
					{
						num_neigh++;
					}
				}
			}
		}

	}
return (num_neigh);
}

int main(){

int nGen;

scanf("%d\n", &nGen);
scanf("%d\n", &alive_cell_num);

//nova generacija
int stCelNG=0;
int vCelNG[1000];
int sCelNG[1000];

int vMin;
int vMax;
int sMin;
int sMax;
int l,m;
int i,j;
for (i = 0; i < alive_cell_num; i++) 
{
	scanf("%d %d\n", &x_live[i], &y_live[i]);
}

for(i=0; i<nGen; i++)
{
	stCelNG=0;
	neig_XeCel(); 
		for(j=0; j<alive_cell; j++)
		{
			if(i_of_cell[j]==1)
			{//ziva
				if((num_of_neig(all_X[j],all_Y[j])==2)||(num_of_neig(all_X[j],all_Y[j])==3))
				{
					vCelNG[stCelNG]= all_X[j];
					sCelNG[stCelNG]= all_Y[j];
					stCelNG++;
				}
			}
			
			if(i_of_cell[j]==0)
			{//mrtva
				if((num_of_neig(all_X[j],all_Y[j])==3))
				{
					vCelNG[stCelNG]= all_X[j];
					sCelNG[stCelNG]= all_Y[j];
					stCelNG++;
				}
			}
		}

		for(l=0; l<alive_cell; l++)
		{
		all_X[l]=0;
		all_Y[l]=0;
		i_of_cell[l]=0;

		x_live[l]=0;
		y_live[l]=0;
		}

		for(m=0; m<stCelNG; m++)
		{
		x_live[m]=vCelNG[m];
		y_live[m]=sCelNG[m];
			if((i+1)==nGen)
			{ //last generation
				if(m==0)
				{
					vMin=x_live[m];
					vMax=x_live[m];
					sMin=y_live[m];
					sMax=y_live[m];
					continue;
				}
				if(x_live[m]<vMin)
				{
					vMin=x_live[m];
				}
				if(x_live[m]>vMax)
				{
					vMax=x_live[m];
				}
				if(y_live[m]<sMin)
				{
					sMin=y_live[m];
				}
				if(y_live[m]>sMax)
				{
					sMax=y_live[m];
				}
			}
		}
	alive_cell_num=stCelNG;
	stCelNG=0;
	alive_cell=0;
	}
	if(alive_cell_num>0)
	{
		printf("%d %d %d %d %d\n", alive_cell_num, vMin, vMax, sMin, sMax);
	}
	if(alive_cell_num==0)
	{
		printf("%d\n", alive_cell_num);
	}
return (0);
}
