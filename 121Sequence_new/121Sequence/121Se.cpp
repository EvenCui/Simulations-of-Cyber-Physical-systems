using namespace std;
#define M0 4
#define nodes_number 50
#define M 2
#define zhishu 1
#define redun 0.4
#include<iostream>
#include"Plist.h"
#include"time.h"
#include"math.h"
#include<fstream>
///////////////////////////////////////////////////////BA网络生成函数////////////////////////////////////////////
void BAGenerate(int(&node)[nodes_number], int(&link)[nodes_number][nodes_number], int(&nodedegree)[nodes_number])
{
	for (int i = 0; i < M0; i++)
	{
		node[i] = 1;
	}
	for (int i = 0; i < M0; i++)
	{
		for (int j = 0; j < i; j++)
		{
			link[i][j] = 1;
			nodedegree[i]++;
			nodedegree[j]++;
		}
	}
	int totaldegree = 0;
	for (int i = 0; i < M0; i++)
	{
		totaldegree = totaldegree + nodedegree[i];
	}
	//开始加入新节点///////////////////////////////////////////////////
	for (int i = M0; i < nodes_number; i++)
	{
		double lp[nodes_number] = { 0 };
		for (int mm = 0; mm < i; mm++)
		{
			int untotal = 0;
			for (int ss = 0; ss <= mm; ss++)
			{
				untotal = untotal + nodedegree[ss];
			}
			lp[mm] = (double)untotal / totaldegree;
		}
		for (int mm = 0; mm < M; mm++)
		{
			double random = (double)rand() / (RAND_MAX + 1.0);
			int select = 0;
			while (lp[select] < random)
			{
				select++;
			}
			if (link[i][select] == 0)
			{
				link[i][select] = 1;
				nodedegree[i]++;
				nodedegree[select]++;
			}
			else
				mm = mm - 1;
		}
		node[i] = 1;
		totaldegree = totaldegree + 2 * M;
	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////

void Load_sim_Del(Plist<int> &dellist, int(&node)[nodes_number], int(&link)[nodes_number][nodes_number], Plist<int> &nodelist, double(&capacity)[nodes_number])
{

	///////////////////////////////////////////////移除节点自身/////////////////////////////
	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
		node[dellist.refer->data] = 0;

	}
	//////////////////////////////////////////////在节点链表中删除节点/////////////////////////

	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
		for (nodelist.refer = nodelist.head; nodelist.refer != NULL; nodelist.refer = nodelist.refer->next)
		{
			if (dellist.refer->data == nodelist.refer->data)
			{
				nodelist.del(nodelist.refer);
				break;
			}
		}
	}

	/*for (nodelist.refer = nodelist.head; nodelist.refer != NULL; nodelist.refer = nodelist.refer->next)
	{
	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
	if (nodelist.refer->data == dellist.refer->data)
	{
	nodelist.refer1 = nodelist.refer;
	if (nodelist.refer == nodelist.head)
	{
	nodelist.del(nodelist.refer1);
	nodelist.refer = nodelist.head;
	}
	else
	{
	nodelist.refer = nodelist.refer->prev;
	nodelist.del(nodelist.refer1);
	}

	}
	}


	}*/
	///////////////////////////////////////////// 负载重分配///////////////////////////////////////
	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
		Plist<int> delnolin = Plist<int>();//////////////////节点的临接节点
		for (int i = 0; i < nodes_number; i++)
		{
			if ((link[dellist.refer->data][i] == 1) && node[i] == 1)
			{
				delnolin.insert(i);
			}
		}
		double totalca = 0;
		for (delnolin.refer = delnolin.head; delnolin.refer != NULL; delnolin.refer = delnolin.refer->next)
		{
			totalca = totalca + capacity[delnolin.refer->data];
		}
		for (delnolin.refer = delnolin.head; delnolin.refer != NULL; delnolin.refer = delnolin.refer->next)
		{
			capacity[delnolin.refer->data] = capacity[delnolin.refer->data] + capacity[delnolin.refer->data] * capacity[dellist.refer->data] / totalca;
		}
	}
	//////////////////////////////////////////////负载重分配结束，开始删除相关的边///////////////////////
	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
		for (int i = 0; i < nodes_number; i++)
		{
			//////////////////////////删除网络内相关的边///////////////////////////////////
			link[dellist.refer->data][i] = 0;
			link[i][dellist.refer->data] = 0;
			//////////////////////////////删除网络间的依赖边///////////////////////////////

		}

	}



	////////////////////////////////////////////////////////////////程序结束/////////////////////////////////////////////////
}

