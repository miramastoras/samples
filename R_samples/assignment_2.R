## Mira Mastoras
## STA141A
## Assignment 2

library(ggplot2)
##Question 1

college_scorecard = readRDS("college_scorecard.rds")
typeof(college_scorecard)
colnames(college_scorecard)

# shadow is a T/F data frame with NAS replaced with true, False is not NAs
shadow = is.na(college_scorecard)

col_sum_na = colSums(shadow)
shadow = as.data.frame(shadow)
shadow
colnames(shadow)

#contain_na is a T/F vector with T if the column contains any na, false if it doesnt
contain_na = sapply(shadow, any,na.rm = TRUE)
typeof(contain_na)
contain_na = unname(contain_na)
nrow(contain_na)

# subset scorecard data - get columns containing NAs
names(college_scorecard[contain_na])

# gets columns NOT containing NAS
names(college_scorecard[contain_na == FALSE])

## get columns where shadow is true
college_scorecard[shadow]

# which have most / least missing values?
col_sum_na
sort(col_sum_na)

colnames(college_scorecard)

# missing values by academic year 

college_scorecard$shadow_data = shadow
data = subset(college_scorecard, select = c(women_only, new_shadow_data, academic_year))
data
nrow(college_scorecard$new_shadow_data)
ggplot(data, aes(x = academic_year, y = new_shadow_data)) + geom_bar(stat = "identity")

year_shadow = subset(shadow, select = c(academic_year))

aggregate(academic_year ~ new_shadow_data, college_scorecard, sum)

ncol(shadow_data)
ncol(college_scorecard)

## Question 2

colnames(college_scorecard)

# population of every school
ggplot(college_scorecard, aes(x = size, y = grad_students)) +
  geom_point() +
  labs(title = "Distribution of Undergraduate Students vs. Graduate students", x = "Undergraduate", y = "Graduate")


#Just the large schools 
large_schools = subset(college_scorecard, college_scorecard$size > 50000)
ggplot(large_schools, aes(x = ownership)) + 
  geom_bar() +
  labs(title = "Schools larger than 50,000")

large_schools$ownership

# Small schools - distribution of Undergraduate vs. Graduate students
small_schools = subset(college_scorecard, college_scorecard$size < 50000)
ggplot(small_schools, aes(x = size, y = grad_students)) + 
  geom_point() +
  geom_abline(slope = 1, intercept = 0) +
  labs(title = "Distribution of Undergraduate vs. Graduate students", x = "Undergraduate", y = "Graduate")

# For schools with much higher population of grad students
lots_of_grad = subset(college_scorecard, college_scorecard$grad_students > 10000 & college_scorecard$size < 10000)
ggplot(lots_of_grad, aes(x = ownership)) + 
  geom_bar() 
  ##labs(title = "Distribution of Undergraduate Students vs. Graduate students", x = "Undergraduate", y = "Graduate")
  
lots_of_grad$ownership

## Question 3

names(college_scorecard)
starts_with_program = startsWith(names(college_scorecard), "program_percentage")
typeof(starts_with_program)
starts_with_program

# average popularity of all programs
str(starts_with_program)
program_means = sapply(college_scorecard[starts_with_program], mean, na.rm = TRUE)

program_means
sort(program_means, decreasing = TRUE)

program_means = as.data.frame(program_means)
ggplot(program_means, aes(x = program_means )) + geom_density() 

# variance of programs 
program_var = sapply(college_scorecard[starts_with_program], var, na.rm = TRUE)
sort(program_var, decreasing = TRUE)
program_var = as.data.frame(program_var)
ggplot(program_var, aes(x = program_var )) + geom_density() + labs(title = "Variance of programs", x = "Program Variance", y = "Density")

# boxplot for health and personal culinary
health = ggplot(college_scorecard, aes(x = "", y = college_scorecard$program_percentage.health)) + 
  geom_boxplot() +
  labs(x = "Culinary Programs", y ="Percentage", title = "Programs with the highest variance from their mean")
cul = ggplot(college_scorecard, aes(x = "", y = college_scorecard$program_percentage.personal_culinary)) + 
  geom_boxplot()+
  labs( x = "Health Programs", y ="Percentage")
grid.arrange(health, cul)

#density plot for health and personal culinary
ggplot(college_scorecard, aes(x = college_scorecard$program_percentage.health )) + geom_density() 
ggplot(college_scorecard, aes(x = college_scorecard$program_percentage.personal_culinary )) + geom_density() 
# top five most popular

ggplot(college_scorecard, aes(x = college_scorecard$program_percentage.health)) + geom_density()

## Question 4 tuition across different states

#how tuition varies across states


collegesbystate = table(college_scorecard$state)
collegesbystate

# the following code is from piazza
# comparing tuition for each year

avg_in = aggregate(tuition.in_state ~ academic_year, college_scorecard, mean)
names(avg_in)[2] = "avg_tuition"
avg_in$in_or_out_state = "In-state"

