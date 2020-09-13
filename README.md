# Multi View Geometry Library for Autonomous Robots
Open source library in C++ for autonomous driving platform and autonomous robots 

## What is it?

- This library implements the multivew geometry algorithms for machine vision.
- Used in autonomous driving platform or autonomous robots including autonomous drones, rovers and submarines.

## What does it do?
To enable an autonomous robot 

1) to scan a scene
2) to track dynmaic objects in static background.
3) to register temporal point clouds
4) to reconstrct the real world in real time.
4) to estimate the norm vectors of direction and velocity of dynamic agents.
5) to estimate the traffic signs and signals.
6) robustly estimate point clouds in arcmin of 1 degree at few centimeters.


## Why another platform?

- To provide an independent implemenation for the public, without having the dependency on any commercial libraries.


## What's the implementation roadmap?

   The plan is to implement:
   
- Epipolar Geometry constraint, Multiview Geometry
- Namely,
- Essential Matrix Estimation
- Foundamental Matrix Estimation
- Direct Linear Transform (8 point algorithm)
- 5 point algorithm
- Nonlinear and linear optimizations
- Error Minimization of Nonliner and linear systems
- Norm 2 Least Square Minimization
- Norm-Forbenius LS Min
- Jacobian Matrix
- Hessian Matrix
- GBA (Generic Bundle Adjustment)
- Feature Extractions
- Pairwise Matching
- RANSAC 
- Differentiation
- Gradient Descent

  For these, in real time
   
- Structure from Motion
- Sparse 3D reconstruction
- Dense 3D reconstruction
- Photogrammetry
- Visual Odometry
- Direct Odometry


## What's the vision?

- To provide the baseline implmenation for a noble neural network architecture for reliable and safe autonomous robots including self-driving vehicles.
- Working towards the creation of a noble neural network architure to support robust, efficient and safe multi-modality neural network.

## 
