## Estimates a projection matrix


# What is a project matrix?
Using the 3d points in real world, compute a project matrix to further estimate the corresponding 2d points in an image view.

# What are the methods?
- Two methods are provided.
1) A Singular Vector Decomposition (SVD) method to compute the orthogonal matrix of Eigenvectors of A_T*A by
using the Jacobian Eigenvectors which produces the tilda U and tilda V.
2) A Least Quare method by using a 8 point formula 

# What is the camera center?
- Estimates the camera center by estimate Q of a projection matrix.
- C = [-Q^-1 b / 1]
- Null-space camera of projection matrix: MC = 0
- M = [Q | b]

# What is the residual calculation?
- Given the 2d points in an image plane.
- e.g.) for a minimizing reprojection error.
- One needs to calculate the norm between the estimated 2d points by using a project matrix in homogenous coordinates and the given 2d points, which may be GT.
