#include<iostream>
#include<iomanip>
#include<cmath>
#include"Matlab.hpp"
using namespace std;
#define EPS 1e-10


int main()
{
    int length=3;
    Vector<double> vec(length);
    for(int i=0;i<length;i++)
    {
        vec[i]=i*2;
    }
    cout<<"vec:"<<endl;
    vec.display();

    Matrix<double> mat(3,3);
    mat.init_value(1);
    mat[0][1]=2.0;
    cout<<"mat:"<<endl;
    mat.display();

    ////向量矩阵乘
    //Vector<double> out1=vec*mat;
    //cout<<"out1(vec*mat):"<<endl;
    //out1.display();

    ////矩阵向量乘
    //Vector<double> out2=mat*vec;
    //cout<<"out2(mat*vec):"<<endl;
    //out2.display();

    ////向量点乘
    //cout<<"out3(vec*vec):"<<vec*vec<<endl;

    ////对角矩阵
    //Matrix<double> out4=eye<double>(3);
    //cout<<"out4(eye):"<<endl;
    //out4.display();
    
    ////矩阵转置
    //matrix<double> out5=mat.transpose();
    //cout<<"out5(transpose):"<<endl;
    //out5.display();
    
    ////矩阵拼接
    //Matrix<double> out6=mat.concat(mat);
    //cout<<"out6(concat):"<<endl;
    //out6.display(); 
    //Matrix<double> out7=mat.concat(mat.transpose(),0);
    //cout<<"out7(concat):"<<endl;
    //out7.display();
    
    ////矩阵拼接
    //Matrix<double> out8=mat.concat(vec);
    //cout<<"out8(concat):"<<endl;
    //out8.display(); 
    //Matrix<double> out9=mat.concat(vec,0);
    //cout<<"out9(concat):"<<endl;
    //out9.display();

    ////矩阵拼接
    //Matrix<double> out7=concat(mat,mat,0);
    //cout<<"out7(concat):"<<endl;
    //out7.display(); 
    //Matrix<double> out8=concat(mat,vec,0);
    //cout<<"out8(concat):"<<endl;
    //out8.display(); 
    //Matrix<double> out9=concat(vec,mat,0);
    //cout<<"out9(concat):"<<endl;
    //out9.display();

    ////正定阵，用于验证cholesky分解
    //mat[0][0]=4;
    //mat[0][1]=-2;
    //mat[0][2]=2;
    //mat[1][0]=-2;
    //mat[1][1]=2;
    //mat[1][2]=-4;
    //mat[2][0]=2;
    //mat[2][1]=-4;
    //mat[2][2]=11;
    //mat.display();
    //Matrix<double> out9=mat.cholesky_decomposition();
    //cout<<"out9(concat):"<<endl;
    //out9.display();

    ////格拉姆-施密特正交变换，QR分解的基础
    //Matrix<double> mat_gram(3,2);
    //mat_gram[0][0]=1;
    //mat_gram[0][1]=-4;
    //mat_gram[1][0]=2;
    //mat_gram[1][1]=3;
    //mat_gram[2][0]=2;
    //mat_gram[2][1]=2;
    //cout<<endl;
    //cout<<"原矩阵为："<<endl;
    //mat_gram.display();
    //pair<Matrix<double>,Matrix<double>> qr=mat_gram.gram_schmidt_transform();
    //Matrix<double> out9=qr.first;
    //Matrix<double> out10=qr.second;
    //cout<<"Q矩阵为："<<endl;
    //cout<<out9<<endl;
    //cout<<"R矩阵为："<<endl;
    //cout<<out10<<endl;
    
    //Matrix<double> out9=4*mat;
    //cout<<"数乘结果为："<<endl;
    //out9.display();

    //Matrix<double> out9=4*mat;
    //cout<<"数乘结果为："<<endl;
    //out9.display();
    mat[0][0]=1;
    mat[0][1]=2;
    mat[0][2]=-1;
    mat[1][0]=2;
    mat[1][1]=1;
    mat[1][2]=-2;
    mat[2][0]=-3;
    mat[2][1]=1;
    mat[2][2]=1;
    vec[0]=3;
    vec[1]=3;
    vec[2]=-6;

    cout<<"A矩阵为："<<endl;
    cout<<mat<<endl;
    cout<<"b向量为："<<endl;
    cout<<vec<<endl;
    //Vector<double> out=Gauss_elimination(mat,vec);
    //cout<<"Ax=b 线性方程求解结果为："<<endl;
    //cout<<out<<endl;
    mat.lu_decomposition();
    
    return 0;
}
