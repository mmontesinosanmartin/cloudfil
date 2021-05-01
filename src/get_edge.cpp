//[[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace Rcpp;

//[[Rcpp::export]]
arma::uvec get_edge(int i , int w, int ncols, int nrows){
  // center cell
  int rowi = floor(i / ncols);
  int coli = i - (ncols * rowi);
  // clamp window
  int wcs = -w; if(coli- w < 0) wcs = - coli;
  int wce =  w; if(coli + w > (ncols - 1)) wce = ncols - coli - 1;
  int wrs = -w; if(rowi - w < 0) wrs = - rowi;
  int wre =  w; if(rowi + w > (nrows - 1)) wre = nrows - rowi - 1;
  // top-bottom rows
  arma::vec top = ((rowi - wrs) * ncols) + (coli + arma::regspace<arma::vec>(-wcs, wce));
  arma::vec bot = top + ((2 * w) * ncols);
  // // left-right columns
  arma::vec lft = (rowi + arma::regspace<arma::vec>(-w, w)) * ncols + (coli - w);
  arma::vec rgt = lft + (coli + w);
  // return
  arma::uvec trlb = arma::conv_to<arma::uvec>::from(join_cols(top, rgt, bot, lft));
  arma::uvec edge = arma::sort(arma::unique(trlb));
  return edge;
}
