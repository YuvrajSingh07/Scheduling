#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
struct pros
{
	int arrivalTime,burstTime,copy_bT,Priority,completion_time,waitingTime,TAT;
	string processID;
};
int findMin(pros [],int);
int findIndex(int,string,pros []);
int m=0,cTsetter=0,checker=0,checker1=0;
class Scheduling
{
	int NoProcess,Var,Indef,Var1,Timer,MinPriority,pPI,pIvar,x,PreviousMinPriority;
	pros pro[50];
	string PreviousPro;
	vector<string> q1,q2;
	vector<int> PrioritySelector;
	public:

		void getData()
		{
			cout<<"\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
			cout<<"\t\t\t|\t\t\tCPU Scheduling  (Multi-Level)           |"<<endl;
			cout<<"\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl<<endl;
			cout<<"  Enter the number of processes :- ";
			cin>>NoProcess;
			if(NoProcess==0)
				exit(0);
			int p=65;
			for(int i=0;i<NoProcess;i++)
			{
				pro[i].processID=char(p);
				cout<<"  Enter  Arrival time  ||   Burst Time   ||   Priority for process ["<<pro[i].processID<<"] respectively"<<endl;
				cout<<"  --> ";
				cin>>pro[i].arrivalTime;
				cin>>pro[i].burstTime;
				pro[i].copy_bT=pro[i].burstTime;
				cin>>pro[i].Priority;
				pro[i].completion_time=0;
				p++;
			}
		}

		void findMinInArrivalTime()
		{
			int minval;
			minval=findMin(pro,NoProcess);
			for(int i=0;i<NoProcess;i++)
            {
				if(pro[i].arrivalTime==minval)
				{
					q1.push_back(pro[i].processID);
					PrioritySelector.push_back(pro[i].Priority);
				}
			}
		}

		void processSelector()
		{
			MinPriority=*(std::min_element(PrioritySelector.begin(),PrioritySelector.end()));
			for(int i=0;i<PrioritySelector.size();i++)
			{
				if(MinPriority==PrioritySelector.at(i))
				{
					Var=i;
					break;
				}
			}
			for(int i=0;i<NoProcess;i++)
			{
				if(pro[i].processID==q1[Var])
				{
					Var1=i;
				}
			}
			if(m>=1)
			{
				if(q1[Var]!=PreviousPro)
				{
					q1.erase(std::remove(q1.begin(),q1.end(),PreviousPro),q1.end());
					if(checker==0)
					{
						PrioritySelector.erase(PrioritySelector.begin()+pIvar,PrioritySelector.begin()+(pIvar+1));
					}
					else
					{
						checker=0;
					}
					if(pro[pPI].burstTime!=0)
					{
						q2.push_back(PreviousPro);
					}
				}
			}
			m+=1;
			pIvar=Var;
			PreviousPro=q1[Var];
			PreviousMinPriority=MinPriority;
			pPI=Var1;
			if(checker1==1)
			{
				startQ1Process();
			}
		}

		void startQ1Process()
		{
			while(q1.size()!=0)
			{
				checker1+=1;
				int con=0;
				if(pro[Var1].burstTime==0)
				{
					for(int i=0;i<q1.size();i++)
					{
						if(q1.at(i)==pro[Var1].processID)
						{
							Indef=i;
						}
					}
					q1.erase(std::remove(q1.begin(),q1.end(),q1.at(Indef)),q1.end());
					PrioritySelector.erase(PrioritySelector.begin()+Indef,PrioritySelector.begin()+(Indef+1));
					checker=1;
					if(q1.size()==0)
					{
						checker1=0;
						checker=0;
						break;
					}
					processSelector();
				}
				if(cTsetter==0)
				{
					pro[Var1].completion_time=pro[Var1].arrivalTime;
					cTsetter=1;
				}
				else
				{
					pro[Var1].completion_time=Timer;
				}
				pro[Var1].burstTime-=1;
				pro[Var1].completion_time+=1;
				Timer=pro[Var1].completion_time;
				for(int i=0;i<NoProcess;i++)
				{
					if(Timer==pro[i].arrivalTime)
					{
						q1.push_back(pro[i].processID);
						PrioritySelector.push_back(pro[i].Priority);
						con=1;
					}
				}
				if(con==1)
				{
					processSelector();
				}
			}
			if(q2.size()!=0)
			{
				startQ2process();
			}
		}

