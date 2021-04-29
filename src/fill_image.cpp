//[[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
// #include "POOL.h"
using namespace Rcpp;

arma::uvec get_ngbs(int i, int w, int nrow, int ncol) {
  // current row-col
  int row = floor(i / ncol);
  int col = i - (ncol * row);
  // window limits
  int wcs = -w; if(col-w < 0) wcs = - col;
  int wce =  w; if((col + w) > (ncol - 1)) wce = ncol - col -1;
  int wrs = -w; if(row-w < 0) wrs = - row;
  int wre =  w; if(row + w > nrow - 1) wre = nrow - row - 1;
  // initialize output
  int wln = (abs(wcs) + abs(wce) + 1) * (abs(wrs) + abs(wre) + 1);
  arma::uvec out(wln);
  // sliding indexes
  size_t z = 0;
  for(int j = wrs; j <= wre; j++){
    for(int k = wcs; k <= wce; k++){
      out(z) = (ncol * j) + i + k;
      z++; 
    }
  }
  // return output
  return out;
}

// Fills a (multi-band) cloudy image
// ref: clear-sky image
// cld: cloud-covered image
// w: size of the window leg
// nsim: number of similar pixels
// nrow: number of pixels vertically
// ncol: number of pixels horizontally

//[[Rcpp::export]]
arma::mat fill_image(arma::mat ref,
                     arma::mat cld,
                     int w,
                     int nrow,
                     int ncol){
  // initialize output
  arma::mat out = cld;
  // cloudy/clear px: clouds affect all bands equally
  arma::uvec cldpx = arma::find_nonfinite(cld.col(0));
  // for each cloudy pixel
  for(unsigned int j = 0; j < cldpx.n_elem; j++){
    int i = cldpx[j];
    // get neighbors
    arma::uvec ngbs = get_ngbs(i, w, nrow, ncol);
    arma::mat  cldi = cld.rows(ngbs);
    // clear neighbors
    arma::uvec valngb = arma::find_finite(cldi.col(0));
    arma::uvec ngbclr = ngbs(valngb);
    arma::mat cldclr = cld.rows(ngbclr);
    arma::mat refclr = ref.rows(ngbclr);
    // spatio-spectral similarity
    // arma::vec dssim = 1 / get_dist(ngbclr, i, w, nrow, ncol);
    arma::vec spsim = 1 / sqrt(sum(square(refclr.each_row() - ref.row(i)), 1));
    // spatio-spectral weights
    arma::vec spwgt = spsim / sum(spsim);
    // arma::vec dswgt = dssim / sum(dssim);
    arma::vec simis = spwgt; //% dssim;
    // predictors
    arma::mat deltat = cldclr - refclr;
    arma::mat deltas = cldclr;
    // prediction
    double w1 = (double) ngbclr.n_elem / (double) pow((2 * w + 1), 2);
    double w2 = 1. - w1;
    arma::rowvec shat = sum(deltas.each_col() % simis, 0);
    arma::rowvec that = sum(deltat.each_col() % simis, 0)+ ref.row(i);
    out.row(i) = (w1 * shat) + (w2 * that);
  }
  // return filled
  return out;
}