using namespace std;
#define M0 4
#define nodes_number 50
#define M 1
#define zhishu 1
#define redun 0.5
#include<iostream>
#include"Plist.h"
#include"time.h"
#include"math.h"
#include<fstream>
///////////////////////////////////////////////////////BA�������ɺ���////////////////////////////////////////////
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
	//��ʼ�����½ڵ�///////////////////////////////////////////////////
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

	///////////////////////////////////////////////�Ƴ��ڵ�����/////////////////////////////
	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
		node[dellist.refer->data] = 0;

	}
	//////////////////////////////////////////////�ڽڵ�������ɾ���ڵ�/////////////////////////

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
	///////////////////////////////////////////// �����ط���///////////////////////////////////////
	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
		Plist<int> delnolin = Plist<int>();//////////////////�ڵ���ٽӽڵ�
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
	//////////////////////////////////////////////�����ط����������ʼɾ����صı�///////////////////////
	for (dellist.refer = dellist.head; dellist.refer != NULL; dellist.refer = dellist.refer->next)
	{
		for (int i = 0; i < nodes_number; i++)
		{
			//////////////////////////ɾ����������صı�///////////////////////////////////
			link[dellist.refer->data][i] = 0;
			link[i][dellist.refer->data] = 0;
			//////////////////////////////ɾ��������������///////////////////////////////

		}

	}



	////////////////////////////////////////////////////////////////�������/////////////////////////////////////////////////
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
	//��ʼ�����½ڵ�///////////////////////////////////////////////////
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
				link[select][i] = 1;       // �����������    
				nodedegree[i]++;
				nodedegree[select]++;
			}
			else
				mm = mm - 1;
		}
		node[i] = 1;
		totaldegree = totaldegree + 2 * M;
	}

	//����ڵ�capacity
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
	//��ʼһ��һ�����ƥ��
	for (int i = 0; i < nodes_number; i++)
	{
		int randshu = rand() % (rnode.len);
		delinkl2r[i] = rnode.getAt(randshu);
		delinkr2l[rnode.getAt(randshu)] = i;
		//cout << "delete " << randshu << " total  " << rnode.len;
		rnode.del(randshu);
	}

}

//////////////////////////////////////////////////////////////ɾ���ڵ㺯��///////////////////////////////////////////////////////////////////////////
void Del(int no, int(&node)[nodes_number], int(&link)[nodes_number][nodes_number], Plist<int> &nodelist)
{
	node[no] = 0;//�Ƴ��ڵ�����
	for (nodelist.refer = nodelist.head; nodelist.refer != NULL; nodelist.refer = nodelist.refer->next)
	{
		if (nodelist.refer->data == no)
		{
			nodelist.del(nodelist.refer);
			break;
		}

	}
	//ɾ����������ڵ������ı�
	for (int i = 0; i < nodes_number; i++)
	{
		link[no][i] = 0;
		link[i][no] = 0;
	}
}
///////////////////////////////////////////////////////ɾ���ڵ����////////////////////////////////////////////////////////////////////////////////////

