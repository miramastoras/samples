## Mira Mastoras
## STA141A assignment 1

## Question 1 

college_scorecard = readRDS("college_scorecard.rds")

## Question 2

nrow(college_scorecard)
rownames(college_scorecard)
head(college_scorecard)

## Question 3
ncol(college_scorecard)
colnames(college_scorecard)

#Question 4 

table(college_scorecard$academic_year)

#Question 5 

collegesbystate = table(college_scorecard$state)
sort(collegesbystate)

str(college_scorecard)

##Question 6

install.packages("ggplot2")
library(ggplot2) 


public_2014_data = subset(college_scorecard, college_scorecard$ownership == "Public" & college_scorecard$academic_year == "2014") 
## from Piazza

ggplot(public_2014_data, aes(x = avg_net_price.public, y = earn_10_yrs_after_entry.median)) + 
  geom_point() + 
  labs(title = "Public Schools in 2014", x = "Average Net Price ($) ", y = "Median Student Earnings After 10 Years ($)") +
  theme(plot.title = element_text(hjust = 0.5)) ## from stack overflow 
  
##Question 7

private_fp_2014_data = subset(college_scorecard, college_scorecard$ownership == "Private for-profit" & college_scorecard$academic_year == "2014")

ggplot(private_fp_2014_data, aes(x = avg_net_price.private, y = earn_10_yrs_after_entry.median)) + 
 geom_point() + 
 labs(title = "Private For-Profit Schools in 2014", x = "Average Net Price ($) ", y = "Median Student Earnings After 10 Years ($)") +
  theme(plot.title = element_text(hjust = 0.5)) ## from stack overflow 

## Question 8
private_np_2014_data = subset(college_scorecard, college_scorecard$ownership == "Private nonprofit" & college_scorecard$academic_year == "2014")
ggplot(private_np_2014_data, aes(x = avg_net_price.private, y = earn_10_yrs_after_entry.median)) + 
  geom_point() + 
  labs(title = "Private Non- Profit Schools in 2014", x = "Average Net Price ($)", y = "Median Student Earnings After 10 Years ($)") +
  theme(plot.title = element_text(hjust = 0.5)) ## from stack overflow 

## Question 9 

value = c(table(college_scorecard$academic_year))

ggplot(college_scorecard, aes(fill = ownership, x = academic_year, color = academic_year )) + 
  geom_bar(position = position_dodge()) +
  labs(title = "Number of colleges recorded for each year", x = "Academic Year", y = "Number of Schools", color = "Academic Year", fill = "Ownership") +
  theme_classic() 
  

#Question 10

uc_davis = subset(college_scorecard, college_scorecard$id == "110644")
ggplot(uc_davis, aes(x = academic_year, y = admission_rate.overall, group = 1 )) + 
  geom_line() + 
  geom_point() +
  labs(title = "UC Davis Admission Rates", x = "Academic Year", y = "Admission Rate") +
  theme(plot.title = element_text(hjust = 0.5)) 

#Question 11

str(college_scorecard)

typeof(college_scorecard$ope6_id)
typeof(college_scorecard$name)

#Question 12

str(college_scorecard)