		void startQ2process()
		{
			int TQ=2,index2;
			string pI,preprocess;
			pI=q2.at(0);
			index2=findIndex(NoProcess,pI,pro);
			while(q2.size()!=0)
			{
				pro[index2].completion_time=Timer;
				if(pro[index2].burstTime==1)
				{
					pro[index2].burstTime=1;
					pro[index2].completion_time+=1;
				}
				else
				{
					pro[index2].burstTime-=TQ;
					pro[index2].completion_time+=TQ;
				}
				Timer=pro[index2].completion_time;
				if(pro[index2].burstTime==0)
				{
					q2.erase(std::remove(q2.begin(),q2.end(),pro[index2].processID),q2.end());
				}
				else
				{
					preprocess=pro[index2].processID;
					q2.erase(std::remove(q2.begin(),q2.end(),pro[index2].processID),q2.end());
					q2.push_back(preprocess);
				}
				for(int i=0;i<NoProcess;i++)
				{
					if(Timer==pro[i].arrivalTime)
					{
						q1.push_back(pro[i].processID);
						PrioritySelector.push_back(pro[i].Priority);
					}
				}
				if(q1.size()!=0)
				{
					checker1=1;
					m=0;
					processSelector();
				}
				if(q2.size()==0)
				{
					break;
				}
				pI=q2.at(0);
				index2=findIndex(NoProcess,pI,pro);
			}
		}

		void check()
		{
			x=pro[0].arrivalTime;
			for(int i=0;i<NoProcess;i++)
			{
				if(pro[i].arrivalTime>x)
				{
					x=pro[i].arrivalTime;              // finding te maximum aT
				}
			}
			while(Timer<=x)
			{
				int cod=0;
				Timer++;
				for(int i=0;i<NoProcess;i++)
				{
					if(Timer==pro[i].arrivalTime)
					{
						q1.push_back(pro[i].processID);
						PrioritySelector.push_back(pro[i].Priority);
						cod=1;
					}
				}
				if(cod==1)
				{
					m=0;
					checker1=1;
					processSelector();
				}
			}
		}

		void display()
		{
			cout<<"  Data set given by User"<<endl;
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
			cout<<"  |  ProcessID \t\t\tArrival Time\t\t\tBurst Time\t\t\tPriority        |"<<endl;
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
			for(int i=0;i<NoProcess;i++)
			{
				cout<<"  |  "<<pro[i].processID<<"\t\t\t\t"<<pro[i].arrivalTime<<"\t\t\t\t"<<pro[i].burstTime<<"\t\t\t\t"<<pro[i].Priority<<"\t        |"<<endl;
			}
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl<<endl;
		}

		void finalResult()
		{
			float avgwT=0;
			cout<<"  +*************************************************************************************************************+"<<endl;
			cout<<"  |\t\t\t\t\tFinal result  timing table of processes\t\t\t\t\t        |"<<endl;
			cout<<"  +*************************************************************************************************************+"<<endl;
			cout<<"  |  PId"<<"\t||\t"<<"AT"<<"\t||\t"<<"BT"<<"\t||\t"<<"CT"<<"\t||\t"<<"TAT"<<"\t||\t  "<<"WT"<<"\t\t        |"<<endl;
			cout<<"  +*************************************************************************************************************+"<<endl;
			for(int i=0;i<NoProcess;i++)
			{
				pro[i].TAT=pro[i].completion_time-pro[i].arrivalTime;
				pro[i].waitingTime=pro[i].TAT-pro[i].copy_bT;
				avgwT+=pro[i].waitingTime;
				cout<<"  |  "<<pro[i].processID<<"\t\t||\t"<<pro[i].arrivalTime<<"\t||\t"<<pro[i].copy_bT<<"\t||\t"<<pro[i].completion_time<<"\t||\t"<<pro[i].TAT<<"\t||\t  "<<pro[i].waitingTime<<"\t\t        |"<<endl;
				cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
			}
			cout<<"  |\t\t\t\t\tAverage waiting time : "<<avgwT/NoProcess<<"\t\t\t\t\t\t|"<<endl;
			cout<<"  +-------------------------------------------------------------------------------------------------------------+"<<endl;
		}
};
int main()
{
	Scheduling sc;
	sc.getData();
	sc.display();
	sc.findMinInArrivalTime();
	sc.processSelector();
	sc.startQ1Process();
	sc.check();
	sc.finalResult();
}
int findMin(pros pro[], int NoProcess)
{
    int mn=pro[0].arrivalTime;
    for(int i=0;i<NoProcess;i++)
	{
        int temp=pro[i].arrivalTime;
        mn=std::min(mn,temp);
    }
    return mn;
}
int findIndex(int NoProcess,string pI,pros pro[])
{
	int in;
	for(int i=0;i<NoProcess;i++)

    if(pI==pro[i].processID)
		{
			in=i;
		}
	}
	return in;