void load_BAG(int(&node)[nodes_number], int(&link)[nodes_number][nodes_number], int(&nodedegree)[nodes_number], double(&icapacity)[nodes_number], double(&tcapacity)[nodes_number])
{
	for (int i = 0; i < M0; i++)
	{
		node[i] = 1;
	}
	for (int i = 0; i < M0; i++)
	{
		for (int j = 0; j < i; j++)
		{
			link[i][j] = 1;
			link[j][i] = 1;
			nodedegree[i]++;
			nodedegree[j]++;
		}
	}
	int totaldegree = 0;
	for (int i = 0; i < M0; i++)
	{
		totaldegree = totaldegree + nodedegree[i];
	}
	//开始加入新节点///////////////////////////////////////////////////
	for (int i = M0; i < nodes_number; i++)
	{
		double lp[nodes_number] = { 0 };
		for (int mm = 0; mm < i; mm++)
		{
			int untotal = 0;
			for (int ss = 0; ss <= mm; ss++)
			{
				untotal = untotal + nodedegree[ss];
			}
			lp[mm] = (double)untotal / totaldegree;
		}
		for (int mm = 0; mm < M; mm++)
		{
			double random = (double)rand() / (RAND_MAX + 1.0);
			int select = 0;
			while (lp[select] < random)
			{
				select++;
			}
			if (link[i][select] == 0)
			{
				link[i][select] = 1;
				link[select][i] = 1;       // 问题出在这里    
				nodedegree[i]++;
				nodedegree[select]++;
			}
			else
				mm = mm - 1;
		}
		node[i] = 1;
		totaldegree = totaldegree + 2 * M;
	}

	//赋予节点capacity
	for (int i = 0; i < nodes_number; i++)
	{
		icapacity[i] = pow(nodedegree[i], zhishu);
		tcapacity[i] = (1 + redun)*icapacity[i];
	}

}

void BuildO2Osupportlinkd(int(&delinkl2r)[nodes_number], int(&delinkr2l)[nodes_number])
{
	Plist<int> rnode = Plist<int>();
	for (int i = 0; i < nodes_number; i++)
	{
		rnode.insert(i);
	}
	//开始一对一的随机匹配
	for (int i = 0; i < nodes_number; i++)
	{
		int randshu = rand() % (rnode.len );
		delinkl2r[i] = rnode.getAt(randshu);
		delinkr2l[rnode.getAt(randshu)] = i;
		//cout << "delete " << randshu << " total  " << rnode.len;
		rnode.del(randshu);
	}

}

//////////////////////////////////////////////////////////////删除节点函数///////////////////////////////////////////////////////////////////////////
void Del(int no, int(&node)[nodes_number], int(&link)[nodes_number][nodes_number], Plist<int> &nodelist)
{
	node[no] = 0;//移除节点自身
	for (nodelist.refer = nodelist.head; nodelist.refer != NULL; nodelist.refer = nodelist.refer->next)
	{
		if (nodelist.refer->data == no)
		{
			nodelist.del(nodelist.refer);
			break;
		}

	}
	//删除网络中与节点依赖的边
	for (int i = 0; i < nodes_number; i++)
	{
		link[no][i] = 0;
		link[i][no] = 0;
	}
}
///////////////////////////////////////////////////////删除节点结束////////////////////////////////////////////////////////////////////////////////////

