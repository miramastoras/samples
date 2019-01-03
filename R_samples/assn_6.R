# Mira Mastoras
# Assignment 6 


library(ggplot2)
#Question 1
# read digits function 

read_digits = function(file_path) {
  image_df = read.table(file_path, header = F, sep = "")
  return (image_df)
}

test_table = read_digits("/Users/miramastoras/sta141a/digits/test.txt")
train_table = read_digits("/Users/miramastoras/sta141a/digits/train.txt")

#Question 2

#What does each digit look like on average? 

#combined data, but i ended up just using the training set 
all_image_data = rbind.data.frame(test_table, train_table)
all_image_data

#rename V1 to be "class"
colnames(train_table)[colnames(train_table) == "V1"] = "class"

#split data by class
split_data = split(train_table, train_table$class)

#find means in each column for pixels in each class
avg_data = lapply(split_data, colMeans)
 
# convert to a matrix
avg_data = lapply(avg_data, as.matrix)

#subset 
test_image_zero = avg_data$`0`[-1,1]
#convert to matrix
test_zero = as.matrix(test_image_zero)
typeof(test_zero)
# coerce into a 16X16 matrix
first = matrix(test_zero, 16, 16, byrow=T)
# apply the image function 
image(t(apply(first, 2, rev)), col=grey(seq(0,1,length=256)))

# Generalized image function

get_images = function(DF_element) { # input is avg_data$'class'
  test_image = DF_element[-1,1]
  test_matrix = as.matrix(test_image)
  first = matrix(test_matrix,16, 16, byrow=T)
  image(t(apply(first, 2, rev)), col=grey(seq(0,1,length=256))) # from Stack Overflow
}

par(mfrow = c(3,4))
lapply(avg_data,get_images)


# Which pixels seem to be the most useful ones for classification ? 
# this is asking which pixel location in the matrix is the most or least variable
# need to get the variances across each of the pixel locations in the 16 x 16 matrix 
# make a heat map of the variances 


#remove class label 
test_tbl = subset(test_table, select = -c(V1))
#get the variance 
var_data = lapply(test_tbl, var)
var_data= as.numeric(var_data) # make it numeric before making the matrix - Piazza
var_data = as.matrix(var_data)
#coerce to 16x16 matrix
var_data_16X16 = matrix(var_data,16, 16, byrow=T)

#variance heatmap 

par(mfrow = c(1,1)) #resetting the grid
image(t(apply(var_data_16X16, 2, rev)), col=grey(seq(1,0,length=256)))
class(var_data_16X16)


# Question 3: KNN function 

# need to calculate distance matrix between K neighbors - distances of all the points between the two 
# 16x16 matrices

# this function iterates through and finds labels for the K nearest neighbors
# returns a vector of the labels
find_k_labels = function(k, row_ordered, correct_dist, combined, m){
  x = 1
  labels = vector(mode = "list", length = k) # preallocate a vector of labels based on K 
  while (x <= k){
    positions = which(correct_dist == row_ordered[x], arr.ind=T) #getting row & col number in distance matrix with the k distance value
    label = combined[(positions[2]) + m, 1] # gives column of original distance matrix, and position to draw label from 
    labels[x] = label
    x = x + 1
  }
  return(labels)
}

# this function takes in vector of labels for K nearest neighbors and decides 
# which one wins 
decide_label = function(labels) { 
  unlisted = unlist(labels)
  tbl = table(unlisted)
  label = as.numeric(names(which.max(tbl)))
  #still need to deal with ties somehow 
  return(label)
}

predict_knn = function(predict, train, k, distance = dist(rbind(predict, train))) {
 m = nrow(predict)
 p = nrow(train)
 
 combined = rbind(predict, train)
 distance = as.matrix(distance)
 predicted_labels = vector(mode = "list", length = m) # preallocating room for a vector of the predicted labels for each row
 correct_dist = distance[(1:m),(m + 1):(m + p)] #subsetted distance matrix 
 
 for (row in (1:m)) {
   row_ordered = sort(correct_dist[row,], decreasing = T) # order the distances in the row for that point
   
   labels = find_k_labels(k, row_ordered, correct_dist, combined, m) # gets a vector of k labels
   label = decide_label(labels) # finds the highest label
   predicted_labels[row] = label # add highest label to correct position in vector
 }
 return(predicted_labels) # returns vector of predicted labels for predict data based off of train data
}


# KNN function testing: 

train = train_matrix[1:200,]
predict = test_matrix[1:200,]

train_matrix = as.matrix(train_table)
test_matrix = as.matrix(test_table)

train = train_matrix
predict = test_matrix
ncol(predict)

predict_labels = predict_knn(predict, train, k = 6, metric = "euclidean")
predict_labels = unlist(predict_labels)
table(predict_labels)
debug(predict_knn)    


# Question 4 Cross Validation 

# for each fold, (m) calculate and compute an error estimate 
# calculate the distance matrix outside of predict_knn and then pass it into predict_knn

train = train_matrix[1:8,]
set.seed(141)

# this function shuffles the data and splits on m groups 
shuffle = function (train, m) { 
  train_df = as.data.frame(train) # convert to data frame
  train_rows = nrow(train_df)
  
  shuffled = train_df[sample(nrow(train_df)), ] # shuffle the data 
  groups = rep(c(1:m), (train_rows / m )) # create vector of group labels
  shuffled$Groups = groups # assign groups to data
  
  return(shuffled) # returns a data frame with original train data split into m groups 
}

# This function calculates error rate based on output from predict_knn & actual labels
calc_error_rate = function (predicted_labels, predict) { 
  length = nrow(predict)
  sum_incorrect = 0
  for (row in (1:length)) {
    if (predicted_labels[row] != predict[row,1]) {
      sum_incorrect = sum_incorrect + 1 
    }
  }
  error_rate = sum_incorrect / length
  return(error_rate)
}

cv_error_knn = function(train, m, k, metric) {
  train_shuffle = shuffle(train, m) # calls the function to shuffle & split data
  
  sum_error_rates = 0
  for (group in 1:m) {
    predict = as.matrix(train_shuffle[train_shuffle$Groups == group,])
    train = as.matrix(train_shuffle[-(train_shuffle$Groups == group),])

    distance = dist(rbind(predict, train), method = metric)
    predicted_labels = predict_knn(predict, train, k , distance )
    group_error_rate = calc_error_rate(predicted_labels, predict) #get error rate
    sum_error_rates = sum_error_rates + group_error_rate # add error rate to sum
  }
  cv_error_rate = sum_error_rates / m
}

# Testing my CVV function
train = train_matrix
predict = test_matrix
debug(cv_error_knn)
cv_error_test = cv_error_knn(train, m = 5, k = 10)
cv_error_test

predict_labels = predict_knn(predict, train, k = 2)

train_test = lapply(train_split[-1], as.matrix)
train_test = unsplit(train_split[-1], train_split[])
train_test = train_split[-1]
train_split = split_shuffle(train, m)
train_test$'2'
debug(shuffle)
shuffledd = shuffle(train, m = 10)
shuffledd
group = 1
typeof(as.matrix((shuffled[shuffled$Groups == group,])))
