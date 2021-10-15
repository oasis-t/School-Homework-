#include <iostream>
using namespace std;

int load1;//�ִ�1��������
int load2;//�ִ�2��������
int currentload1=0;//��ǰ�ִ�1��������
int currentload2;//��ǰ�ִ�2��������
int x[100]; //��ʾ��ǰ�⣬0������ţ�1�����
int bestx[100];//��ʾ���Ž�
int w[100];// ��ʾ��װ��i������
int bestw=0;//��ǰ����װ������
int rest=0;//ʣ�༯װ�������
int n; //��װ�������

void BackTrack(int i){
    if (i > n){ //�ж��Ƿ�ﵽҶ�ӽڵ�
        if (currentload1 > bestw){
            for (int j = 1; j <= n; j++){
                bestx[j] = x[j];
            }
            bestw = currentload1;
        }
    }
    rest = rest - w[i];
    if (currentload1 + w[i] <= load1){ //�жϸü�װ�䵽�׷Ų���
        x[i] = 1;
        currentload1 = currentload1 + w[i];
        BackTrack(i + 1);
        //���ڵ�i�������������ʱҪ����i�ڵ�
        x[i] = 0;
        currentload1 = currentload1 - w[i];

    }
    if (currentload1 + rest > bestw){ //�ж��Ȳ��Ÿü�װ����Ƿ��п��н�
        x[i] = 0;
        BackTrack(i + 1);
    }
    rest = rest + w[i];//���ڵ�i�������������ʱҪ����i�ڵ�
}

int main()
{
    cout << "�����뼯װ���������" << endl;
    cin >> n;
    cout << "�������ִ�1,2����������" << endl;
    cin >> load1 >> load2;
    cout << "������ÿ����װ���������" << endl;
    for (int i = 1; i <= n; i++){
        cin >> w[i];
    }
    for (int i = 1; i <= n; i++) {
        rest = rest + w[i];
    }
    BackTrack(1); 
    for (int i = 1; i <= n; i++){
        if (bestx[i] == 0){
            currentload2 = currentload2 + w[i];
        }
    }
    if (currentload2 > load2)
        cout << "װ��ʧ��" << endl;
    else{
        cout << "װ�سɹ�\n�ִ�1װ��ļ�װ�����Ϊ��";
        for (int i = 1; i <= n; i++){
            if (bestx[i] == 1)
                cout << i << " ";
        }
        cout << endl;
        cout << "�ִ�2װ��ļ�װ�����Ϊ��";
        for (int i = 1; i <= n; i++){
            if (bestx[i] != 1)
                cout << i << " ";
        }
    }
}