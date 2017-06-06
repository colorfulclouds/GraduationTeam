//先到先服务，短作业优先，时间片轮转，优先级优先！
#include<stdio.h>
#include<stdlib.h>
//#include<conio.h>
#define N 50
struct Job{
		int Process_ID;  //
		int Process_ArriveTime;  //到达时刻
		int Process_ServeTime;  //ServeTime	
		int Process_FinishTime;  //完成时刻
		int Process_ServeTime2; //标志是否完成
                int Process_Priority;
		float CyclingTime;  //CyclingTime
		float Weighted_CyclingTime;  //WeightedCyclingTime
	};
void RR();
void FIFO();
void SJF();
void Priotity();
int main()
{      
void  RR();
void  FIFO();
void  SJF();
void  Priority();
int a;
while(true)
{
	printf("\n\n");
//	printf("\t\t/*************************/");
	printf(" 1.FIFO 2.SJF 3.RR 4.Priority 5.Exit");
	printf("\nplease choose:\n ");
	scanf("%d",&a);
	printf("\n");
	switch(a)
	{
	case 1: FIFO();break;
	case 2: SJF();break;
	case 3: RR();break;
	case 4: Priority();break;
        case 5: exit(0);
	}
	if(a<0&&a>4) break;
}
return 0;
}
void RR()
{
	int i,j,n,min,px,RR,time;
	float sum1,sum2;
	bool flag=true;
	printf("Please input the number of process(0<n<=50):\t");
	scanf("%d",&n);
	while(n>50||n<=0)
	{
		printf("Please input again：  ");
		scanf("%d",&n);
	}
	printf("\n\n");
	printf("Please input timer(0<RR):\t");
	scanf("%d",&RR);
	while(RR<=0)
	{
		printf("Please input again：  ");
		scanf("%d",&RR);
	}
	Job a[N];
	for(i=0;i<n;i++)
	{
		a[i].Process_ID=i+1;
                printf("The Process_ID of this process:%d",a[i].Process_ID);
		printf("ArriveTime： \n ");
		scanf("%d",&a[i].Process_ArriveTime);
		printf("ServeTime：\n  ");
		scanf("%d",&a[i].Process_ServeTime);
		a[i].Process_ServeTime2 = a[i].Process_ServeTime;
		printf("\n");
	}
	for(j=n-1;j>=0;j--)
	{  
		for(i=0;i<j;i++)
		{
			if(a[i].Process_ArriveTime>a[i+1].Process_ArriveTime) 
			{
				
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min; 
				
				min=a[i].Process_ServeTime2;
				a[i].Process_ServeTime2=a[i+1].Process_ServeTime2;
				a[i+1].Process_ServeTime2=min;
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
			}
		} 
	}
	time = a[0].Process_ArriveTime;
	min = 0;
	while(min<n)
	{
		flag = true;
		for(i = 0;i<n;i++)
			{
				if(a[i].Process_ServeTime2>0&&a[i].Process_ArriveTime<=time)
				flag = false;				
				
			}
		for(i=0;i<n;i++)
		{
			
			if(a[i].Process_ServeTime2 > 0 )
			{
				if(a[i].Process_ArriveTime<=time)
				{
					//printf("当前a[%d].Process_ServeTime2值为：%d\n",i,a[i].Process_ServeTime2);
					a[i].Process_ServeTime2 = a[i].Process_ServeTime2 - RR;
					//printf("运算后当前a[%d].Process_ServeTime2值为：%d\n",i,a[i].Process_ServeTime2);
					//printf("当前TIME值为：%d\n",time);
					time = time + RR;
					//printf("增加之后TIME值为：%d\n",time);
					if(a[i].Process_ServeTime2<=0)
					{	
						a[i].Process_FinishTime = time + a[i].Process_ServeTime2;
						a[i].CyclingTime=(float)(a[i].Process_FinishTime-a[i].Process_ArriveTime);
						a[i].Weighted_CyclingTime=a[i].CyclingTime/a[i].Process_ServeTime;											
						min++;
					}		
					
				}else if(flag)
				{
					for(i=0;i<n;i++)
					{
						if(a[i].Process_ServeTime2>0&&a[i].Process_ArriveTime>time)
						{
							time = a[i].Process_ArriveTime;
							break;
						}
						
					}
				}
					
					
			}
		}
	}
	
	printf("\t1、Output with Process_Process_ID\n");
	printf("\t2、Output with Finishnumber\n");
	printf("\nPlease imput 1 or 2:\t");
	scanf("%d",&px);
	printf("\nProcess_ID：ArriveTime\tServeTime\tFinishTime\tCyclingTime\tWeightedCyclingTime\n");
	sum1=0;
	sum2=0;
	switch(px)
	{
	case 2:
		
			for(i=0;i<n;i++)
			{     printf("%d：\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_ServeTim    e,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
                                sum1+=a[i].CyclingTime;
				sum2+=a[i].Weighted_CyclingTime;
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}
	case 1: 
		{
			for(j=0;j<n;j++)
			{    
				for(i=0;i<n;i++)
					if(a[i].Process_ID==j+1)
					{
						printf("%d： %d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_ServeTime,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
						sum1+=a[i].CyclingTime;
						sum2+=a[i].Weighted_CyclingTime;
					}
					
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}  
	default: break;
	}
}
void FIFO()
{
	int i,j,n,min,px;
	float sum1,sum2;
	printf("Please input the number of process(0<n<=50):\n");
	scanf("%d",&n);
	while(n>50||n<=0)
	{
		printf("Please input again： \n");
		scanf("%d",&n);
	}
	//printf("\n\n");
	Job a[N];
	for(i=0;i<n;i++)
	{       
		a[i].Process_ID=i+1;
                printf("Please input the no.%d Process_ID\n",a[i].Process_ID);
		printf("ArriveTime：\n  ");
		scanf("%d",&a[i].Process_ArriveTime);
		printf("ServeTime：\n  ");
		scanf("%d",&a[i].Process_ServeTime);
		printf("\n");
	}
	
	for(j=n-1;j>=0;j--)
	{  
		for(i=0;i<j;i++)
		{
			if(a[i].Process_ArriveTime>a[i+1].Process_ArriveTime) 
			{
				
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min;  
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
			}
		} 
	}
	a[0].Process_FinishTime=a[0].Process_ServeTime+a[0].Process_ArriveTime;
	a[0].CyclingTime=(float)a[0].Process_ServeTime;
	a[0].Weighted_CyclingTime=a[0].CyclingTime/a[0].Process_ServeTime;
	
	for(i=1;i<n;i++)
	{
		if(a[i].Process_ArriveTime>a[i-1].Process_FinishTime)
		{
			a[i].Process_FinishTime=a[i].Process_ArriveTime+a[i].Process_ServeTime;
			a[i].CyclingTime=(float)a[i].Process_ServeTime;
			a[i].Weighted_CyclingTime=a[i].CyclingTime/a[i].Process_ServeTime;
		}
		else
		{
			a[i].Process_FinishTime=a[i-1].Process_FinishTime+a[i].Process_ServeTime;
			a[i].CyclingTime=(float)(a[i].Process_FinishTime-a[i].Process_ArriveTime);
			a[i].Weighted_CyclingTime=a[i].CyclingTime/a[i].Process_ServeTime;
		}
	}                                                                      
	
	printf("1、Output with Process_Process_ID\n");
	printf("2、Output with Finishnumber\n");
	printf("Please choose 1 or 2:\n");
	scanf("%d",&px);
	printf("\nProcess_ID：ArriveTime\tServeTime\tFinishTime\tCyclingTime\tWeightedCyclingTime\n");
	sum1=0;
	sum2=0;
	switch(px)
	{
	case 2:
		{	  
			for(i=0;i<n;i++)
			{    
				printf("%d：\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_ServeTime,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
				sum1+=a[i].CyclingTime;
				sum2+=a[i].Weighted_CyclingTime;
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}
	case 1: 
		{
			for(j=0;j<n;j++)
			{    
				for(i=0;i<n;i++)
					if(a[i].Process_ID==j+1)
					{
						printf("%d：\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_ServeTime,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
						sum1+=a[i].CyclingTime;
						sum2+=a[i].Weighted_CyclingTime;
					}
					
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}  
	default: break;
	}
}

void SJF()
{
	int i,j,n,min,px;
	int b=0,z;
	float sum1,sum2;
	printf("\n\t\tPlease input the number of process(0<n<=50):\t");
	scanf("%d/n",&n);
	while(n>50||n<=0)
	{
		printf("n\tPlease input again：  ");
		scanf("%d",&n);
	}
	printf("\n");
	Job a[N];
	for(i=0;i<n;i++)
	{
		a[i].Process_ID=i+1;
		printf("ArriveTime：\n ");
		scanf("%d",&a[i].Process_ArriveTime);
		printf("ServeTime：\n ");
		scanf("%d",&a[i].Process_ServeTime);
		printf("\n");
	}
	
	min=a[0].Process_ArriveTime;       
	for(j=n-1;j>=0;j--)
	{  
		for(i=0;i<j;i++)
		{
			if(a[i].Process_ArriveTime>a[i+1].Process_ArriveTime) 
			{
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min;            
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
			}
			if(a[i].Process_ArriveTime==a[i+1].Process_ArriveTime&&a[i].Process_ServeTime>a[i+1].Process_ServeTime)
			{
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min;  
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
			}
		} 
	}
	a[0].Process_FinishTime=a[0].Process_ServeTime+a[0].Process_ArriveTime;
	a[0].CyclingTime=(float)a[0].Process_ServeTime;
	a[0].Weighted_CyclingTime=a[0].CyclingTime/a[0].Process_ServeTime;
	
	for(i=1;i<n;i++)
	{
		if(a[i].Process_ArriveTime>a[0].Process_FinishTime) ;
		else b=b+1;
		
	}
	
	for(j=b-1;j>=1;j--)
	{  
		for(i=1;i<j;i++)
		{
			if(a[i].Process_ServeTime>a[i+1].Process_ServeTime) 
			{
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min;   
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
				
			}
		} 
	}
	
	for(i=1;i<n;i++)
	{
		if(a[i].Process_ArriveTime>a[i-1].Process_FinishTime)
		{
			a[i].Process_FinishTime=a[i].Process_ArriveTime+a[i].Process_ServeTime;
			a[i].CyclingTime=(float)a[i].Process_ServeTime;
			a[i].Weighted_CyclingTime=a[i].CyclingTime/a[i].Process_ServeTime;
		}
		else
		{
			a[i].Process_FinishTime=a[i-1].Process_FinishTime+a[i].Process_ServeTime;
			a[i].CyclingTime=(float)(a[i].Process_FinishTime-a[i].Process_ArriveTime);
			a[i].Weighted_CyclingTime=a[i].CyclingTime/a[i].Process_ServeTime;
		}		  
		
		for(j=i+1,b=j;j<n;j++)
		{
			if(a[j].Process_ArriveTime>a[i].Process_FinishTime) ;
			else b=b+1;
			
		}
		
		for(j=b-1;j>=i;j--)
		{  
			for(z=i;z<j;z++)
			{
				if(a[z].Process_ServeTime>a[z+1].Process_ServeTime) 
				{
					min=a[z].Process_ArriveTime;
					a[z].Process_ArriveTime=a[z+1].Process_ArriveTime;
					a[z+1].Process_ArriveTime=min;
					
					min=a[z].Process_ServeTime;
					a[z].Process_ServeTime=a[z+1].Process_ServeTime;
					a[z+1].Process_ServeTime=min; 
					
					min=a[i].Process_ID;
					a[i].Process_ID=a[i+1].Process_ID;
					a[i+1].Process_ID=min;
					
				}
			} 
		}
	}                                                                      
	printf("Please input 1 or 2\n");
	printf("1、Output with Process_Process_ID\n");
	printf("2、Output with Finishnumber\n");
	scanf("%d",&px);
	printf("\nProcess_ID：ArriveTime\tServeTime\tFinishTime\tCyclingTime\tWeightedCyclingTime\n");
	sum1=0;
	sum2=0;
	switch(px)
	{
	case 2:
		{	  
			for(i=0;i<n;i++)
			{     printf("%d：\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_ServeTim    e,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
                                sum1+=a[i].CyclingTime;
				sum2+=a[i].Weighted_CyclingTime;
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}
	case 1:
		{ 
			for(j=0;j<n;j++)
			{      for(i=0;i<n;i++)
			if(a[i].Process_ID==j+1)
			{
                                printf("%d：\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_ServeTim    e,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
				sum1+=a[i].CyclingTime;
				sum2+=a[i].Weighted_CyclingTime;
			}
			
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}  
	default: break;
	}
	
}

void Priority()
{
	int i,j,n,min,px;
	int b=0,z;
	float sum1,sum2;
	printf("\n\t\tPlease input the number of process(0<n<=50):\t");
	scanf("%d/n",&n);
	while(n>50||n<=0)
	{
		printf("n\tPlease input again：  ");
		scanf("%d",&n);
	}
	printf("\n");
	/*struct Job{
		int Process_ID;  //进程名字
		int Process_ArriveTime;  //到达时刻
		int Process_ServeTime;  //ServeTime
		int Priority; //优先级
		int Process_FinishTime;  //完成时刻
		float CyclingTime;  //CyclingTime
		float Weighted_CyclingTime;  //WeightedCyclingTime
		
	};*/
	Job a[N];
	for(i=0;i<n;i++)
	{
		a[i].Process_ID=i+1;
		printf("\tArriveTime： ");
		scanf("%d",&a[i].Process_ArriveTime);
		printf("\tServeTime： ");
		scanf("%d",&a[i].Process_ServeTime);
		printf("\t优先级： ");
		scanf("%d",&a[i].Process_Priority);
		printf("\n");
	}
	
	min=a[0].Process_ArriveTime;       
	for(j=n-1;j>=0;j--)
	{  
		for(i=0;i<j;i++)
		{
			if(a[i].Process_ArriveTime>a[i+1].Process_ArriveTime) 
			{
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min;            
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
				
				min=a[i].Process_Priority;
				a[i].Process_Priority=a[i+1].Process_Priority;
				a[i+1].Process_Priority=min;
			}
			if(a[i].Process_ArriveTime==a[i+1].Process_ArriveTime&&a[i].Process_Priority<a[i+1].Process_Priority)
			{
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min;  
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
				
				min=a[i].Process_Priority;
				a[i].Process_Priority=a[i+1].Process_Priority;
				a[i+1].Process_Priority=min;
			}
		} 
	}
	a[0].Process_FinishTime=a[0].Process_ServeTime+a[0].Process_ArriveTime;
	a[0].CyclingTime=(float)a[0].Process_ServeTime;
	a[0].Weighted_CyclingTime=a[0].CyclingTime/a[0].Process_ServeTime;
	
	for(i=1;i<n;i++)
	{
		if(a[i].Process_ArriveTime>a[0].Process_FinishTime) ;
		else b++;
		
	}
	
	for(j=b-1;j>=1;j--)
	{  
		for(i=1;i<j;i++)
		{
			if(a[i].Process_Priority<a[i+1].Process_Priority) 
			{
				min=a[i].Process_ArriveTime;
				a[i].Process_ArriveTime=a[i+1].Process_ArriveTime;
				a[i+1].Process_ArriveTime=min;
				
				min=a[i].Process_ServeTime;
				a[i].Process_ServeTime=a[i+1].Process_ServeTime;
				a[i+1].Process_ServeTime=min;   
				
				min=a[i].Process_ID;
				a[i].Process_ID=a[i+1].Process_ID;
				a[i+1].Process_ID=min;
				
				min=a[i].Process_Priority;
				a[i].Process_Priority=a[i+1].Process_Priority;
				a[i+1].Process_Priority=min;
				
			}
		} 
	}
	
	for(i=1;i<n;i++)
	{
		if(a[i].Process_ArriveTime>a[i-1].Process_FinishTime)
		{
			a[i].Process_FinishTime=a[i].Process_ArriveTime+a[i].Process_ServeTime;
			a[i].CyclingTime=(float)a[i].Process_ServeTime;
			a[i].Weighted_CyclingTime=a[i].CyclingTime/a[i].Process_ServeTime;
		}
		else
		{
			a[i].Process_FinishTime=a[i-1].Process_FinishTime+a[i].Process_ServeTime;
			a[i].CyclingTime=(float)(a[i].Process_FinishTime-a[i].Process_ArriveTime);
			a[i].Weighted_CyclingTime=a[i].CyclingTime/a[i].Process_ServeTime;
		}		  
		
		for(j=i+1,b=j;j<n;j++)
		{
			if(a[j].Process_ArriveTime>a[i].Process_FinishTime) ;
			else b=b+1;
			
		}
		
		for(j=b-1;j>=i;j--)
		{  
			for(z=i;z<j;z++)
			{
				if(a[z].Process_Priority<a[z+1].Process_Priority) 
				{
					min=a[z].Process_ArriveTime;
					a[z].Process_ArriveTime=a[z+1].Process_ArriveTime;
					a[z+1].Process_ArriveTime=min;
					
					min=a[z].Process_ServeTime;
					a[z].Process_ServeTime=a[z+1].Process_ServeTime;
					a[z+1].Process_ServeTime=min; 
					
					min=a[i].Process_ID;
					a[i].Process_ID=a[i+1].Process_ID;
					a[i+1].Process_ID=min;
					
				}
			} 
		}
	}                                                                      
	printf("\n\t请选择输出顺序\n");
	printf("\t1、Output with Process_Process_ID\n");
	printf("\t2、Output with Finishnumber\n");
	scanf("%d",&px);
	printf("\nProcess_ID：ArriveTime\tServeTime\tPriority\tFinishTime\tCyclingTime\tWeightedCyclingTime\n");
	sum1=0;
	sum2=0;
	
	switch(px)
	{
	case 2:
		{	  
			for(i=0;i<n;i++)
			{   printf("%d：\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_ServeTime,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
				sum1+=a[i].CyclingTime;
				sum2+=a[i].Weighted_CyclingTime;
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}
	case 1:
		{ 
			for(j=0;j<n;j++)
			{      for(i=0;i<n;i++)
			if(a[i].Process_ID==j+1)
			{
				printf("%d：\t\t%d\t\t%d\t\t%d\t\t%d\t\t%.0f\t\t%.2f\n",a[i].Process_ID,a[i].Process_ArriveTime,a[i].Process_Priority,a[i].Process_ServeTime,a[i].Process_FinishTime,a[i].CyclingTime,a[i].Weighted_CyclingTime);
				sum1+=a[i].CyclingTime;
				sum2+=a[i].Weighted_CyclingTime;
			}
			
			}
			printf("\nAverageCyclingTime：%.2f\n",sum1/n);
			printf("\nAverageWeightedCyclingTime：%.2f\n\n",sum2/n);
			break;
		}  
	default: break;
	}
	
}

