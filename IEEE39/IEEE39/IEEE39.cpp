using namespace std;
#define nodes_number 39
#define zhishu 2
#define redun 0.8
#include<iostream>
#include"Plist.h"
#include"time.h"
#include"math.h"
#include<fstream>


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
	for (int i = 0; i < nodes_number; i++)
	{
		node[i] = 1;
	}
	////////////////////////////////����IEEE 39bus///////////////////
	link[0][1] = 1; //1
	link[1][0] = 1;
	nodedegree[0]++;
	nodedegree[1]++;

	link[0][38] = 1; //2
	link[38][0] = 1;
	nodedegree[0]++;
	nodedegree[38]++;

	link[1][2] = 1;//3
	link[2][1] = 1;
	nodedegree[1]++;
	nodedegree[2]++;
	link[1][24] = 1;//4
	link[24][1] = 1;
	nodedegree[1]++;
	nodedegree[24]++;
	link[1][29] = 1; //44
	link[29][1] = 1;
	nodedegree[1]++;
	nodedegree[29]++;
	link[2][3] = 1;//5
	link[3][2] = 1;
	nodedegree[2]++;
	nodedegree[3]++;
	link[2][17] = 1;//6
	link[17][2] = 1;
	nodedegree[2]++;
	nodedegree[17]++;
	link[3][4] = 1;//7
	link[4][3] = 1;
	nodedegree[3]++;
	nodedegree[4]++;
	link[3][13] = 1;//8
	link[13][3] = 1;
	nodedegree[3]++;
	nodedegree[13]++;
	link[4][5] = 1;//9
	link[5][4] = 1;
	nodedegree[4]++;
	nodedegree[5]++;
	link[4][7] = 1;//10
	link[7][4] = 1;
	nodedegree[4]++;
	nodedegree[7]++;

	link[5][6] = 1;//11
	link[6][5] = 1;
	nodedegree[5]++;
	nodedegree[6]++;

	link[5][10] = 1;//12
	link[10][5] = 1;
	nodedegree[5]++;
	nodedegree[10]++;
	link[5][30] = 1;//37
	link[30][5] = 1;
	nodedegree[5]++;
	nodedegree[30]++;
	link[6][7] = 1;//13
	link[7][6] = 1;
	nodedegree[6]++;
	nodedegree[7]++;
	link[7][8] = 1;//14
	link[8][7] = 1;
	nodedegree[7]++;
	nodedegree[8]++;
	link[8][38] = 1;//15
	link[38][8] = 1;
	nodedegree[8]++;
	nodedegree[38]++;
	link[9][10] = 1;//16
	link[10][9] = 1;
	nodedegree[9]++;
	nodedegree[10]++;

	link[9][12] = 1;//17
	link[12][9] = 1;
	nodedegree[9]++;
	nodedegree[12]++;

	link[9][31] = 1;//38
	link[31][9] = 1;
	nodedegree[9]++;
	nodedegree[31]++;

	link[10][11] = 1;//35
	link[11][10] = 1;
	nodedegree[10]++;
	nodedegree[11]++;

	link[11][12] = 1;//36
	link[12][11] = 1;
	nodedegree[11]++;
	nodedegree[12]++;

	link[12][13] = 1;//18
	link[13][12] = 1;
	nodedegree[12]++;
	nodedegree[13]++;

	link[13][14] = 1;//19
	link[14][13] = 1;
	nodedegree[13]++;
	nodedegree[14]++;

	link[14][15] = 1;//20
	link[15][14] = 1;
	nodedegree[14]++;
	nodedegree[15]++;

	link[15][16] = 1;//21
	link[16][15] = 1;
	nodedegree[15]++;
	nodedegree[16]++;

	link[15][18] = 1;//22
	link[18][15] = 1;
	nodedegree[15]++;
	nodedegree[18]++;


	link[15][20] = 1;//23
	link[20][15] = 1;
	nodedegree[15]++;
	nodedegree[20]++;

	link[15][23] = 1;//24
	link[23][15] = 1;
	nodedegree[15]++;
	nodedegree[23]++;

	link[16][17] = 1;//25
	link[17][16] = 1;
	nodedegree[16]++;
	nodedegree[17]++;

	link[16][26] = 1;//26
	link[26][16] = 1;
	nodedegree[16]++;
	nodedegree[26]++;

	link[18][19] = 1;//46
	link[19][18] = 1;
	nodedegree[18]++;
	nodedegree[19]++;

	link[18][32] = 1;//39
	link[32][18] = 1;
	nodedegree[18]++;
	nodedegree[32]++;

	link[19][33] = 1;//40
	link[33][19] = 1;
	nodedegree[19]++;
	nodedegree[33]++;

	link[20][21] = 1;//27
	link[21][20] = 1;
	nodedegree[20]++;
	nodedegree[21]++;

	link[21][22] = 1;//28
	link[22][21] = 1;
	nodedegree[21]++;
	nodedegree[22]++;

	link[21][34] = 1;//41
	link[34][21] = 1;
	nodedegree[21]++;
	nodedegree[34]++;

	link[22][23] = 1;//29
	link[23][22] = 1;
	nodedegree[22]++;
	nodedegree[23]++;

	link[22][35] = 1;//42
	link[35][22] = 1;
	nodedegree[22]++;
	nodedegree[35]++;

	link[24][25] = 1;//30
	link[25][24] = 1;
	nodedegree[24]++;
	nodedegree[25]++;

	link[24][36] = 1;//43
	link[36][24] = 1;
	nodedegree[24]++;
	nodedegree[36]++;

	link[25][26] = 1;//31
	link[26][25] = 1;
	nodedegree[25]++;
	nodedegree[26]++;

	link[25][27] = 1;//32
	link[27][25] = 1;
	nodedegree[25]++;
	nodedegree[27]++;

	link[25][28] = 1;//33
	link[28][25] = 1;
	nodedegree[25]++;
	nodedegree[28]++;

	link[27][28] = 1;//34
	link[28][27] = 1;
	nodedegree[27]++;
	nodedegree[28]++;

	link[28][37] = 1;//45
	link[37][28] = 1;
	nodedegree[28]++;
	nodedegree[37]++;



	//����ڵ�capacity
	for (int i = 0; i < nodes_number; i++)
	{
		icapacity[i] = pow(nodedegree[i], zhishu);
		tcapacity[i] = (1 + redun)*icapacity[i];
	}

}

