#pragma once

#include <iostream>
#include <eigen3/Eigen/Dense>

/*********************************
 *  RBF : PROCEDURAL GENERATION  *
 *********************************/

#define WORLD_TAILLE 20

float phi(const float a);
float phi1(const float a);
float phi2(const float a);
Eigen::MatrixXd getMap (const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf values);
Eigen::VectorXf findOmega (const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf values);
int findValue(const int i, const int j, const Eigen::MatrixXf ControlPoints, const Eigen::VectorXf w);