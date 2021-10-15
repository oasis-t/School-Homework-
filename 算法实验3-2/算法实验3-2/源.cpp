#include <iostream>
using namespace std;

int load1;//轮船1的载重量
int load2;//轮船2的载重量
int currentload1=0;//当前轮船1的载重量
int currentload2;//当前轮船2的载重量
int x[100]; //表示当前解，0代不表放，1代表放
int bestx[100];//表示最优解
int w[100];// 表示集装箱i的重量
int bestw=0;//当前最优装载重量
int rest=0;//剩余集装箱的重量
int n; //集装箱的数量

void BackTrack(int i){
    if (i > n){ //判断是否达到叶子节点
        if (currentload1 > bestw){
            for (int j = 1; j <= n; j++){
                bestx[j] = x[j];
            }
            bestw = currentload1;
        }
    }
    rest = rest - w[i];
    if (currentload1 + w[i] <= load1){ //判断该集装箱到底放不放
        x[i] = 1;
        currentload1 = currentload1 + w[i];
        BackTrack(i + 1);
        //当节点i的子树延伸结束时要返回i节点
        x[i] = 0;
        currentload1 = currentload1 - w[i];

    }
    if (currentload1 + rest > bestw){ //判断先不放该集装箱后是否还有可行解
        x[i] = 0;
        BackTrack(i + 1);
    }
    rest = rest + w[i];//当节点i的子树延伸结束时要返回i节点
}

int main()
{
    cout << "请输入集装箱的数量：" << endl;
    cin >> n;
    cout << "请输入轮船1,2的载重量：" << endl;
    cin >> load1 >> load2;
    cout << "请输入每个集装箱的重量：" << endl;
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
        cout << "装载失败" << endl;
    else{
        cout << "装载成功\n轮船1装入的集装箱序号为：";
        for (int i = 1; i <= n; i++){
            if (bestx[i] == 1)
                cout << i << " ";
        }
        cout << endl;
        cout << "轮船2装入的集装箱序号为：";
        for (int i = 1; i <= n; i++){
            if (bestx[i] != 1)
                cout << i << " ";
        }
    }
}