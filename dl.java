import java.awt.Color;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class dl extends JFrame implements ActionListener{

    private String expression;//记录表达式

    //各个按键的字符
    private final String[] keys = {"0","1","CLR","Backspace",
            "XOR","NOT","AND","+",
            "COMP","=","OR","-",
            " ","8位","16位","32位",
    };
    private JTextField result = new JTextField("0");


    //按键
    private JButton[] button = new JButton[16];

    dl(){

        //计算器布局
        JPanel jp = new JPanel();
        this.setTitle("二进制计算器");
        //布局先分为六行，第一行为文本显示，二到五行为按键
        jp.setLayout(new GridLayout(6,1));

        jp.add(result);
        result.setFont(result.getFont().deriveFont((float)(30)));
        Container[] containers = new Container[5];
        for (int i = 0;i < 5;++i){
            containers[i] = new Container();
            containers[i].setLayout(new GridLayout(1,5));
            jp.add(containers[i]);
        }

        //按钮
        for (int i = 0;i < button.length;++i){
            button[i] = new JButton(keys[i]);
            button[i].setFont(button[i].getFont().deriveFont((float)(30)));
            containers[i/4].add(button[i]);
            button[i].addActionListener(this);
            if (i == 2 || i == 3) button[i].setForeground(Color.red);
        }
        getContentPane().add(jp);

        //表达式赋值为空
        expression = "";
    }



    @Override
    public void actionPerformed(ActionEvent e) {
        // TODO Auto-generated method stub
        String action = e.getActionCommand();


        if (action.equals(keys[2])){
            //用户按下CLR
            handleC();
        }else if (action.equals(keys[3])){
            //用户按下退格
            handleBackspace();
        }else if (action.equals(keys[9])){
            //用户按下=
            handleCalc();
        }else if(action.equals(keys[13])){
            //8位运算
            Eight();
        }else if(action.equals(keys[14])) {
            //16位运算
            Sixteen();
        }else if(action.equals(keys[15])){
            //32位运算
            ThirtyThree();
        }
        else{
            //用户输入表达式
            handleExpression(action);
        }
    }

    private void Eight(){
        button[13].setForeground(Color.red);
        button[14].setForeground(Color.black);
        button[15].setForeground(Color.black);
        int []a = Judge(expression);
        if (a[0]!=8||(a[1]!=8&& a[1]!=0)){
            result.setText("输入错误");
            expression="";
        }


    }
    private void Sixteen(){
        button[13].setForeground(Color.black);
        button[14].setForeground(Color.red);
        button[15].setForeground(Color.black);
        int []a = Judge(expression);
        if (a[0]!=16||(a[1]!=16&& a[1]!=0)){
            result.setText("输入错误");
            expression="";
        }
    }
    private void ThirtyThree(){
        button[13].setForeground(Color.black);
        button[14].setForeground(Color.black);
        button[15].setForeground(Color.red);
        int []a = Judge(expression);
        if (a[0]!=32||(a[1]!=32&& a[1]!=0)){
            result.setText("输入错误");
            expression="";
        }
    }
    //判断输入是否正确
    private int[] Judge(String s){
        char[] arr=s.toCharArray();
        int a=0,b=0,c=1;
        for (int i = 0; i <arr.length; i++) {
            if((arr[i]=='0'||arr[i]=='1')&&c ==1){
                a++;
            }
            if(!(arr[i]=='0'||arr[i]=='1')){
                c=0;
            }
            if((arr[i]=='0'||arr[i]=='1')&&c ==0){
                b++;
            }
        }
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
        int[] result={a,b};
        return result;
    }
    //处理按下C的事件
    private void handleC(){
        expression = "";
        result.setText("");
        button[13].setForeground(Color.black);
        button[14].setForeground(Color.black);
        button[15].setForeground(Color.black);
    }

    //处理按下退格的事件
    private void handleBackspace(){
        expression = expression.substring(0,expression.length() - 1);
        result.setText(expression);
    }

    //处理按下等号的事件
    private void handleCalc(){
        result.setText(Calculator.TransferToArray(expression));
        expression = "";
    }

    //处理用户按下数字或运算符的事件
    private void handleExpression(String action){
        expression += action;
        result.setText(expression);
    }

    public static void main(String[] args){
        dl calculator = new dl();
        calculator.setSize(600,800);
        calculator.setVisible(true);
        calculator.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
    }

}

