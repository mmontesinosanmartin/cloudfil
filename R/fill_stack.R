fill_stack <- function(clr.img, cld.img, w = 10){
  
  # format
  npxx <- dim(clr.img)[1]
  npxy <- dim(clr.img)[2]
  clr.mat <- as.matrix(clr.img[])
  cld.mat <- as.matrix(cld.img[])

  # Output 
  setValues(cld.img, fill_image(clr.mat, cld.mat, w, npxx, npxy))
  
}
