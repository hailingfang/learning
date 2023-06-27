#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/Core>
 

int main()
{
/*    
    Eigen::ArrayXi ar(5), br(5);
    int i = 0;

    for (i = 0; i < 5; i++) {
        ar(i) = i;
        br(i) = i * 2;
    }
    
    std::cout << ar << '\n' << std::endl;
    std::cout << br << '\n' << std::endl;
    std::cout << ar * br << std::endl;


    Eigen::SparseMatrix<double, Eigen::ColMajor, long long> sm(100, 100);
    sm.coeffRef(0, 0) = 1.5;
    sm.coeffRef(3, 4) = 1.6;
    sm.insert(5, 6) = 1.7;
    std::cout << "sm.rows: " << sm.rows() << std::endl;
    std::cout << "sm.nonZeros: " << sm.nonZeros() << std::endl;
    std::cout << "sm.outerSize: " << sm.outerSize() << std::endl;
    std::cout << "sm.innerSize: " << sm.innerSize() << std::endl;
    for (int k = 0; k < sm.outerSize(); ++k) {
        for (Eigen::SparseMatrix<double, Eigen::ColMajor, long long>::InnerIterator it(sm, k); it; ++it) {
            std::cout << it.value() << std::endl;
            std::cout << it.row() << std::endl;
            std::cout << it.col() << std::endl;
            std::cout << it.index() << std::endl;
        }
    }

    std::cout << "Eigen::ColMajor: "<< Eigen::ColMajor << std::endl;

    Eigen::SparseMatrix<double, 0, long long> smt;
    smt.resize(1,1);
    smt.startVec(0);
    smt.insertBack(0, 0) = 3.1415;
    smt.finalize();
    std::cout << smt.nonZeros() << std::endl;
    std::cout << smt.coeffRef(0,0) << std::endl;
*/  
    Eigen::SparseMatrix<double, 0, long long> smt2;
    smt2.resize(0,0);
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double, 0, long long>> ldlt_smt2(smt2);
    Eigen::SparseMatrix<double, 0, long long> ressm;
    Eigen::SparseMatrix<double, 0, long long> tmp;
    ressm.resize(0, 0);
    tmp.resize(0,0);
    ressm.setIdentity();

    tmp = ldlt_smt2.solve(ressm).eval();


    return 0;
}