class Calculator {
    public static String PlusOrMinus(String s){//加法或减法功能
        int len=s.length();
        /*String Former="0"+s.substring(0,(len-1)/2);
        char[] former=Former.toCharArray();//被加数或被减数字符串转化为字符数组
        String Latter="",fin="";
        char[] latter;
        char Symbol=s.charAt((len-1)/2);//符号
        if(Symbol=='+'){//符号为+则第一位加0不变
            Latter="0"+s.substring((len+1)/2,len);
            latter=Latter.toCharArray();//加数字符串转化为字符数组
        }else{//符号为-则第一位加1后取补码
            Latter="1"+s.substring((len+1)/2,len);
            latter=Latter.toCharArray();//减数字符串转化为字符数组
            for(int i=1;i<latter.length;i++){//将减数数组取补码
                if(latter[i]=='1')
                    latter[i]='0';
                else
                    latter[i]='1';
            }
        }
        //到此两个操作对象根据加减号取补码
        char[] result=new char[former.length];
        for(int i=result.length-1;i>0;i--){
            if(Integer.parseInt(String.valueOf(former[i]))+Integer.parseInt(String.valueOf(latter[i]))==0){
                result[i]='0';
            }else if(Integer.parseInt(String.valueOf(former[i]))+Integer.parseInt(String.valueOf(latter[i]))==1){
                result[i]='1';
            }else{
                result[i]=(char)(Integer.parseInt(String.valueOf(former[i]))+Integer.parseInt(String.valueOf(latter[i]))-2);
//                if(i!=1)
                    former[i-1]++;
            }
        }
        if(Integer.parseInt(String.valueOf(former[0]))+Integer.parseInt(String.valueOf(latter[0]))==1){
//            result[0]='0';
            for(int i=1;i<result.length;i++){
                if(result[i]=='1'){
                    result[i]='0';
                }else if(result[i]=='0'){
                    result[i]='1';
                }
            }
            fin=new String(result).substring(1,result.length);
        }else if(Integer.parseInt(String.valueOf(former[0]))+Integer.parseInt(String.valueOf(latter[0]))==2){
            result[0]='0';
            fin="1"+new String(result).substring(1,result.length);
        }else{
            fin=new String(result).substring(1,result.length);
        }

//        if(result[0])
        return fin;*/
        String Former=s.substring(0,(len-1)/2);
        String Latter=s.substring((len+1)/2,len);
        char Symbol=s.charAt((len-1)/2);//符号
        long former=Long.parseLong(Former);
        long latter=Long.parseLong(Latter);
        long decimalOfFormer=0,p=0;
        long decimalOfLatter=0,q=0;
        while(former!=0)
        {
            decimalOfFormer+=((former%10)*Math.pow(2,p));
            former/=10;
            p++;
        }
        while(latter!=0)
        {
            decimalOfLatter+=((latter%10)*Math.pow(2,q));
            latter/=10;
            q++;
        }
        //加法操作
        if(Symbol=='+'){
            long sum=decimalOfFormer+decimalOfLatter;
            String result = Long.toBinaryString(sum);
            return result;
        }
        //减法操作
        if(Symbol=='-'){
            if(decimalOfFormer>=decimalOfLatter){
                long minus=decimalOfFormer-decimalOfLatter;
                String result=Long.toBinaryString(minus);
                return result;
            }else{
                long minus=decimalOfLatter-decimalOfFormer;
                String result="-";
                result+=Long.toBinaryString(minus);
                return result;
            }
        }
        return null;
    }

    public static String Or(String s){//或运算
        int len=s.length();
        String Former=s.substring(0,len/2-1);//读取前一个数
        String Latter=s.substring(len/2+1,len);//读取后一个数

        char[] arr1=Former.toCharArray();
        char[] arr2=Latter.toCharArray();
        char[] arrOfResult=new char[len/2-1];//结果数组
        for (int i = 0; i < len/2-1; i++) {
            if(arr1[i]=='1'||arr2[i]=='1'){
                arrOfResult[i]='1';
            }else{
                arrOfResult[i]='0';
            }
        }
        String result=new String(arrOfResult);
        return result;
    }

    public static String NOT(String s){//NOT运算
        int len=s.length();
        String Former=s.substring(0,len-3);
        char[] arr=Former.toCharArray();
        for (int i = 0; i < len-3; i++) {
            if(arr[i]=='1')
                arr[i]='0';
            else if(arr[i]=='0')
                arr[i]='1';
        }
        String result=new String(arr);
        return result;
    }

    public static String ANDorXOR(String s){
        int len=s.length();
        String Former=s.substring(0,len/2-1);
        String Latter=s.substring((len+1)/2+1,len);
        char Symbol=s.charAt(len/2-1);//符号
        char[] arr1=Former.toCharArray();
        char[] arr2=Latter.toCharArray();
        char[] arrOfResult=new char[len/2-1];//结果数组
        if(Symbol=='X'){//异或功能
            for (int i = 0; i < len/2-1; i++) {
                if(arr1[i]==arr2[i]){
                    arrOfResult[i]='0';
                }else
                    arrOfResult[i]='1';
            }
            String result=new String(arrOfResult);
            return result;
        }else if(Symbol=='A'){//与功能
            for (int i = 0; i < len/2-1; i++) {
                if(arr1[i]=='1'&&arr2[i]=='1'){
                    arrOfResult[i]='1';
                }else
                    arrOfResult[i]='0';
            }
            String result=new String(arrOfResult);
            return result;
        }
        return null;
    }

    public static String COMP(String s){//补码
        int len=s.length();
        String str=s.substring(0,len-4);
        char[] arr=str.toCharArray();

        if(arr[0]=='0'){//正数
            return new String(arr);
        }else{
            for (int i = 1; i < arr.length; i++) {
                if(arr[i]=='1'){
                    arr[i]='0';
                }else if(arr[i]=='0'){
                    arr[i]='1';
                }
            }
            return new String(arr);
        }
    }

    public static String TransferToArray(String s){
        int len=s.length();//获取字符串长度
        if(s.contains(String.valueOf('+'))||s.contains(String.valueOf('-'))){//+和-
            return Calculator.PlusOrMinus(s);
        }else if(s.contains("XOR")||s.contains("AND")){//XOR/AND
            return Calculator.ANDorXOR(s);
        }else if(s.contains("OR")){//OR
            return Calculator.Or(s);
        }else if(s.contains("NOT")){
            return Calculator.NOT(s);
        }else if(s.contains("COMP")){//COMP
            return Calculator.COMP(s);
        }
        return null;
    }
}
