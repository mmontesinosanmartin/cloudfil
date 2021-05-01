fill_stack <- function(clr.img, cld.img, w = 10){
  
  # input
  npxx <- dim(clr.img)[1]
  npxy <- dim(clr.img)[2]
  nbnd <- dim(clr.img)[3]
  clr.mat <- as.matrix(clr.img[])
  cld.mat <- as.matrix(cld.img[])
  
  # output
  out <- .gen_tmp(raster(cld.img), (nbnd + 1))

  # Output 
  out <- setValues(out, fill_image(clr.mat, cld.mat, w, npxx, npxy))
  names(out) <- c(names(cld.img), "sp.wgt")
  list(img = out[[(1:nbnd)]], flag = out[[(nbnd+1)]])
}
