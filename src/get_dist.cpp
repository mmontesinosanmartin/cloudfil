// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
// #include "POOL.h"
using namespace Rcpp;

// [[Rcpp::export]]
arma::vec get_dist(arma::uvec ngbs,
                   int i,
                   int w,
                   int nrow,
                   int ncol) {
  // center row-col
  int row = floor(i / ncol);
  int col = i - (ncol * row);
  // neighbors row-cols
  arma::uvec rows = floor(ngbs / ncol);
  arma::uvec cols = ngbs - (ncol * rows);
  // distance
  arma::vec dx = arma::conv_to<arma::vec>::from(cols) - (double) col;
  arma::vec dy = arma::conv_to<arma::vec>::from(rows) - (double) row;
  arma::vec out = sqrt(arma::pow(dx, 2) + arma::pow(dy, 2)) / (double) w;
  // return output
  return out;
}