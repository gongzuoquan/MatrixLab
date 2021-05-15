#include<iostream>
#include<cmath>
using namespace std;
//1.向量类
template<class T>
class Vector{
    public:
        T *data;
        int length;
    public:
        Vector(){
            length=0;
            data=NULL;
            return;
        }
        explicit Vector(int in_len):length(in_len){
            //data=(T*)malloc(sizeof(T)*in_len);
            data=new T[length]();
            for(int i=0;i<length;i++)
                data[i]=0;
        }
        Vector(int in_len,T *in_data)
        {
            length=in_len;
            //data=(double*)malloc(sizeof(T)*in_len);
            data=new T[length]();
            for(int i=0;i<in_len;i++)
            {
                data[i]=in_data[i];
            }
            return;
        }

        Vector(const Vector &in_vec) //一定要加const，否则报错
        {
            length=in_vec.length;
            data=new T[length]();
            for(int i=0;i<length;i++)
                data[i]=in_vec.data[i];
            return;
        }

        ~Vector()
        {
            delete[] data;
        }

    public:
        //1.重载运算符[]
        T &operator[]( int idx)
        {
            if(idx >= length || idx<-length)
            {
                cerr<<"下标输入错误"<<endl;
                return data[0]; //TODO
            }
            if(idx<0)
            {
                return data[length+idx];
            }
            return data[idx];
        }
        //2.展示向量内容
        void display()
        {
            if(length==0)
            {
                cout<<"本向量为空"<<endl;
            }
            for(int i=0;i<length;i++)
            {
                cout<<setprecision(4)<<setw(8)<<data[i]<<" ";
            }
            cout<<endl;
            return ;
        }
        //3.向量点乘
        T dot( Vector &vec)
        {
            if(length!=vec.length)
            {
                cerr<<"向量与矩阵维度不符，无法相乘"<<endl;
                return 0.0;
            }
            int length=vec.length;
            T out=0;
            for(int i=0;i<length;i++)
            {
                out+=vec[i]*data[i];
            }
            return out;
        }
};