void DFS(int &no, int(&link)[nodes_number][nodes_number], int(&visited)[nodes_number], int(&giant)[nodes_number][nodes_number], int &giantnumber)
{
	//cout << "������" << no << " �ڵ�" << endl;
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
//////////////////////////////////////////////////////////////��ʼ�������ͨ��ͼ/////////////////////////////////////////////////////////////
void giantset(int(&link)[nodes_number][nodes_number], Plist<int> &node)
{
	int livenumber = node.len;//���ڵ���
	int giantnumber = 0;//�����ͨ��ͼ����
	int giant[nodes_number][nodes_number] = { 0 };
	int visited[nodes_number] = { 0 };
	node.refer3 = node.head;
	while (node.refer3 != NULL)
	{
		if (visited[node.refer3->data] == 0)
		{
			int temnuber = 0;//��ǰ��õ������ͨ��ͼ������
			int temp[nodes_number][nodes_number] = { 0 };//��ǰ����ͨ��ͼ
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
	double Result1[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result2[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result3[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result4[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result5[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result6[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result7[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result8[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result9[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result10[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result11[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result12[nodes_number][nodes_number][nodes_number] = { 0 };
	double Result13[nodes_number][nodes_number][nodes_number] = { 0 };
	srand(time(NULL));
	Plist<int> leftnode = Plist<int>();//�����ڵ�����
	Plist<int> rightnode = Plist<int>();//�Ҳ���ڵ�����
	int nodeleft[nodes_number] = { 0 }; //�洢��������нڵ�״̬
	int noderight[nodes_number] = { 0 }; //�洢�Ҳ������нڵ�״̬
	int leftlink[nodes_number][nodes_number] = { 0 };//�洢��������б�״̬
	int rightlink[nodes_number][nodes_number] = { 0 };//�洢�Ҳ������б�״̬
	int deplinkl2r[nodes_number] = { 0 };//һ��һ��������
	int deplinkr2l[nodes_number] = { 0 };//һ��һ��������
	int leftdegree[nodes_number] = { 0 };//����
	int rightdegree[nodes_number] = { 0 };//�Ҳ��
	double inicapacity[nodes_number] = { 0 };//�Ҳ������ʼ����
	double trecapacity[nodes_number] = { 0 };//�Ҳ����縺�ط�ֵ
	BAGenerate(nodeleft, leftlink, leftdegree);//����������磻
	load_BAG(noderight, rightlink, rightdegree, inicapacity, trecapacity);
	BuildO2Osupportlinkd(deplinkl2r, deplinkr2l);
	////////////////////////////////////////////////////////////��ʼ�������нڵ�����////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		leftnode.insert(i);
		rightnode.insert(i);
	}
	///////////////////////////////ͬʱɾ�������ڵ�i,j,k/////////////////////////////////
	cout << "����1��ʼ" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i+1; j < nodes_number; j++)
		{
			for (int k = j+1; k < nodes_number; k++)
			{
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
				///////////////////////////////��ʼɾ���ڵ�/////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Result1[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();

			}
		}
	}

	cout << "����1����������2��ʼ" << endl;
	/////////////////////////////////////////����1����////////////////////////////////////////////////
	////////////////////////////////////////����2��˳��ɾ��i,j,k/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				///////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				///////////////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////////////��ʼɾ���ڶ����ڵ�////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				/////////////////////////////////////////��ʼɾ���������ڵ�////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Result2[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();


			}
		}
	}
	cout << "����2����������3��ʼ" << endl;
	/////////////////////////////////////////����2����////////////////////////////////////////////////
	////////////////////////////////////////����3��˳��ɾ��i,k,j/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				///////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				///////////////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////////////��ʼɾ���ڶ����ڵ�////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				/////////////////////////////////////////��ʼɾ���������ڵ�////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Result3[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();








			}
		}
	}
	cout << "����3����������4��ʼ" << endl;
	/////////////////////////////////////////����3����////////////////////////////////////////////////
	////////////////////////////////////////����4��˳��ɾ��j,i,k/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				///////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				///////////////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////////////��ʼɾ���ڶ����ڵ�////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				/////////////////////////////////////////��ʼɾ���������ڵ�////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Result4[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();
			}
		}
	}
	cout << "����4����������5��ʼ" << endl;
	/////////////////////////////////////////����4����////////////////////////////////////////////////
	////////////////////////////////////////����5��˳��ɾ��j,k,i/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				///////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				///////////////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////////////��ʼɾ���ڶ����ڵ�////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				/////////////////////////////////////////��ʼɾ���������ڵ�////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Result5[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();
			}
		}
	}
	cout << "����5����������6��ʼ" << endl;
	/////////////////////////////////////////����5����////////////////////////////////////////////////
	////////////////////////////////////////����6��˳��ɾ��k,i,j/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				///////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				///////////////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////////////��ʼɾ���ڶ����ڵ�////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				/////////////////////////////////////////��ʼɾ���������ڵ�////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Result6[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();
			}
		}
	}
	cout << "����6����������7��ʼ" << endl;
	/////////////////////////////////////////����6����////////////////////////////////////////////////
	////////////////////////////////////////����7��˳��ɾ��k,j,i/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				///////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				///////////////////////////////��ʼɾ����һ���ڵ�/////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				/////////////////////////////////////////��ʼɾ���ڶ����ڵ�////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				/////////////////////////////////////////��ʼɾ���������ڵ�////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				Result7[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();

			}
		}
	}
	cout << "����7����������8��ʼ" << endl;
	/////////////////////////////////////////����7����////////////////////////////////////////////////
	////////////////////////////////////////����8��˳��ɾ��i,(k,j)/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				//////////////////////////////////////////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				////////////////////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				Result8[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();


			}
		}
	}
	cout << "����8����������9��ʼ" << endl;
	/////////////////////////////////////////����8����////////////////////////////////////////////////
	////////////////////////////////////////����9��˳��ɾ��j,(k,i)/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				//////////////////////////////////////////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				////////////////////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				Result9[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();




			}
		}
	}
	cout << "����9����������10��ʼ" << endl;
	/////////////////////////////////////////����9����////////////////////////////////////////////////
	////////////////////////////////////////����10��˳��ɾ��k,(i,j)/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				//////////////////////////////////////////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				////////////////////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				Result10[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();
			}
		}
	}
	cout << "����10����������11��ʼ" << endl;
	/////////////////////////////////////////����10����////////////////////////////////////////////////
	////////////////////////////////////////����11��˳��ɾ��(i,j),k/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{

				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				//////////////////////////////////////////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				////////////////////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				Result11[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();



			}
		}
	}
	cout << "����11����������12��ʼ" << endl;
	/////////////////////////////////////////����11����////////////////////////////////////////////////
	////////////////////////////////////////����12��˳��ɾ��(i,k),j/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{

				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				//////////////////////////////////////////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				////////////////////////////////////////////////
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				Result12[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();


			}
		}
	}
	cout << "����12����������13��ʼ" << endl;
	/////////////////////////////////////////����12����////////////////////////////////////////////////
	////////////////////////////////////////����13��˳��ɾ��(k,j),i/////////////////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				///////////////////////////���ȸ�ֵһ����������//////////////////////////////
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
				//////////////////////////////////////////////////////////////////////
				Del(k, Tnodeleft, Tleftlink, Tleftnode);
				Del(j, Tnodeleft, Tleftlink, Tleftnode);
				bool alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}
				////////////////////////////////////////////////
				Del(i, Tnodeleft, Tleftlink, Tleftnode);
				alltag = true;
				while (alltag)
				{
					alltag = false;
					giantset(Tleftlink, Tleftnode);
					Tleftnode.refer = Tleftnode.head;
					/////////////////////////////////////////////����������Ƿ���ڲ����������ͨ��ͼ�ĵ�/////
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
					///////////////////////////////////////////����������Ƿ������������Ľڵ�//////////////
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
					///////////////////�Ҳ������Ƿ���ڹ��صĽڵ�/////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();////���Դ洢��������й��ؽڵ�
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
					////////////////////�Ҳ��������Ƿ�����������Ľڵ�////////////////////////////////
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel1 = Plist<int>();
					while (Trightnode.refer != NULL)
					{
						if (Tnodeleft[deplinkr2l[Trightnode.refer->data]] == 0)
						{
							alltag = true;
							zandel1.insert(Trightnode.refer->data);
							//cout << "����" << i << "  " << j << endl;
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					if (zandel1.head != NULL)
					{
						Load_sim_Del(zandel1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel1.~Plist();
				}

				Result13[i][j][k] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();

			}
		}
	}









	///////////////////////////////////////////////������////////////////////////////////////////////////













	ofstream fout("strategy8.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				
				fout << Result8[i][j][k] << endl;;
			}
		}
	}
	fout.close();
	//////////////////////////////////
	ofstream cout2("strategy9.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout2 << Result9[i][j][k] << endl;
			}
		}
	}
	cout2.close();
	//////////////////////////////////
	ofstream cout3("strategy10.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout3 << Result10[i][j][k] << endl;
			}
		}
	}
	cout3.close();
	//////////////////////////////////
	ofstream cout4("strategy11.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout4 << Result11[i][j][k] << endl;
			}
		}
	}
	cout4.close();
	//////////////////////////////////
	ofstream cout5("strategy12.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout5 << Result12[i][j][k] << endl;
			}
		}
	}
	cout5.close();
	////////////////////////////
	ofstream cout6("strategy13.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout6 << Result13[i][j][k] << endl;
			}
		}
	}
	cout6.close();
	//////////////////////////////////////
	ofstream cout7("strategy1.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout7 << Result1[i][j][k] << endl;
			}
		}
	}
	cout7.close();
	//////////////////////////////////////
	ofstream cout8("strategy2.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout8 << Result2[i][j][k] << endl;
			}
		}
	}
	cout8.close();
	///////////////////////////////////////
	ofstream cout9("strategy3.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout9 << Result3[i][j][k] << endl;
			}
		}
	}
	cout9.close();
	/////////////////////////////////////////
	ofstream cout10("strategy4.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout10 << Result4[i][j][k] << endl;
			}
		}
	}
	cout10.close();
	/////////////////////////////////////////
	ofstream cout11("strategy5.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout11 << Result5[i][j][k] << endl;
			}
		}
	}
	cout11.close();
	///////////////////////////////////////////
	ofstream cout12("strategy6.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout12 << Result6[i][j][k] << endl;
			}
		}
	}
	cout12.close();
	//////////////////////////////////////////////////
	ofstream cout13("strategy7.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i + 1; j < nodes_number; j++)
		{
			for (int k = j + 1; k < nodes_number; k++)
			{
				cout13 << Result7[i][j][k] << endl;
			}
		}
	}
	cout13.close();






	
	cout << "helloworld" << endl;
}
