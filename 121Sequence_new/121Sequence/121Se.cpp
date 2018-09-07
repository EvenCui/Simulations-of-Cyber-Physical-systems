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
		int randshu = rand() % (rnode.len );
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
	int seq_number = 0;//�ܵ����й���ռ����
	int sim_number = 0;//�ܵĹ�ʶ����ռ����
	int rightseq_number = 0; //�����������й���ռ������
	int rightsim_number = 0;//�������繲ʱ����ռ������
	srand(time(NULL));
	Plist<int> leftnode = Plist<int>();//�����ڵ�����
	Plist<int> rightnode = Plist<int>();//�Ҳ���ڵ�����
	double Del_sequence_result[nodes_number][nodes_number] = { 0 };
	double Del_sim_result[nodes_number][nodes_number] = { 0 };
	double right_Del_sequence_result[nodes_number][nodes_number] = { 0 };
	double right_Del_sim_result[nodes_number][nodes_number] = { 0 };
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
	////////////////////////////////////////////////////���Ҳ�������ͬʱɾ�������ڵ�////////////////////////
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
				///////////////////////////���ȸ�ֵһ������//////////////////////////////
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
					Plist<int> zandel = Plist<int>();///////////////////////���Դ洢���ι��ؽڵ�//////////////////////////
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
	//ͬʱɾ������������̽���//////////////////////////////////////////////////////////
	cout << "state1" << endl;
	/////////////////////////////////////////////////��ʼ˳��ɾ�����������ڽڵ�/////////
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
				///////////////////////////���ȸ�ֵһ������//////////////////////////////
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
				///////////////////ɾ����һ���ڵ�/////////////////////////////
				Plist<int> dlist = Plist<int>();
				dlist.insert(i);
				Load_sim_Del(dlist, Tnoderight, Trightlink, Trightnode, Tinicapacity);
				bool changetag = true;
				while (changetag)
				{
					changetag = false;
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();///////////////////////���Դ洢���ι��ؽڵ�//////////////////////////
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
				////////////////////////////////ɾ���ڶ����ڵ�///////////////////////////////
				Plist<int> dlist1 = Plist<int>();
				dlist1.insert(j);
				Load_sim_Del(dlist1, Tnoderight, Trightlink, Trightnode, Tinicapacity);
				changetag = true;
				while (changetag)
				{
					changetag = false;
					Trightnode.refer = Trightnode.head;
					Plist<int> zandel = Plist<int>();///////////////////////���Դ洢���ι��ؽڵ�//////////////////////////
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
	////////////////////////////////////////////////////////˳��ɾ�����������ڵĽڵ����/////////////////////////////////////

	///////////////////////////////////////////////////////ͬʱɾ�����������е������ڵ�/////////////////////////////////////
	
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
				///////////////////////////////��ʼɾ���ڵ�/////////////////////////////////
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
				Del_sim_result[i][j] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();


			}
		}
	}

	//////////////////////////////////////////˳��ɾ�����������ڵ�//////////////////////
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
				/////////////////////////////////�������///////////////////////////////////////////////
				Del_sequence_result[i][j] = (double)(Tleftnode.len + Trightnode.len) / (leftnode.len + rightnode.len);
				Tleftnode.~Plist();
				Trightnode.~Plist();


			}
		}
	}










	cout << "helloworld" << endl;






	////////////////////////////////////������/////////////////////////////////////////////
	/**/
	ofstream fout("single.txt");
	cout << endl;
	fout << "������������ԱȽ�������й������ڹ�ʱ����" << endl;
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
	fout << "������������ԱȽ������ʱ�����������й���" << endl;
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
	fout1 << "������������ԱȽ�������й������ڹ�ʱ����" << endl;
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
	fout1 << "������������ԱȽ������ʱ�����������й���" << endl;
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
	//////////////////////////////////////�����������ṹ//////////////////////////////////
	ofstream fout2("struct.txt");
	fout2 << "�����ṹ" << endl;
	for(int i = 0; i < nodes_number; i++)
	{
		fout2 << i << "  " << deplinkl2r[i] << endl;
	}
	fout2.close();
	////////////////////////////////////��Ϣ��������������ṹ////////////////////////////////////
	ofstream fout3("structCP.txt");
	fout3 << "��Ϣ���������ṹ" << endl;
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = i+1; j < nodes_number; j++)
		{
			fout3 << i << " " << j << "  " << leftlink[i][j] << endl;
		}
	}

	fout3 << "�������������ṹ" << endl;
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