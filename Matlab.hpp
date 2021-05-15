#include"Vector.hpp"
#include"Matrix.hpp"
//3.向量乘矩阵
template<class T>
Vector<T> operator*(Vector<T> &vec, Matrix<T> &mat)
{
    //cout<<"v*m"<<endl;
    if(vec.length!=mat.row)
    {
        cerr<<"向量与矩阵维度不符，无法相乘"<<endl;
        return vec;
    }
    Vector<T> out(mat.col);
    
    int row=mat.row;
    int col=mat.col;
    for(int c=0;c<col;c++)
    {
        T sum=0;
        for(int r=0;r<row;r++)
        {
            sum+=vec[r]*mat[r][c];
        }
        out[c]=sum;
    }
    //out.display();
    return out;
}

//4.矩阵乘向量
template<class T>
Vector<T> operator*(Matrix<T> &mat,Vector<T> &vec)
{
    cout<<"m*v"<<endl;
    if(vec.length!=mat.col)
    {
        cerr<<"向量与矩阵维度不符，无法相乘"<<endl;
        return vec;
    }
    Vector<T> out(mat.row);
    
    int row=mat.row;
    int col=mat.col;
    for(int r=0;r<row;r++)
    {
        T sum=0;
        for(int c=0;c<col;c++)
        {
            sum+=vec[c]*mat[r][c];
        }
        out[r]=sum;
    }
    //out.display();
    return out;
}

//5.向量点乘
template<class T>
T operator*(Vector<T> &vec1,Vector<T> &vec2)
{
    return vec1.dot(vec2);
}
//6.单位阵
template<class T>
Matrix<T> eye(int n)
{
    //TODO
    //n<=0
    Matrix<T> out(n,n); //先获取一个零矩阵
    for(int i=0;i<n;i++)
    {
        out[i][i]=1;
    }
    //out.display();
    return out;
}

//7.拼接
template<class T>
Matrix<T> concat(Matrix<T> mat1, Matrix<T> mat2,int axis=1)
{
    return mat1.concat(mat2,axis);
}
template<class T>
Matrix<T> concat(Matrix<T> mat,Vector<T> vec,int axis=1)
{
    return mat.concat(vec,axis);
}
template<class T>
Matrix<T> concat(Vector<T> vec,Matrix<T> mat,int axis=1)
{
    return mat.concat(vec,axis,false); //concat_at_end=false，即向量拼接在矩阵前
}

//8.数乘
template<class T>
Vector<T> operator*(int factor, Vector<T> vec)
{
    Vector<T> out(vec.length);
    for(int i=0;i<vec.length;i++)
        out[i]=vec[i]*factor;
    return out;
}
template<class T>
Vector<T> operator*(Vector<T> vec,int factor)
{
    Vector<T> out(vec.length);
    for(int i=0;i<vec.length;i++)
        out[i]=vec[i]*factor;
    return out;
}
template<class T>
Matrix<T> operator*(Matrix<T> mat,int factor)
{
    Matrix<T> out(mat.row, mat.col);
    for(int i=0;i<mat.row;i++)
        for(int j=0;j<mat.col;j++)
            out[i][j]=mat[i][j]*factor;
    return out;
}
template<class T>
Matrix<T> operator*(int factor, Matrix<T> mat)
{
    Matrix<T> out(mat.row, mat.col);
    for(int i=0;i<mat.row;i++)
        for(int j=0;j<mat.col;j++)
            out[i][j]=mat[i][j]*factor;
    return out;
}

//9.重载运算符<<
template<class T>
ostream &operator<<(ostream &os, const Matrix<T> &mat)
{
    int row=mat.row;
    int col=mat.col;
    if(row==0 || col==0)
    {
        os<<"本矩阵为空"<<endl;
        return os;
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            os<<setprecision(4)<<setw(8)<<mat[i][j]<<" ";
        }
        if(i!=row-1)
            os<<endl;
    }
    return os;
}
template<class T>
ostream &operator<<(ostream &os, const Vector<T> &vec)
{
    int length=vec.length;
    if(length==0)
    {
        os<<"本向量为空"<<endl;
        return os;
    }
    for(int i=0;i<length;i++)
    {
        os<<setw(5)<<vec.data[i]<<" ";
    }
    return os;
}

//10.高斯消元法
template<class T>
Vector<T> Gauss_elimination(Matrix<T> &mat, Vector<T> &vec)
{
    int mat_row=mat.row;
    int mat_col=mat.col;
    int vec_len=vec.length;
    if(mat_col!=vec_len) //TODO
    {
        cerr<<"矩阵列长度与向量长度不等，线性方程无解"<<endl;
        return vec;
    }
    if(mat_row!=mat_col) //TODO
    {
        cerr<<"矩阵行列长度不等，线性方程无解"<<endl;
        return vec;
    }
    Vector<T> out(vec_len); //返回求解结果
    Matrix<T> augmented_matrix=concat(mat,vec); // 增广矩阵，concat默认在列上拼接（axis=1）
    int amat_col=augmented_matrix.col;
    int amat_row=augmented_matrix.row;

    //T *pivot=new T[mat_row];
    int num_iter=amat_col<amat_row?amat_col:amat_row;

    //1.消元过程
    //以行列中小的那个作为迭代数，如果某行主元为零则切换主元不为零的行进行消减，如果剩余行都为零行，则算法提前结束
    for(int iter=0;iter<num_iter;iter++)
    {
        //T factor=pivot[];
        //依次将iter列的行号>iter的元素消成零
        for(int row_idx=iter+1;row_idx<amat_row;row_idx++)
        {
            //遍历某一行的每个元素进行消减，首先要计算出这一行的iter位消成零需要的系数是多少
            //然后改行iter位置零，其余元素减去系数和iter行对应元素的乘积
            T coef =  augmented_matrix[row_idx][iter]/augmented_matrix[iter][iter]; //*注意这里除数不能为零
            for(int col_idx=iter;col_idx<amat_col;col_idx++)
            {
                augmented_matrix[row_idx][col_idx]=augmented_matrix[row_idx][col_idx]-augmented_matrix[iter][col_idx]*coef;
            }
        }
    }

    //发现消元结果中出现了（+/-）1e-16级别的小数，这里我们定义EPS值，限制这些绝对值极小数的出现，强制其归零
    for(int row_idx=0;row_idx<amat_row;row_idx++)
        for(int col_idx=0;col_idx<amat_col;col_idx++)
            if(!(augmented_matrix[row_idx][col_idx]>EPS || augmented_matrix[row_idx][col_idx]<-EPS))
            {
                augmented_matrix[row_idx][col_idx]=0.0;
            }
    cout<<"消元后的增广矩阵为："<<endl;
    cout<<augmented_matrix<<endl;

    //2.回代过程（back substitution）
    for(int i=out.length-1;i>=0;i--)
    {
        out[i]=augmented_matrix[i][amat_col-1];
        for(int j=i+1;j<num_iter;j++)
        {
            out[i]-=augmented_matrix[i][j]*out[j];
        }
        out[i]/=augmented_matrix[i][i];
    }

    //delete pivot;
    return out;
}