avg_out = aggregate(tuition.out_of_state ~ academic_year, college_scorecard, mean)
names(avg_out)[2] = "avg_tuition"
avg_out$in_or_out_state = "Out of state"

tuition = rbind(avg_in, avg_out)

ggplot(tuition, aes(x = academic_year, fill = )) + geom_bar()

# comparing tuition by state

collegesbystate = table(college_scorecard$state)
collegesbystate = as.data.frame(collegesbystate)
names(collegesbystate)[2] = "num_colleges"
collegesbystate

# in state tuition
avg_in = aggregate(tuition.in_state ~ state +  , college_scorecard, mean)
names(avg_in)[2] = "avg_tuition"
avg_in$in_or_out_state = "In-state"

avg_in$num_colleges = collegesbystate[[2]]

in_graph = ggplot(avg_in, aes(y = num_colleges, x = avg_tuition)) +
  geom_point() + 
  labs(title = "In state tuition, by state", y = "Number of colleges", x = "Average Tuition")

# out of state tuition
avg_out = aggregate(tuition.out_of_state ~ state, college_scorecard, mean)
names(avg_out)[2] = "avg_tuition"
avg_out$in_or_out_state = "Out of state"

?geom_text
avg_out$num_colleges = collegesbystate[[2]]

out_graph = ggplot(avg_out, aes(y = num_colleges, x = avg_tuition)) +
  geom_point() + 
  labs(title = "Out of state tuition, by state", y = "Number of colleges", x = "Average Tuition")

# graph in state tuition next to out of state tuition
library(gridExtra)
grid.arrange(in_graph, out_graph, ncol = 2)

tuition_by_state = rbind(avg_in, avg_out)

## Question 5

colnames(college_scorecard)

# subset data to get minority column vectors, sum & append back to college_scorecard
minority_data = subset(college_scorecard, select = c(demographics.race_ethnicity.black, demographics.race_ethnicity.hispanic,demographics.race_ethnicity.asian,demographics.race_ethnicity.aian,demographics.race_ethnicity.nhpi,demographics.race_ethnicity.two_or_more))
minority_sum = rowSums(minority_data)

college_scorecard$minority_sum = minority_sum

#dot plot 
ggplot(college_scorecard, aes(x = minority_sum, y = demographics.race_ethnicity.white)) +
  geom_point() +
  labs(title = "Diversity of US Colleges", x = "Percentage of population Non-white", y = "Percentage of population, white")

# find colleges with highest and lowest diversity

highly_diverse = subset(college_scorecard, minority_sum > 0.847 & minority_sum < 0.853 & demographics.race_ethnicity.white > 0.137 & demographics.race_ethnicity.white < 0.143)
highly_diverse$name

str(college_scorecard$religious_affiliation)

low_diverse = subset(college_scorecard, minority_sum == 0 & demographics.race_ethnicity.white == 1.0)
isreligious = is.na(low_diverse$religious_affiliation)
isreligious = as.data.frame(isreligious)

ggplot(isreligious, aes(x = isreligious )) + geom_bar() + labs(title = "Low Diversity US Colleges", x = "Is the school religiously affiliated?", y = "Count")

colnames(college_scorecard)

## Question 6

# Is there a correlation between SAT scores and school ownership? 

ggplot(college_scorecard, aes (x = ownership, y = sat_scores.average.overall, fill = ownership)) +
  geom_bar(position = position_dodge(), stat = "identity") +
  labs(title = "SAT Scores by Ownership", x = "Ownership", y = "SAT scores") +
  theme_classic()

# instructional_expenditure_per_fte vs admission rates

ggplot(college_scorecard, aes(x = admission_rate.overall, y = instructional_expenditure_per_fte)) +
  geom_point() + scale_y_continuous(limits = c(0,320000)) +
  labs(title = "US Colleges", y = "Instructional Expenditure per Full time Student", x = "Overall Admission Rate")
  

##Question 8

# size & instructional expenditure? 

ggplot(college_scorecard, aes(x = size, y = instructional_expenditure_per_fte)) +
  geom_point() +
  labs(title = "US Colleges", y = "Instructional Expenditure per Full time Student", x = "School size") +
  scale_y_continuous(limits = c(0,400000)) + scale_x_continuous(limits = c(0, 50000))

## price and expenditure

ggplot(college_scorecard, aes(x = avg_net_price.public, y = instructional_expenditure_per_fte)) +
  geom_point() +
  labs(title = "Public US Colleges", y = "Instructional Expenditure per Full time Student", x = "Average Net Price") +
  scale_y_continuous(limits = c(0,130000)) + scale_x_continuous(limits = c(0, 35000))

ggplot(college_scorecard, aes(x = avg_net_price.private, y = instructional_expenditure_per_fte)) +
  geom_point() +
  labs(title = "Private US Colleges", y = "Instructional Expenditure per Full time Student", x = "Average Net Price") +
  scale_y_continuous(limits = c(0,150000)) + scale_x_continuous(limits = c(0, 50000))



