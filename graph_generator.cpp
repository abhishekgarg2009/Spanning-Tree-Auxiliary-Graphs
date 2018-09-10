#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <cstring>
#include <set>
using namespace std;
struct disjoint
{
	long long rank;
	long long par;
}arr[1000006];
void makeset(long long x)
{
	arr[x].par = x;
	arr[x].rank = 0;
}
long long find(long long x)
{
	long long temp = arr[x].par;
	if(temp!=x)
	{
		temp = find(arr[x].par);
	}
	return temp;
}
/*void union1(long long x,long long y)
{
	long long xroot = find(x);
	long long yroot = find(y);
	if(xroot==yroot)
		return;
	if(arr[xroot].rank < arr[yroot].rank)
		arr[xroot].par = yroot;
	else if(a[xroot].rank > arr[yroot].rank)
		arr[yroot].par = xroot;
	else
	{
		arr[yroot].par = xroot;
		arr[xroot].rank = arr[xroot].rank+1;
	}
}*/
vector<pair<long long,long long> > ed;
vector<pair<long long,long long> > new_ed;
vector<pair<long long,long long> > temp_ed;
int ma[1000006]={0};
int ver[1000006]={0};
int temp_ma[1000006]={0};
vector<long long> aux_graph[1000006];
vector<long long> maxi_cq[1000006];
set<long long> aux_cq[1000006]; //stores clqiues for each node in aux graph;
vector<long long> aux_all_cq[1000006];
vector<long long> temp_cq;
vector<long long> vertex_adj;
int vertex_adj_mat[1000006]={0};
int adj_aux[1003][1003];
int temp_adj_aux[1003][1003];
long long count1,n,m;
long long count2;
long long tot_full_cliques,max_cq_size,temp_size;
set< vector<long long> > clique_set;
void func(long long index, long long num)
{
	//cout<<"index: "<<index<<"\n";
	//cout<<"num : "<<num<<"\n";
	if(num==(n-1))
	{
		count1++;
		for(long long i=1;i<=m;i++)
		{
			if(ma[i]==1)
			{
				aux_graph[count1].push_back(i);
			}
			if(aux_graph[count1].size()==(n-1))
			{
				return;
			}
		}
		return;
	}
	if(index>m)
	{
		return;
	}
	pair<long long,long long> pi;
	pi = ed[index-1];
	//cout<<"\n";
	//cout<<"pi.first: "<<pi.first<<"\n";
	//cout<<"ver[pi.first]: "<<ver[pi.first]<<"\n";
	//cout<<"pi.second: "<<pi.second<<"\n";
	//cout<<"ver[pi.second]: "<<ver[pi.second]<<"\n";
	long long temp1,temp2,temp3,temp4;
	temp3 = find(pi.first);
	temp4 = find(pi.second);
	if(temp3!=temp4)
	{
		ver[pi.first]++;
		ver[pi.second]++;
		ma[index]=1;
		temp1 = min(temp3,temp4);
		temp2 = max(temp3,temp4);
		arr[temp2].par=temp1;
		func(index+1,num+1);
		arr[temp2].par=temp2;
		ma[index]=0;
		ver[pi.second]--;
		ver[pi.first]--;
	}
	func(index+1,num);
}
/*void clique(long long index)
{
	if(index>count1)
	{
		if(temp_cq.size()>2)
		{
			count2++;
			for(long long i=0;i<temp_cq.size();i++)
			{
				maxi_cq[count2].push_back(temp_cq[i]);
			}
		}
		return;
	}
	int flag2=1;
	for(long long i=0;i<temp_cq.size();i++)
	{
		if(adj_aux[index][temp_cq[i]]==0)
		{
			flag2=0;
			break;
		}
	}
	if(flag2==1)
	{
		temp_cq.push_back(index);
		clique(index+1);
		temp_cq.pop_back(index);
	}
	clique(index+1);
}*/
void addClique(long long node)
{
	memset(temp_adj_aux,0,sizeof(temp_adj_aux));
	memset(vertex_adj_mat,0,sizeof(vertex_adj_mat));
	temp_ed.clear();
	vertex_adj.clear();
	for(long long i=0;i<new_ed.size();i++)
	{
		if(new_ed[i].first==node)
		{
			vertex_adj_mat[new_ed[i].second]=1;
			vertex_adj.push_back(new_ed[i].second);
		}
		if(new_ed[i].second==node)
		{
			vertex_adj_mat[new_ed[i].first]=1;
			vertex_adj.push_back(new_ed[i].first);
		}
	}
	for(long long i=0;i<new_ed.size();i++)
	{
		if(vertex_adj_mat[new_ed[i].first]==1 && vertex_adj_mat[new_ed[i].second]==1)
		{
			temp_ed.push_back(new_ed[i]);
			temp_adj_aux[new_ed[i].first][new_ed[i].second]=1;
			temp_adj_aux[new_ed[i].second][new_ed[i].first]=1;
		}
	}
	for(long long i=1;i<=count1;i++)
	{
		temp_adj_aux[i][i]=1;
	}
	count2=0;
	long long count3,x,y;
	int flag3;
	memset(temp_ma,0,sizeof(temp_ma));
	memset(ma,0,sizeof(ma));
	for(long long i=0;i<temp_ed.size();i++)
	{
		if(temp_ma[i+1]==0)
		{
			//cout<<"i: "<<i<<"\n";
			count3=2;
			ma[temp_ed[i].first]=1;
			ma[temp_ed[i].second]=1;
			temp_cq.push_back(temp_ed[i].first);
			temp_cq.push_back(temp_ed[i].second);
			temp_ma[i+1]=1;
			for(long long j=i+1;j<temp_ed.size();j++)
			{
				x = temp_ed[j].first;
				y = temp_ed[j].second;
				flag3=1;
				for(long long k=0;k<temp_cq.size();k++)
				{
					//cout<<"temp_cq[k]: "<<temp_cq[k]<<"\n";
					if(temp_adj_aux[x][temp_cq[k]]==0 || temp_adj_aux[y][temp_cq[k]]==0)
					{
						flag3=0;
						break;
					}
				}
				if(flag3==1)
				{
					temp_ma[j+1]=1;
					if(ma[x]==0)
					{
						ma[x]=1;
						temp_cq.push_back(x);
						count3++;
					}
					if(ma[y]==0)
					{
						ma[y]=1;
						temp_cq.push_back(y);
						count3++;
					}
				}
			}
			count2++;
			temp_cq.push_back(node);
			sort(temp_cq.begin(),temp_cq.end());
			for(long long j=0;j<temp_cq.size();j++)
			{
				clique_set.insert(temp_cq);
				ma[temp_cq[j]]=0;
			}
			temp_cq.clear();
		}
	}
}
int main()
{
	long long a,b;
	pair<long long, long long> pi;
	cout<<"Enter number of vertices: \n";
	cin>>n;
	cout<<"Enter number of edges: \n";
	cin>>m;
	cout<<"Enter endpoint of "<<m<<" edges:\n";
	for(int i=0;i<m;i++)
	{
		cin>>a;
		cin>>b;
		pi.first = min(a,b);
		pi.second = max(a,b);
		ed.push_back(pi);
	}
	for(long long i=1;i<=n;i++)
	{
		makeset(i);
	}
	cout<<"The entered edges:\n";
	for(int i=0;i<ed.size();i++)
	{
		cout<<ed[i].first<<" "<<ed[i].second<<"\n";
	}
	count1=0;
	func(1,0);
	cout<<"Number of spanning trees: "<<count1<<"\n";
	int flag;
	for(long long i=1;i<=count1;i++)
	{
		for(long long j=i+1;j<=count1;j++)
		{
			flag=0;
			for(long long k=0;k<(n-1);k++)
			{
				temp_ma[aux_graph[i][k]]=1;
			}
			for(long long k=0;k<(n-1);k++)
			{
				if(temp_ma[aux_graph[j][k]]==0)
				{
					flag++;
				}
			}
			for(long long k=0;k<(n-1);k++)
			{
				temp_ma[aux_graph[i][k]]=0;
			}
			if(flag==1)
			{
				pi.first = i;
				pi.second = j;
				new_ed.push_back(pi);
			}
		}
	}
	memset(adj_aux,0,sizeof(adj_aux));
	memset(temp_adj_aux,0,sizeof(temp_adj_aux));
	memset(temp_ma,0,sizeof(temp_ma));
	memset(ma,0,sizeof(ma));
	cout<<"The edges of the auxilary graph : \n";
	for(long long i=0;i<new_ed.size();i++)
	{
		cout<<new_ed[i].first<<"   "<<new_ed[i].second<<"\n";
		if(new_ed[i].first==1)
		{
			vertex_adj_mat[new_ed[i].second]=1;
			vertex_adj.push_back(new_ed[i].second);
		}
		if(new_ed[i].second==1)
		{
			vertex_adj_mat[new_ed[i].first]=1;
			vertex_adj.push_back(new_ed[i].first);
		}
		adj_aux[new_ed[i].first][new_ed[i].second]=1;
		adj_aux[new_ed[i].second][new_ed[i].first]=1;
		temp_ma[new_ed[i].first]++;
		temp_ma[new_ed[i].second]++;
	}
	cout<<"Degree sequence: \n";
	for(int i=1;i<=count1;i++)
	{
		cout<<"i: "<<i<<"   deg(i): "<<temp_ma[i]<<"\n";
		ma[temp_ma[i]]++;
	}
	cout<<"degree distribution: \n";
	for(int i=1;i<=count1;i++)
	{
		if(ma[i])
		{
			cout<<"degree: "<<i<<"   freq: "<<ma[i]<<"\n";
		}
	}
	for(long long i=0;i<new_ed.size();i++)
	{
		if(vertex_adj_mat[new_ed[i].first]==1 && vertex_adj_mat[new_ed[i].second]==1)
		{
			temp_ed.push_back(new_ed[i]);
			temp_adj_aux[new_ed[i].first][new_ed[i].second]=1;
			temp_adj_aux[new_ed[i].second][new_ed[i].first]=1;
		}
	}
	for(long long i=1;i<=count1;i++)
	{
		adj_aux[i][i]=1;
		temp_adj_aux[i][i]=1;
	}
	count2=0;
	//clique(1);
	long long count3,x,y;
	int flag3;
	memset(temp_ma,0,sizeof(temp_ma));
	memset(ma,0,sizeof(ma));
	for(long long i=0;i<temp_ed.size();i++)
	{
		if(temp_ma[i+1]==0)
		{
			//cout<<"i: "<<i<<"\n";
			count3=2;
			ma[temp_ed[i].first]=1;
			ma[temp_ed[i].second]=1;
			temp_cq.push_back(temp_ed[i].first);
			temp_cq.push_back(temp_ed[i].second);
			temp_ma[i+1]=1;
			for(long long j=i+1;j<temp_ed.size();j++)
			{
				x = temp_ed[j].first;
				y = temp_ed[j].second;
				flag3=1;
				for(long long k=0;k<temp_cq.size();k++)
				{
					//cout<<"temp_cq[k]: "<<temp_cq[k]<<"\n";
					if(temp_adj_aux[x][temp_cq[k]]==0 || temp_adj_aux[y][temp_cq[k]]==0)
					{
						flag3=0;
						break;
					}
				}
				if(flag3==1)
				{
					temp_ma[j+1]=1;
					if(ma[x]==0)
					{
						ma[x]=1;
						temp_cq.push_back(x);
						count3++;
					}
					if(ma[y]==0)
					{
						ma[y]=1;
						temp_cq.push_back(y);
						count3++;
					}
				}
			}
			count2++;
			for(long long j=0;j<temp_cq.size();j++)
			{
				maxi_cq[count2].push_back(temp_cq[j]);
				ma[temp_cq[j]]=0;
			}
			temp_cq.clear();
		}
	}
	cout<<"The maximal cliques in neighbourhood of 1:\n";
	for(long long i=1;i<=count2;i++)
	{
		cout<<"The number "<<i<<" clique: \n";
		for(long long j=0;j<maxi_cq[i].size();j++)
		{
			cout<<maxi_cq[i][j]<<" ";
		}
		cout<<"\n";
	}
	for(int i=1;i<=count1;i++)
	{
		addClique(i);
	}
	set< vector<long long> >::iterator it;
	cout<<"All cliques: \n";
	tot_full_cliques=0;
	memset(ma,0,sizeof(ma));
	memset(temp_ma,0,sizeof(temp_ma));
	max_cq_size=0;
	for(it = clique_set.begin(); it!=clique_set.end(); it++)
	{
		temp_cq = (*it);
		tot_full_cliques++;
		temp_size = temp_cq.size();
		for(long long j=0;j<temp_cq.size();j++)
		{
			cout<<temp_cq[j]<<" ";
			temp_ma[temp_cq[j]]++;
			aux_cq[temp_cq[j]].insert(temp_size);
			aux_all_cq[temp_cq[j]].push_back(temp_size);
		}
		ma[temp_size]++;
		max_cq_size=max(max_cq_size,temp_size);
		cout<<"\n";
	}
	cout<<"Total full cliques : "<<tot_full_cliques<<"\n";
	cout<<"Clique sizes with freq: \n";
	for(long long i=1;i<=max_cq_size;i++)
	{
		if(ma[i])
		{
			cout<<"clique size : "<<i<<"  freq: "<<ma[i]<<"\n";
		}
	}
	cout<<"Occurence of each node in Cliques: \n";
	set<long long>::iterator it1;
	for(long long i=1;i<=count1;i++)
	{
		cout<<"Node i : "<<i<<"   occurs : "<<temp_ma[i]<<" times\n";
		cout<<"All clique sizes: \n";
		for(long long j=0;j<aux_all_cq[i].size();j++)
		{
			cout<<aux_all_cq[i][j]<<" ";
		}
		/*cout<<"Here are different size of cliques:\n";
		for(it1=aux_cq[i].begin(); it1!=aux_cq[i].end();it1++)
		{
			temp_size = (*it1);
			cout<<temp_size<<" ";
		}*/
		cout<<"\n";
	}
	return 0;
}