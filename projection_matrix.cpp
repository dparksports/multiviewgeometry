#include <Eigen/Core>
#include <Eigen/Cholesky>
#include <Eigen/Dense>

#include <opencv2/core/core.hpp>
#include <opencv2/core/eigen.hpp>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace Eigen;
using namespace std;

cv::Mat compute_projection_matrix_SVD(Eigen::MatrixXf pts2d, Eigen::MatrixXf pts3d) {
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

    return projectionMatrixSVD;
}

cv::Mat compute_projection_matrix_LS(Eigen::MatrixXf &pts2d, Eigen::MatrixXf &pts3d) {
    assert(pts2d.rows() == pts3d.rows() && pts2d.cols() == 2 && pts3d.cols() == 3);

    const size_t rows = pts3d.rows() * 2;
    size_t cols = 11;
    Eigen::MatrixXf A(rows, cols);
    Eigen::MatrixXf b(rows, 1);

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

    Eigen::MatrixXf leastsquare = (A.transpose() * A).ldlt().solve(A.transpose() * b);
    leastsquare.conservativeResize(leastsquare.rows() + 1, leastsquare.cols());
    leastsquare(leastsquare.rows() - 1, 0) = 1;

    cv::Mat leaseSquareCV;
    cv::eigen2cv(leastsquare, leaseSquareCV);
    cv::Mat projectionMatrix = leaseSquareCV.reshape(0, 3);
    std::cout << "projectionMatrix:" << projectionMatrix << endl;
    std::cout << projectionMatrix.size()  << endl;

    return projectionMatrix;
}

void compute_camera_center(cv::Mat projectionMatrix) {
    cv::Mat Q = projectionMatrix.colRange(0, 3);
    cv::Mat invQ = Q.inv();
    cv::Mat invQnegative = -1.f * invQ;
    cv::Mat m4 = projectionMatrix.col(3);
    cv::Mat cameraCenter = invQnegative * m4;
    std::cout << "cameraCenter:" << cameraCenter << endl;
}

void estimate_residual(Eigen::MatrixXf &pts2d, Eigen::MatrixXf &pts3d, cv::Mat projectionMatrix) {
    cv::Mat cv3dpts, cv2dpts;
    cv::eigen2cv(pts3d, cv3dpts);
    cv::eigen2cv(pts2d, cv2dpts);

    cv::Mat lastPt2D = cv2dpts.row(0);
    cv::Mat lastPt3D = cv3dpts.row(0);

    cv::Mat homogenousPt3D;
    homogenousPt3D.push_back(lastPt3D.at<float>(0,0));
    homogenousPt3D.push_back(lastPt3D.at<float>(0,1));
    homogenousPt3D.push_back(lastPt3D.at<float>(0,2));
    homogenousPt3D.push_back(1.f);

    cv::Mat projected = projectionMatrix * homogenousPt3D;
    for (size_t col = 0; col < projected.cols; col++) {
        float s = projected.at<float>(2, col);
        projected.col(col) = projected.col(col) / s;
    }

    cv::Mat projected2d = projected.rowRange(0, 2);
    cv::Mat transposed2D =  lastPt2D.t();
    double residual = cv::norm(projected2d, transposed2D);
    std::cout << "residual:" << residual << endl;
}

void test_projection_matrix() {
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

    cv::Mat p_matrix_LS = compute_projection_matrix_LS( pts2d, pts3d);
    cv::Mat p_matrix_SVD = compute_projection_matrix_SVD(pts2d, pts3d);
    compute_camera_center(p_matrix_LS);
    compute_camera_center(p_matrix_SVD);
    estimate_residual(pts2d, pts3d, p_matrix_LS);
    estimate_residual(pts2d, pts3d, p_matrix_SVD);
}

int main() {
    test_projection_matrix();
}