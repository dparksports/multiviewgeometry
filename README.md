# Multi View Geometry Library for Autonomous Robots
Open source library in C++ for autonomous driving platform and autonomous robots 

## What is it?

- This library implements the multivew geometry algorithms for machine vision.
- Used in autonomous driving platform or autonomous robots including autonomous drones, rovers and submarines.

## What does it do?
To enable an autonomous robot 

- 1) to see a scene 
- 2) to track both static and dynmaic objects.
- 3) to construct the world in real time.
- 4) to estimate the norm vector of direction and velocity of a dynamic agent.
- 5) to estimate the traffic signs and signals.
- 6) robustly estimate with arcmin of 1 degree at few centimeters.


## Why another platform?

- To support a non-vendor dependent implemenation, so there is no dependency in any major companies like NVIDA, Intel, AMD, and others.


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

- To provide the baseline implmenation of noble neural network architecture for autonomous robots including self-driving platform.
- Towards creation of noble neural network architure to support multi-modality.

## 
