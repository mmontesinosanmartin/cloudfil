#ifndef POOL_H
#define POOL_H

#include <RcppArmadillo.h>
arma::uvec get_ngbs(int i, int w, int nrow, int ncol);

#include <RcppArmadillo.h>
arma::uvec get_dist(arma::uvec ngbs, int i, int w, int nrow, int ncol);

#endif