void DFS(int &no, int(&link)[nodes_number][nodes_number], int(&visited)[nodes_number], int(&giant)[nodes_number][nodes_number], int &giantnumber)
{
	//cout << "遍历第" << no << " 节点" << endl;
	visited[no] = 1;
	giantnumber++;
	for (int j = 0; j < nodes_number; j++)
	{
		if (link[no][j] == 1)
		{
			giant[no][j] = 1;
			if (visited[j] == 0)
			{
				DFS(j, link, visited, giant, giantnumber);
			}
		}
		if (link[j][no] == 1)
		{
			giant[j][no] = 1;
			if (visited[j] == 0)
			{
				DFS(j, link, visited, giant, giantnumber);
			}
		}
	}
}
//////////////////////////////////////////////////////////////初始化最大联通子图/////////////////////////////////////////////////////////////
void giantset(int(&link)[nodes_number][nodes_number], Plist<int> &node)
{
	int livenumber = node.len;//存活节点数
	int giantnumber = 0;//最大联通子图个数
	int giant[nodes_number][nodes_number] = { 0 };
	int visited[nodes_number] = { 0 };
	node.refer3 = node.head;
	while (node.refer3 != NULL)
	{
		if (visited[node.refer3->data] == 0)
		{
			int temnuber = 0;//当前求得的最大联通子图个数；
			int temp[nodes_number][nodes_number] = { 0 };//当前的联通子图
			DFS(node.refer3->data, link, visited, temp, temnuber);
			if (temnuber>giantnumber)
			{
				giantnumber = temnuber;
				memcpy(giant, temp, sizeof(int)*nodes_number*nodes_number);
			}
		}
		node.refer3 = node.refer3->next;

	}
	livenumber = giantnumber;
	memcpy(link, giant, sizeof(int)*nodes_number*nodes_number);
	/*
	cout << "zuidaliantongzituwei" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
	for (int j = 0; j < i; j++)
	{
	cout << link[i][j] << " ";
	}
	cout << endl;
	}
	*/

}
bool judpo(int &no, int(&link)[nodes_number][nodes_number])
{
	bool res = false;
	for (int j = 0; j < nodes_number; j++)
	{
		if (link[no][j] == 1 || link[j][no] == 1)
		{
			res = true;
		}
	}
	return res;
}

