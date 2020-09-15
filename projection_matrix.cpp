#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/eigen.hpp>
#include <iostream>
#include <chrono>
#include <Eigen/Core>
#include <Eigen/Cholesky>
#include <Eigen/Dense>

using namespace std;
using namespace std::chrono;
using namespace Eigen;
using namespace std;

void compute_projection_matrix_SVD() {
    Eigen::MatrixXf pts2d(6,2), pts3d(6,3);
    pts3d <<
          1.5706,-0.1490,0.2598,
            -1.5282, 0.9695, 0.3802,
            -0.6821, 1.2856, 0.4078,
            0.4124, -1.0201, -0.0915,
            1.2095, 0.2812, -0.1280,
            0.8819, -0.8481, 0.5255;

    pts2d <<
          1.0486, -0.3645,
            -1.6851, -0.4004,
            -0.9437, -0.4200,
            1.0682, 0.0699,
            0.6077, -0.0771,
            1.2543, -0.6454;


    assert(pts2d.rows() == pts3d.rows() && pts2d.cols() == 2 && pts3d.cols() == 3);

    const size_t rows = pts3d.rows() * 2;
    size_t cols = 11;
    cols = 12;

    Eigen::MatrixXf ASVD(rows, cols);
    for (int i = 0; i < rows; i += 2) {
        float X = pts3d(i / 2, 0);
        float Y = pts3d(i / 2, 1);
        float Z = pts3d(i / 2, 2);
        float x = pts2d(i / 2, 0);
        float y = pts2d(i / 2, 1);
        ASVD.row(i) << X, Y, Z, 1, Eigen::MatrixXf::Zero(1, 4), -x * X, -x * Y, -x * Z, -x;
        ASVD.row(i + 1) << Eigen::MatrixXf::Zero(1, 4), X, Y, Z, 1, -y * X, -y * Y, -y * Z, -y;
    }

    // Compute the orthogonal matrix of eigenvectors of A_T*A
    Eigen::MatrixXf eigenvectors = ASVD.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).matrixV();
    Eigen::MatrixXf smallest = eigenvectors.col(eigenvectors.cols() - 1);

    cv::Mat cvSol;
    cv::eigen2cv(smallest, cvSol);
    cv::Mat projectionMatrixSVD = cvSol.reshape(0, 3);
}

void compute_projection_matrix_LS() {
    Eigen::MatrixXf pts2d(6,2), pts3d(6,3);
    pts3d <<
          1.5706,-0.1490,0.2598,
            -1.5282, 0.9695, 0.3802,
            -0.6821, 1.2856, 0.4078,
            0.4124, -1.0201, -0.0915,
            1.2095, 0.2812, -0.1280,
            0.8819, -0.8481, 0.5255;

    pts2d <<
          1.0486, -0.3645,
            -1.6851, -0.4004,
            -0.9437, -0.4200,
            1.0682, 0.0699,
            0.6077, -0.0771,
            1.2543, -0.6454;


    std::cout <<pts3d.rows()  << "," << pts3d.cols() << std::endl;
    std::cout <<pts2d.rows()  << "," << pts2d.cols() << std::endl;

    std::cout << pts3d << endl;
    std::cout << pts2d << endl;

    assert(pts2d.rows() == pts3d.rows() && pts2d.cols() == 2 && pts3d.cols() == 3);
    // Set up A and b matrices.
    const size_t rows = pts3d.rows() * 2;
    size_t cols = 11;
    Eigen::MatrixXf A(rows, cols);
    Eigen::MatrixXf b(rows, 1);

    // Build A and b matrices
    for (int i = 0; i < rows; i += 2) {
        float X = pts3d(i / 2, 0);
        float Y = pts3d(i / 2, 1);
        float Z = pts3d(i / 2, 2);
        float x = pts2d(i / 2, 0);
        float y = pts2d(i / 2, 1);
        A.row(i) << X, Y, Z, 1, Eigen::MatrixXf::Zero(1, 4), -x * X, -x * Y, -x * Z;
        A.row(i + 1) << Eigen::MatrixXf::Zero(1, 4), X, Y, Z, 1, -y * X, -y * Y, -y * Z;
        b.row(i) << x;
        b.row(i + 1) << y;
    }

    cols = 12;

    // Solve least squares
    Eigen::MatrixXf leastsquare = (A.transpose() * A).ldlt().solve(A.transpose() * b);
    leastsquare.conservativeResize(leastsquare.rows() + 1, leastsquare.cols());
    leastsquare(leastsquare.rows() - 1, 0) = 1;

    cv::Mat leaseSquareCV;
    cv::eigen2cv(leastsquare, leaseSquareCV);
    cv::Mat projectionMatrix = leaseSquareCV.reshape(0, 3);
    std::cout << "projectionMatrix:" << projectionMatrix << endl;
    std::cout << projectionMatrix.size()  << endl;
}

void compute_camera_center(cv::Mat projectionMatrix) {
        // Find center of camera
    cv::Mat Q = projectionMatrix.colRange(0, 3);
    std::cout << "Q:" << Q << endl;
    std::cout << Q.size()  << endl;

    cv::Mat invQ = Q.inv();
    std::cout << "invQ:" << invQ << endl;
    std::cout << invQ.size()  << endl;

    cv::Mat invQnegative = -1.f * invQ;
    std::cout << "invQnegative:" << invQnegative << endl;

    cv::Mat m4 = projectionMatrix.col(3);
    std::cout << "m4:" << m4 << endl;

    cv::Mat cameraCenter = invQnegative * m4;
    std::cout << "cameraCenter:" << cameraCenter << endl;
}


int main() {
    compute_projection_matrix_LS();
    compute_projection_matrix_SVd();
    compute_camera_center();
}