fill_kmeans <- function(clr.img, cld.img, k = 4){
  
  
  clr.mat <- clr.img[]
  cld.mat <- cld.img[]
  
  clss <- kmeans(clr.mat, centers = k)
  epsl <- clr.img - setValues(clr.img, clss$centers[clss$cluster,])
  kcnt <- do.call(rbind, lapply(1:k, function(i){
    apply(cld.mat[which(clss$cluster == i),], 2, median, na.rm = TRUE)
  }))
  out <- setValues(cld.img, kcnt[clss$cluster,]) + epsl
  out <- stack(lapply(1:nlayers(out), function(i, r1, r2){
    .lm_band(r1[[i]], r2[[i]])
  }, r1 = out, r2 = cld.img))
  out[][!is.na(cld.img[][,1]),] <- cld.img[][!is.na(cld.img[][,1]),]
  out
}

.lm_band <- function(r1, r2){
  x <- r1[]; y <- r2[]; lmod <- lm(y~x);
  out <- raster(r1)
  out[] <- predict(lmod, data.frame(x = x))
  out
}
