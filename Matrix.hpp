#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
#define EPS 1e-10

//2.矩阵类
template<class T>
class Matrix
{
    public:
        int row,col; //行，列
        T *data; //一维向量映射二维矩阵
    public:
        Matrix()
        {
            row=0;
            col=0;
            data=NULL;
        }
        Matrix(const int in_row,const int in_col)
        {
            row=in_row;
            col=in_col;
            //data=(T*)malloc(sizeof(T)*row*col);
            data=new T[row*col]();
            for(int i=0;i<row*col;i++)
                data[i]=0;
        }
        Matrix(const Matrix &in_mat)
        {
            row=in_mat.row;
            col=in_mat.col;
            data=new T[row*col]();
            for(int i=0;i<row*col;i++)
                data[i]=in_mat.data[i];
        }
        ~Matrix()
        {
            if(data != NULL)
                //free(data);
                delete[] data;
        }

    public:
        //1.重载符号[]
        //注：这里为了实现使用a[i][j]获取矩阵特定元素，设计a[i]返回行指针
        T *operator[](const int in_row) const
        {
            if(in_row>=row || in_row<0)
            {
                cout<<"下标输入错误"<<endl;
                return &data[0]; //TODO
            }
            return &data[in_row*col];
        }


        //2.重载符号()
        T operator()(const int in_row,const int in_col)
        {
            if(in_row>=row || in_row<0|| in_col>=col|| in_col<0)
            {
                cerr<<"下标输入错误"<<endl;
                return data[0]; //TODO 
            }
            return data[in_row*col+in_col];
        }
        //3.统一初始化为一个值
        void init_value(T value)
        {
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<col;j++)
                {
                    data[i*col+j]=value;
                }
            }
        }
        //4.展示矩阵内容
        void display()
        {
            if(row==0 || col==0)
            {
                cout<<"本矩阵为空"<<endl;
                return;
            }
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<col;j++)
                {
                    cout<<setprecision(4)<<setw(8)<<data[i*col+j]<<" ";
                }
                cout<<endl;
            }
        }
        //5.矩阵转置
        Matrix<T> transpose()
        {
            Matrix<T> out(col,row);
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<col;j++)
                {
                    out[i][j]=data[j*col+i];
                }
            }
            return out;
        }
        //6.联合
        Matrix<T> concat(Matrix<T> mat,int axis=1)//默认在列上扩增
        {
            if(axis!=1 && axis!=0)
            {
                cerr<<"维度指定错误"<<endl;
                return mat;
            }
            if((axis==0 && mat.col!=col)||(axis==1 && mat.row!=row))
            {
                cerr<<"维度不匹配"<<endl;
                return mat;
            }
            if(axis==0) //在行上拼接
            {
                Matrix<T> out=Matrix(row+mat.row,col);
                for(int i=0;i<row;i++)
                {
                    for(int j=0;j<col;j++)
                    {
                        out[i][j]=data[i*col+j];
                    }
                }
                for(int i=row;i<row+mat.row;i++)
                {
                    for(int j=0;j<col;j++)
                    {
                        out[i][j]=mat[i-row][j];
                    }
                }
                return out;
            }
            else //在列上拼接
            {
                Matrix<T> out=Matrix(row,col+mat.col);
                for(int i=0;i<row;i++)
                {
                    for(int j=0;j<col;j++)
                    {
                        out[i][j]=data[i*col+j];
                    }
                }
                for(int i=0;i<row;i++)
                {
                    for(int j=col;j<col+mat.col;j++)
                    {
                        out[i][j]=mat[i][j-col];
                    }
                }
                return out;
            }
        }
        Matrix<T> concat(Vector<T> vec,int axis=1, bool concat_at_end=true)//默认在列上扩增
        {
            if(axis!=1 && axis!=0)
            {
                cerr<<"维度指定错误"<<endl;
                return *this;
            }
            if((axis==0 && vec.length!=col)||(axis==1 && vec.length!=row))
            {
                cerr<<"维度不匹配"<<endl;
                return *this;
            }
            if(axis==0)
            {
                Matrix<T> mat1d=Matrix(1,col);
                for(int i=0;i<1*col;i++) mat1d.data[i]=vec[i];
                if(concat_at_end)
                {
                    return concat(mat1d,0);
                }
                else
                {
                    return mat1d.concat(*this,0);
                }
            }
            else
            {
                Matrix<T> mat1d=Matrix(row,1);
                for(int i=0;i<1*row;i++) mat1d.data[i]=vec[i];
                if(concat_at_end)
                {
                    return concat(mat1d,1);
                }
                else
                {
                    return mat1d.concat(*this,1);
                }
            }
        }
        //7.楚列斯基分解        
        Matrix<T> cholesky_decomposition()
        {
            //楚列斯基分解：目标矩阵是对称正定阵-方阵
            //A=Lt*L，正定阵类似于正实数，可做开根号操作，楚列斯基分解和开根号等价
            if(row!=col)
            {
                cerr<<"ERROR: 楚列斯基分解的目标矩阵必须是方阵"<<endl;
                return *this;
            }
            Matrix<T> out(row,col);
            out.display();
            for(int i=0;i<row;i++)
            {
                for(int j=i;j<row;j++)
                {
                    T sum=data[j*col+i];
                    for(int k=i-1;k>=0;k--)
                    {
                        sum-=out[i][k]*out[j][k]; 
                        //i,j这一个元素由i行元素与j列元素相乘加和得到
                    }
                    if(i==j)
                    {
                        if(sum<=0)
                        {
                            cerr<<"ERROR: 楚列斯基分解的目标矩阵必须是正定阵"<<endl;
                            return *this;
                        }
                        out[i][i]=sqrt(sum);
                    }
                    else
                    {
                        out[j][i]=sum/out[i][i];
                    }
                }
            }
            return out;
        }

        //8.格拉姆-施密特正交变换--QR分解
        pair<Matrix<T>,Matrix<T>> gram_schmidt_transform()
        {
            Matrix<T> Q(row,col);
            int n=row<col?row:col;
            Matrix<T> R(n,n);
            for(int j=0;j<col;j++)
            {
                for(int i=0;i<row;i++)
                {
                    Q[i][j]=data[i*col+j];
                }

                if(j>0)
                {
                    //先求出点积，即当前向量在之前每一个正交向量上的投影大小
                    for(int f=0;f<j;f++)  //f变量遍历每一个先前的正交向量（列）
                    {
                        T dot=0.0;
                        for(int k=0;k<row;k++) //第f列向量和第j列向量做点积
                            dot=dot+Q[k][f]*Q[k][j];
                        R[f][j]=dot;
                        for(int k=0;k<row;k++) //第j列向量减去点积倍的f向量，即去除f向量方向上的分量，保证正交性
                            Q[k][j]=Q[k][j]-Q[k][f]*dot;
                    }
                }
                
                T sum=0;
                for(int i=0;i<row;i++)
                {
                    //cout<<Q[i][j]<<endl;
                    sum+=pow(Q[i][j],2);
                }
                sum=sqrt(sum);
                R[j][j]=sum;
                for(int i=0;i<row;i++)
                {
                    Q[i][j]=Q[i][j]/sum;
                }
            }
            return {Q,R};
        }

        //9.LU分解
        pair<Matrix<T>,Matrix<T>> lu_decomposition()
        {
            int num_iter=col<row?col:row;
            Matrix<T> L(num_iter,num_iter);
            Matrix<T> U=*this;
            //T *pivot=new T[mat_row];

            //消元过程
            //以行列中小的那个作为迭代数，如果某行主元为零则切换主元不为零的行进行消减，如果剩余行都为零行，则算法提前结束
            for(int iter=0;iter<num_iter;iter++)
            {
                //T factor=pivot[];
                //依次将iter列的行号>iter的元素消成零
                L[iter][iter]=1.0;
                for(int row_idx=iter+1;row_idx<row;row_idx++)
                {
                    //遍历某一行的每个元素进行消减，首先要计算出这一行的iter位消成零需要的系数是多少
                    //然后改行iter位置零，其余元素减去系数和iter行对应元素的乘积
                    T coef =  U[row_idx][iter]/U[iter][iter]; //*注意这里除数不能为零
                    L[row_idx][iter]=coef;

                    for(int col_idx=iter;col_idx<col;col_idx++)
                    {
                        U[row_idx][col_idx]=U[row_idx][col_idx]-U[iter][col_idx]*coef;
                    }
                }
            }

            //发现消元结果中出现了（+/-）1e-16级别的小数，这里我们定义EPS值，限制这些绝对值极小数的出现，强制其归零
            for(int row_idx=0;row_idx<row;row_idx++)
                for(int col_idx=0;col_idx<col;col_idx++)
                    if(!(U[row_idx][col_idx]>EPS || U[row_idx][col_idx]<-EPS))
                    {
                        U[row_idx][col_idx]=0.0;
                    }
            cout<<"消元后的增广矩阵为："<<endl;
            cout<<L<<endl;
            cout<<U<<endl;
            return {L,U};
        }
        
};

