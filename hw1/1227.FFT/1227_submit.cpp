#include <iostream>
#include <complex>
#include <cmath>
using namespace std;
#define cp complex<double>
#define PI acos(-1)
/***
这一版是可以通过的版本
声明：本题所有主要代码均为本人编写。
参考：
1、PI的定义，采用了https://blog.csdn.net/weijifen000/article/details/82691555?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164653173016780265417960%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=164653173016780265417960&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-2-82691555.es_vector_control_group&utm_term=C%2B%2BPI&spm=1018.2226.3001.4187
2、主要思路采用了张驰豪老师上课讲授的算法，在实现上做了一些改动。
3、复数类的使用，参考了：https://horizonwd.blog.csdn.net/article/details/81478582
致谢：非常感谢张驰豪老师给我指出浮点数比较的问题，也感谢助教老师的关心。
***/
void fft(cp *pq, cp *pq_omega, cp omega, int D,int inv)
{
    //注意浮点数的比较，原来张老师提示的abs(omega.real()-1)<1e-8仍然有误差。
    //之前自己写的omega.real()==1非常错误，会导致死循环
    if (D == 1) { 
        for (int i=0;i<D;++i) pq_omega[i] = pq[i];
        return;
    }
    cp *pq_e = new cp[D/2];
    cp *pq_o = new cp[D/2];
    cp *pq_e_omega = new cp[D/2];
    cp *pq_o_omega = new cp[D/2];
    for (int i=0;i<D/2;++i) {pq_e[i] = pq[2*i];}
    for (int i=0;i<D/2;++i) {pq_o[i] = pq[2*i+1];}

    fft(pq_e,pq_e_omega,omega*omega,D/2,inv);
    fft(pq_o,pq_o_omega,omega*omega,D/2,inv);
    pq_omega[0] = pq_e_omega[0]+pq_o_omega[0];//0是特殊情况
    pq_omega[D/2] = pq_e_omega[0]-pq_o_omega[0];
    for (int t=1;t<D/2;++t) {
    //为了简化omega^t的计算，此处利用inv和w的性质(注意，此处的D是每次调用fft时候产生的除以2以后的D)
        pq_omega[t] = pq_e_omega[t]+cp(cos(2*t*PI/D),inv*sin(2*t*PI/D))*pq_o_omega[t];
        pq_omega[t+D/2] = pq_e_omega[t]-cp(cos(2*t*PI/D),inv*sin(2*t*PI/D))*pq_o_omega[t]; 
    }
    delete pq_e;
    delete pq_o;
    delete pq_e_omega;
    delete pq_o_omega;
}
void multiply(cp *p, cp *q, cp *r, int D, int p_order, int q_order)
{
    cp omega(cos(2*PI/D),sin(2*PI/D));
    cp *p_omega = new cp[D];
    cp *q_omega = new cp[D];
    cp *r_omega = new cp[D];
    fft(p,p_omega,omega,D,1);
    fft(q,q_omega,omega,D,1);
    for (int t=0;t<D;++t) r_omega[t] = p_omega[t]*q_omega[t];
    fft(r_omega,r,cp(cos(2*PI/D),-sin(2*PI/D)),D,-1);
    for (int i=0;i<D;++i) r[i] /= D;
    delete p_omega;
    delete q_omega;
    delete r_omega;
}
int main()
{
    int D_p=0, D_q=0,p_order,q_order;
    cin >> p_order >> q_order;
    while ((1<<D_p)<((p_order+1)*2)) ++D_p;
    while ((1<<D_q)<((q_order+1)*2)) ++D_q;
    int D = (D_p > D_q ? D_p : D_q);
    D = 1 << D;

    int *p = new int[D];
    int *q = new int[D];
    cp *cp_p = new cp[D];
    cp *cp_q = new cp[D];
    cp *r = new cp[D];
    for (int i=0;i<p_order+1;++i) {cin >> p[i];cp_p[i] = cp(p[i],0);}
    for (int i=p_order+1;i<D;++i) {p[i] = 0;cp_p[i] = cp(0,0);}
    for (int i=0;i<q_order+1;++i) {cin >> q[i];cp_q[i] = cp(q[i],0);}
    for (int i=q_order+1;i<D;++i) {q[i] = 0;cp_q[i] = cp(0,0);}
    multiply(cp_p,cp_q,r,D, p_order, q_order);
    for (int i=0;i<p_order+q_order+1;++i) cout <<  (int)(r[i].real()+0.5) << ' ';
    delete p;
    delete q;
    delete cp_p;
    delete cp_q;
    delete r;
    return 0;
}