int main()
{
	int seq_number = 0;//总的序列攻击占优数
	int sim_number = 0;//总的共识攻击占优数
	int rightseq_number = 0; //负载网络序列攻击占优总数
	int rightsim_number = 0;//负载网络共时攻击占优总数
	srand(time(NULL));
	Plist<int> leftnode = Plist<int>();//左侧存活节点链表；
	Plist<int> rightnode = Plist<int>();//右侧存活节点链表；
	double Del_sequence_result[nodes_number][nodes_number] = { 0 };
	double Del_sim_result[nodes_number][nodes_number] = { 0 };
	double right_Del_sequence_result[nodes_number][nodes_number] = { 0 };
	double right_Del_sim_result[nodes_number][nodes_number] = { 0 };
	int nodeleft[nodes_number] = { 0 }; //存储左侧网络中节点状态
	int noderight[nodes_number] = { 0 }; //存储右侧网络中节点状态
	int leftlink[nodes_number][nodes_number] = { 0 };//存储左侧网络中边状态
	int rightlink[nodes_number][nodes_number] = { 0 };//存储右侧网络中边状态
	int deplinkl2r[nodes_number] = { 0 };//一对一的依赖边
	int deplinkr2l[nodes_number] = { 0 };//一对一的依赖边
	int leftdegree[nodes_number] = { 0 };//左侧度
	int rightdegree[nodes_number] = { 0 };//右侧度
	double inicapacity[nodes_number] = { 0 };//右侧网络初始负载
	double trecapacity[nodes_number] = { 0 };//右侧网络负载阀值
	BAGenerate(nodeleft, leftlink, leftdegree);//生成左侧网络；
	load_BAG(noderight, rightlink, rightdegree, inicapacity, trecapacity);
	BuildO2Osupportlinkd(deplinkl2r, deplinkr2l);
	////////////////////////////////////////////////////////////初始化网络中节点链表////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		leftnode.insert(i);
		rightnode.insert(i);
	}
	////////////////////////////////////////////////////在右侧网络中同时删除两个节点////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (i == j)
			{
				Del_sim_result[i][j] = 1;
			}
			else
			{
				///////////////////////////首先赋值一个网络//////////////////////////////
				int Tnoderight[nodes_number] = { 0 };
				int Trightlink[nodes_number][nodes_number] = { 0 };
				int Trightdegree[nodes_number] = { 0 };
				double Tinicapacity[nodes_number] = { 0 };
				double Tthrecapacity[nodes_number] = { 0 };
				Plist<int> Trightnode = Plist<int>();
				Trightnode = rightnode;
				for (int counti = 0; counti < nodes_number; counti++)
				{
					Tnoderight[counti] = noderight[counti];
					Trightdegree[counti] = rightdegree[counti];
					Tinicapacity[counti] = inicapacity[counti];
					Tthrecapacity[counti] = trecapacity[counti];
					for (int countj = 0; countj < nodes_number; countj++)
					{
						Trightlink[counti][countj] = rightlink[counti][countj];
					}
				}

				Plist<int> dlist = Plist<int>();
				dlist.insert(i);
				dlist.insert(j);
				Load_sim_Del(dlist, Tnoderight, Trightlink, Trightnode,Tinicapacity);
				bool changetag = true;
				while (changetag)
				{
					changetag = false;
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();///////////////////////用以存储本次过载节点//////////////////////////
					while (Trightnode.refer != NULL)
					{
						if (Tinicapacity[Trightnode.refer->data] > Tthrecapacity[Trightnode.refer->data])
						{
							changetag = true;
							zandel.insert(Trightnode.refer->data);
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel.head != NULL)
					{
						Load_sim_Del(zandel, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel.~Plist();

				}
				right_Del_sim_result[i][j] = (double)Trightnode.len / rightnode.len;
				dlist.~Plist();
				Trightnode.~Plist();


			}
		}
	}
	//同时删除单个网络过程结束//////////////////////////////////////////////////////////
	cout << "state1" << endl;
	/////////////////////////////////////////////////开始顺序删除单个网络内节点/////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (i == j)
			{
				Del_sim_result[i][j] = 1;
			}
			else
			{
				///////////////////////////首先赋值一个网络//////////////////////////////
				int Tnoderight[nodes_number] = { 0 };
				int Trightlink[nodes_number][nodes_number] = { 0 };
				int Trightdegree[nodes_number] = { 0 };
				double Tinicapacity[nodes_number] = { 0 };
				double Tthrecapacity[nodes_number] = { 0 };
				Plist<int> Trightnode = Plist<int>();
				Trightnode = rightnode;
				for (int counti = 0; counti < nodes_number; counti++)
				{
					Tnoderight[counti] = noderight[counti];
					Trightdegree[counti] = rightdegree[counti];
					Tinicapacity[counti] = inicapacity[counti];
					Tthrecapacity[counti] = trecapacity[counti];
					for (int countj = 0; countj < nodes_number; countj++)
					{
						Trightlink[counti][countj] = rightlink[counti][countj];
					}
				}
				///////////////////删除第一个节点/////////////////////////////
				Plist<int> dlist = Plist<int>();
				dlist.insert(i);
				Load_sim_Del(dlist, Tnoderight, Trightlink, Trightnode, Tinicapacity);
				bool changetag = true;
				while (changetag)
				{
					changetag = false;
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();///////////////////////用以存储本次过载节点//////////////////////////
					while (Trightnode.refer != NULL)
					{
						if (Tinicapacity[Trightnode.refer->data] > Tthrecapacity[Trightnode.refer->data])
						{
							changetag = true;
							zandel.insert(Trightnode.refer->data);
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel.head != NULL)
					{
						Load_sim_Del(zandel, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel.~Plist();

				}
				dlist.~Plist();
				////////////////////////////////删除第二个节点///////////////////////////////
				Plist<int> dlist1 = Plist<int>();
				dlist1.insert(j);
				Load_sim_Del(dlist1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
				changetag = true;
				while (changetag)
				{
					changetag = false;
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();///////////////////////用以存储本次过载节点//////////////////////////
					while (Trightnode.refer != NULL)
					{
						if (Tinicapacity[Trightnode.refer->data] > Tthrecapacity[Trightnode.refer->data])
						{
							changetag = true;
							zandel.insert(Trightnode.refer->data);
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel.head != NULL)
					{
						Load_sim_Del(zandel, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel.~Plist();

				}
				dlist1.~Plist();
				right_Del_sequence_result[i][j] = (double)Trightnode.len / rightnode.len;
				Trightnode.~Plist();


			}
		}
	}
	////////////////////////////////////////////////////////顺序删除单个网络内的节点结束/////////////////////////////////////

	///////////////////////////////////////////////////////同时删除相依网络中的两个节点/////////////////////////////////////
	
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (i == j)
			{
				Del_sim_result[i][j] = 1;
			}
			else
			{
				///////////////////////////首先赋值一相依个网络//////////////////////////////
				int Tnodeleft[nodes_number] = { 0 };
				int Tnoderight[nodes_number] = { 0 };
				int Tleftlink[nodes_number][nodes_number] = { 0 };
				int Trightlink[nodes_number][nodes_number] = { 0 };
				int Tleftdegree[nodes_number] = { 0 };
				int Trightdegree[nodes_number] = { 0 };
				double Tinicapacity[nodes_number] = { 0 };
				double Tthrecapacity[nodes_number] = { 0 };
				Plist<int> Tleftnode = Plist<int>();
				Plist<int> Trightnode = Plist<int>();
				Tleftnode = leftnode;
				Trightnode = rightnode;
				for (int counti = 0; counti < nodes_number; counti++)
				{
					Tnodeleft[counti] = nodeleft[counti];
					Tnoderight[counti] = noderight[counti];
					Tleftdegree[counti] = leftdegree[counti];
					Trightdegree[counti] = rightdegree[counti];
					Tinicapacity[counti] = inicapacity[counti];
					Tthrecapacity[counti] = trecapacity[counti];
					for (int countj = 0; countj < nodes_number; countj++)
					{
						Trightlink[counti][countj] = rightlink[counti][countj];
						Tleftlink[counti][countj] = leftlink[counti][countj];
					}
				}
				///////////////////////////////开始删除节点/////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////左侧网络中是否存在不属于最大联通子图的点/////
					while (Tleftnode.refer != NULL)
					{
						if (!judpo(Tleftnode.refer->data, Tleftlink))
						{
							alltag = true;
							if (Tleftnode.refer == leftnode.head)
							{
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, leftnode);
								Tleftnode.refer = Tleftnode.head;
							}
							else
							{
								Tleftnode.refer2 = Tleftnode.refer->next;
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, Tleftnode);
								Tleftnode.refer = Tleftnode.refer2;
							}
						}
						else
						{
							Tleftnode.refer = Tleftnode.refer->next;
						}
					}
					///////////////////////////////////////////左侧网络中是否存在依赖不足的节点//////////////
					Tleftnode.refer = Tleftnode.head;
					while (Tleftnode.refer != NULL)
					{
						if (Tnoderight[deplinkl2r[Tleftnode.refer->data]] == 0)
						{
							alltag = true;
							if (Tleftnode.refer == leftnode.head)
							{
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, leftnode);
								Tleftnode.refer = Tleftnode.head;
							}
							else
							{
								Tleftnode.refer2 = Tleftnode.refer->next;
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, Tleftnode);
								Tleftnode.refer = Tleftnode.refer2;
							}

						}
						else
						{
							Tleftnode.refer = Tleftnode.refer->next;
						}
					}
					///////////////////右侧网络是否存在过载的节点/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////用以存储左侧网络中过载节点
					while (Trightnode.refer != NULL)
					{
						if (Tinicapacity[Trightnode.refer->data] > Tthrecapacity[Trightnode.refer->data])
						{
							alltag = true;
							zandel.insert(Trightnode.refer->data);
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel.head != NULL)
					{
						Load_sim_Del(zandel, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel.~Plist();
					////////////////////右侧网络中是否存在无依赖的节点////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "过载" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Del_sim_result[i][j] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();


			}
		}
	}

	//////////////////////////////////////////顺序删除两个相依节点//////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (i == j)
			{
				Del_sequence_result[i][j] = 1;
			}
			else
			{
				///////////////////////////首先赋值一相依个网络//////////////////////////////
				int Tnodeleft[nodes_number] = { 0 };
				int Tnoderight[nodes_number] = { 0 };
				int Tleftlink[nodes_number][nodes_number] = { 0 };
				int Trightlink[nodes_number][nodes_number] = { 0 };
				int Tleftdegree[nodes_number] = { 0 };
				int Trightdegree[nodes_number] = { 0 };
				double Tinicapacity[nodes_number] = { 0 };
				double Tthrecapacity[nodes_number] = { 0 };
				Plist<int> Tleftnode = Plist<int>();
				Plist<int> Trightnode = Plist<int>();
				Tleftnode = leftnode;
				Trightnode = rightnode;
				for (int counti = 0; counti < nodes_number; counti++)
				{
					Tnodeleft[counti] = nodeleft[counti];
					Tnoderight[counti] = noderight[counti];
					Tleftdegree[counti] = leftdegree[counti];
					Trightdegree[counti] = rightdegree[counti];
					Tinicapacity[counti] = inicapacity[counti];
					Tthrecapacity[counti] = trecapacity[counti];
					for (int countj = 0; countj < nodes_number; countj++)
					{
						Trightlink[counti][countj] = rightlink[counti][countj];
						Tleftlink[counti][countj] = leftlink[counti][countj];
					}
				}
				///////////////////////////////开始删除第一个节点/////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////左侧网络中是否存在不属于最大联通子图的点/////
					while (Tleftnode.refer != NULL)
					{
						if (!judpo(Tleftnode.refer->data, Tleftlink))
						{
							alltag = true;
							if (Tleftnode.refer == leftnode.head)
							{
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, leftnode);
								Tleftnode.refer = Tleftnode.head;
							}
							else
							{
								Tleftnode.refer2 = Tleftnode.refer->next;
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, Tleftnode);
								Tleftnode.refer = Tleftnode.refer2;
							}
						}
						else
						{
							Tleftnode.refer = Tleftnode.refer->next;
						}
					}
					///////////////////////////////////////////左侧网络中是否存在依赖不足的节点//////////////
					Tleftnode.refer = Tleftnode.head;
					while (Tleftnode.refer != NULL)
					{
						if (Tnoderight[deplinkl2r[Tleftnode.refer->data]] == 0)
						{
							alltag = true;
							if (Tleftnode.refer == leftnode.head)
							{
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, leftnode);
								Tleftnode.refer = Tleftnode.head;
							}
							else
							{
								Tleftnode.refer2 = Tleftnode.refer->next;
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, Tleftnode);
								Tleftnode.refer = Tleftnode.refer2;
							}

						}
						else
						{
							Tleftnode.refer = Tleftnode.refer->next;
						}
					}
					///////////////////右侧网络是否存在过载的节点/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////用以存储左侧网络中过载节点
					while (Trightnode.refer != NULL)
					{
						if (Tinicapacity[Trightnode.refer->data] > Tthrecapacity[Trightnode.refer->data])
						{
							alltag = true;
							zandel.insert(Trightnode.refer->data);
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel.head != NULL)
					{
						Load_sim_Del(zandel, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel.~Plist();
					////////////////////右侧网络中是否存在无依赖的节点////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "过载" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////////////开始删除第二个节点////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////左侧网络中是否存在不属于最大联通子图的点/////
					while (Tleftnode.refer != NULL)
					{
						if (!judpo(Tleftnode.refer->data, Tleftlink))
						{
							alltag = true;
							if (Tleftnode.refer == leftnode.head)
							{
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, leftnode);
								Tleftnode.refer = Tleftnode.head;
							}
							else
							{
								Tleftnode.refer2 = Tleftnode.refer->next;
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, Tleftnode);
								Tleftnode.refer = Tleftnode.refer2;
							}
						}
						else
						{
							Tleftnode.refer = Tleftnode.refer->next;
						}
					}
					///////////////////////////////////////////左侧网络中是否存在依赖不足的节点//////////////
					Tleftnode.refer = Tleftnode.head;
					while (Tleftnode.refer != NULL)
					{
						if (Tnoderight[deplinkl2r[Tleftnode.refer->data]] == 0)
						{
							alltag = true;
							if (Tleftnode.refer == leftnode.head)
							{
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, leftnode);
								Tleftnode.refer = Tleftnode.head;
							}
							else
							{
								Tleftnode.refer2 = Tleftnode.refer->next;
								Del(Tleftnode.refer->data, Tnodeleft, Tleftlink, Tleftnode);
								Tleftnode.refer = Tleftnode.refer2;
							}

						}
						else
						{
							Tleftnode.refer = Tleftnode.refer->next;
						}
					}
					///////////////////右侧网络是否存在过载的节点/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////用以存储左侧网络中过载节点
					while (Trightnode.refer != NULL)
					{
						if (Tinicapacity[Trightnode.refer->data] > Tthrecapacity[Trightnode.refer->data])
						{
							alltag = true;
							zandel.insert(Trightnode.refer->data);
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel.head != NULL)
					{
						Load_sim_Del(zandel, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel.~Plist();
					////////////////////右侧网络中是否存在无依赖的节点////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "过载" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////计算结束///////////////////////////////////////////////
				Del_sequence_result[i][j] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();


			}
		}
	}










	cout << "helloworld" << endl;






	////////////////////////////////////结果输出/////////////////////////////////////////////
	/**/
	ofstream fout("single.txt");
	cout << endl;
	fout << "单个网络输出对比结果：序列攻击优于共时攻击" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (right_Del_sim_result[i][j] > right_Del_sequence_result[i][j])
			{
				fout << "result: " << i << "  " << j << "   sim: " << right_Del_sim_result[i][j] << "  sequence: " << right_Del_sequence_result[i][j]<< endl;
				rightseq_number = rightseq_number + 1;
			}
		}
	}
	fout << endl;
	fout << "单个网络输出对比结果：共时攻击优于序列攻击" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (right_Del_sequence_result[i][j] > right_Del_sim_result[i][j])
			{
				fout << "result: " << i << "  " << j << "   sim: " << right_Del_sim_result[i][j] << "  sequence: " << right_Del_sequence_result[i][j] << endl;
				rightsim_number = rightsim_number + 1;
			}
		}
	}
	fout.close();

	ofstream fout1("interdependent.txt");
	fout1 << endl;
	fout1 << "相依网络输出对比结果：序列攻击优于共时攻击" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (Del_sim_result[i][j] > Del_sequence_result[i][j])
			{
				fout1 << "result: " << i << "  " << j << "   sim: " << Del_sim_result[i][j] << "  sequence: " << Del_sequence_result[i][j] << endl;
				seq_number = seq_number + 1;
			}
		}
	}
	fout1 << endl;
	fout1 << "相依网络输出对比结果：共时攻击优于序列攻击" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (Del_sequence_result[i][j] > Del_sim_result[i][j])
			{
				fout1 << "result: " << i << "  " << j << "   sim: " << Del_sim_result[i][j] << "  sequence: " << Del_sequence_result[i][j] << endl;
				sim_number = sim_number + 1;
			}
		}
	}
	fout1.close();
	//////////////////////////////////////输出相依网络结构//////////////////////////////////
	ofstream fout2("struct.txt");
	fout2 << "相依结构" << endl;
	for(int i = 0; i < nodes_number; i++)
	{
		fout2 << i << "  " << deplinkl2r[i] << endl;
	}
	fout2.close();
	////////////////////////////////////信息网和物理网络络结构////////////////////////////////////
	ofstream fout3("structCP.txt");
	fout3 << "信息网络相依结构" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i+1; j < nodes_number; j++)
		{
			fout3 << i << " " << j << "  " << leftlink[i][j] << endl;
		}
	}

	fout3 << "物理网络相依结构" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			fout3 << i << " " << j << "  " << rightlink[i][j] << endl;
		}
	}
	fout3.close();






	cout << "Program End" << endl;
	/*
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			cout << right_Del_sequence_result[i][j] << " ";
		}
		cout << endl;
	}
	*/

	cout << "singgleSeq: " << rightseq_number << endl;
	cout << "singgleSim: " << rightsim_number << endl;
	cout << "interSeq:  " << seq_number << endl;
	cout << "interSim:  " << sim_number << endl;


	ofstream seqout("singleseq.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			seqout << right_Del_sequence_result[i][j] << endl;
		}
	}
	seqout.close();

	ofstream simout("singlesim.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			simout << right_Del_sim_result[i][j] << endl;
		}
	}
	simout.close();

	ofstream Iseqout("Interseq.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			Iseqout << Del_sequence_result[i][j] << endl;
		}
	}
	Iseqout.close();


	ofstream Isimout("Intersim.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			Isimout << Del_sim_result[i][j] << endl;
		}
	}
	Isimout.close();

	return 0;
}