int main()
{
	int rightseq_number = 0; //�����������й���ռ������
	int rightsim_number = 0;//�������繲ʱ����ռ������
	Plist<int> rightnode = Plist<int>();//�Ҳ���ڵ�����
	double right_Del_sequence_result[nodes_number][nodes_number] = { 0 };
	double right_Del_sim_result[nodes_number][nodes_number] = { 0 };
	int noderight[nodes_number] = { 0 }; //�洢�Ҳ������нڵ�״̬
	int rightlink[nodes_number][nodes_number] = { 0 };
	int rightdegree[nodes_number] = { 0 };
	double inicapacity[nodes_number] = { 0 };//�Ҳ������ʼ����
	double trecapacity[nodes_number] = { 0 };//�Ҳ����縺�ط�ֵ
	load_BAG(noderight, rightlink, rightdegree, inicapacity, trecapacity);

	////////////////////////////////////////////////////////////��ʼ�������нڵ�����////////////////////////
	for (int i = 0; i < nodes_number; i++)
	{
		rightnode.insert(i);
	}

	////////////////////////////////////////////////////���Ҳ�������ͬʱɾ�������ڵ�////////////////////////
	ofstream simfout("singlesim.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (i == j)
			{
				right_Del_sim_result[i][j] = 1;
			}
			else
			{
				simfout << "i " << i << " j " << j << endl;
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
							simfout << " node " << Trightnode.refer->data << "  failed";
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					simfout << endl;
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
	simfout.close();
	//ͬʱɾ������������̽���//////////////////////////////////////////////////////////
	cout << "state1" << endl;
	/////////////////////////////////////////////////��ʼ˳��ɾ�����������ڽڵ�/////////
	ofstream seqfout("singleseq.txt");
	for (int i = 0; i < nodes_number; i++)
	{
		for (int j = 0; j < nodes_number; j++)
		{
			if (i == j)
			{
				right_Del_sequence_result[i][j] = 1;
			}
			else
			{
				seqfout << "seqɾ�� " << endl;
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
				seqfout << "i " << i << endl;
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
							seqfout << " node " << Trightnode.refer->data << "  failed";

						}
						Trightnode.refer = Trightnode.refer->next;
					}
					seqfout << endl;
					if (zandel.head != NULL)
					{
						Load_sim_Del(zandel, Tnoderight, Trightlink, Trightnode, Tinicapacity);
					}
					zandel.~Plist();

				}
				dlist.~Plist();
				////////////////////////////////ɾ���ڶ����ڵ�///////////////////////////////
				seqfout << "j " << j << endl;
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
							seqfout << " node " << Trightnode.refer->data << "  failed";
						}
						Trightnode.refer = Trightnode.refer->next;
					}
					seqfout << endl;
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
	seqfout.close();
	////////////////////////////////////////////////////////˳��ɾ�����������ڵĽڵ����/////////////////////////////////////

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
				fout << "result: " << i << "  " << j << "   sim: " << right_Del_sim_result[i][j] * nodes_number << "  sequence: " << right_Del_sequence_result[i][j] * nodes_number << endl;
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
				fout << "result: " << i << "  " << j << "   sim: " << right_Del_sim_result[i][j] * nodes_number << "  sequence: " << right_Del_sequence_result[i][j] * nodes_number << endl;
				rightsim_number = rightsim_number + 1;
			}
		}
	}
	fout.close();


	return 0;
}
