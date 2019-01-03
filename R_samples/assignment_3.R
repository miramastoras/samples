# Mira Mastoras
# STA141A 
# Assignment 3

apartment_data = readRDS("~/sta141a/cl_apartments (1).rds")
library(ggplot2)
## Overview section
colnames(apartment_data)
nrow(apartment_data)

summary(apartment_data)
# time & date span of data
sorted = sort(apartment_data$date_posted)
head(sorted)
tail(sorted)

# locations 

#Are apartments in suburbs more family friendly? 

# 217 cities
city_count = table(apartment_data$city)
city_count = as.data.frame(city_count)

county_count = table(apartment_data$county)
county_count = data.frame(county_count)
nrow(county_count)
county_count

# read in external data set with population values for all cities in CA
city_pop_data = read.csv("~/sta141a/california_cities_by_population.csv", stringsAsFactors =  FALSE, strip.white = TRUE)

city_by_population = as.data.frame(city_pop_data)

#get list of cities in the data set
cities_in_dataset = city_count$Var1

#subset population data set by only cities in the data
less_cities = subset(city_by_population, City %in% cities_in_dataset)
less_cities

index = c(1:212)
less_cities$index = index

less_cities$city_or_suburb[1:49] = "city"
less_cities$city_or_suburb[50:212] = "suburb"
less_cities = as.data.frame(less_cities)
city_designation = as.data.frame(city_designation)
names(city_designation) = c("city", "city_or_suburb")
city_designation = subset(less_cities, select = c(City, city_or_suburb))

table(less_cities$city_or_suburb)

#apartment data with city/ suburb designation
ap_data_2 = merge(apartment_data, city_designation, by = "city")
colnames(ap_data_2)
table(ap_data_2$city_or_suburb)


nrow(ap_data_2)
#pets allowed: 
pets_qs = table(ap_data_2$pets, ap_data_2$city_or_suburb.y)
pets_qs = as.data.frame(pets_qs)
names(pets_qs) = c("pets", "city_or_suburb", "count")


#splitting data to get proportion for bar graph
city_pets_split = split(pets_qs, pets_qs$city_or_suburb)

sum_suburb = sum(city_pets_split$suburb$count)
city_pets_split$suburb$prop = city_pets_split$suburb$count / sum_suburb

sum_city = sum(city_pets_split$city$count)
city_pets_split$city$prop = city_pets_split$city$count / sum_city

# bring data back together, from stack overflow
city_pets_split = do.call(rbind, city_pets_split)
city_pets_split = as.data.frame(city_pets_split)

ggplot(city_pets_split, aes(x = city_or_suburb, fill = pets, y = prop, label = sprintf("%0.2f", round(prop, digits = 2 )))) + 
  geom_bar(stat = "identity", position = "dodge") +
  geom_text(position=position_dodge(width=0.9), vjust=-0.25, hjust = 0.5, size = 4.5) +
  labs(x = "Location", y = "Proportion", title = "Apartment Pet-friendliness by Neighborhood Type", fill = "Pets Allowed") +
  scale_fill_viridis_d() +
  theme(axis.text=element_text(size=12), axis.title = element_text(size = 12))

# num of bedrooms
beds_by_desig = table(ap_data_2$city_or_suburb.y, ap_data_2$bedrooms)
beds_by_desig = as.data.frame(beds_by_desig)
colnames(beds_by_desig) = c("city_or_suburb", "bedroom_num", "Freq")

#make it a proportion 

beds_split = split(beds_by_desig, beds_by_desig$city_or_suburb)

sum_beds_suburb = sum(beds_split$suburb$Freq)
beds_split$suburb$prop = beds_split$suburb$Freq / sum_beds_suburb

sum_beds_city = sum(beds_split$city$Freq)
beds_split$city$prop = beds_split$city$Freq / sum_beds_city

# bring data back together, from stack overflow
beds_split = do.call(rbind, beds_split)
beds_split = as.data.frame(beds_split)


ggplot(beds_split, aes(x = city_or_suburb, y = prop, fill = bedroom_num)) + 
  geom_bar(stat = "identity", position = "dodge") +
  labs(title = "Number of Bedrooms by Neighborhood Type", x = "Neighborhood Type", y = "Proportion", fill = "Bedroom Number" ) +
  scale_fill_viridis_d() +
  theme(axis.text=element_text(size=12), axis.title = element_text(size = 13))

# attempt to do average bed number
mean_beds = tapply(beds_by_desig$Freq, beds_by_desig$Var1, mean)
mean_beds = as.data.frame(mean_beds)
mean_beds$city_or_suburb = c("city", "suburb")
mean_beds
ggplot(mean_beds, aes(x = city_or_suburb, y = mean_beds)) + geom_bar(stat="identity")

# for loop attempt before i learned about merge 
city_names = subset(less_cities, less_cities$city_or_suburb == "city")
suburb_names = subset(less_cities, less_cities$city_or_suburb == "suburb")
suburb_names

nrow(apartment_data)
apartment_data$city_or_suburb = "city"
apartment_data$city_or_suburb
for (x in 1:2198) {
  if (apartment_data$city[x] %in% suburb_names) {
    apartment_data$city_or_suburb[x] = "suburb"
  }
}

apartment_data$city_or_suburb
apartment_data$city

table(apartment_data$city_or_suburb)


# effect of beds / baths on rent pricing 

apartment_data$price

table(apartment_data$bedrooms)
ggplot(apartment_data, aes(x = price)) + geom_histogram() + xlim(0,10000)

apartment_data$price


#get vector with average net price for each number of bedrooms 
# aggregate? 

avg_price_beds = aggregate(price ~ bedrooms, apartment_data, mean)
avg_price_baths = aggregate(price ~ bathrooms, apartment_data, mean)

avg_price_beds
avg_price_beds$type = "bedroom"
avg_price_baths$type = "bathroom"

colnames(avg_price_beds)[1] = "rooms"
colnames(avg_price_baths)[1] = "rooms"

avg_price = rbind(avg_price_beds, avg_price_baths)

avg_price_beds
ggplot(avg_price, aes(x = rooms, y= price, color = type)) +
  geom_point() + 
  geom_line(stat = "identity") +
  labs(title = "Effect of Bedroom and Bathroom Number on Rent Pricing", x = "Number of Rooms", y = "Average Price", color = "Type of Room") 
linear_model = lm(rooms ~ price, avg_price_baths )


## Geographical similarity of apartments
## san francisco, oakland, san jose 
three_cities = subset(apartment_data, apartment_data$city == "San Francisco" | apartment_data$city == "San Jose" | apartment_data$city == "Oakland")
table(three_cities$city== "San Francisco" | three_cities$city== "San Jose" | three_cities$city== "Oakland")
colnames(three_cities)

## average rent btw the three
summary(three_cities$price)
means_three_cities = aggregate(price ~ city, three_cities, mean)
means_three_cities = data.frame(means_three_cities)
means_three_cities

ggplot(three_cities, aes(x = city, y = price)) +
  geom_boxplot() +
  labs(title = "Average Apartment Rent by City", y = "Average Price", x = "City")

ggplot(means_three_cities, aes(x = city, y = price, fill = city)) +
  geom_bar(stat = "identity") +
  labs(title = "Average Apartment Rent by City", y = "Average Price", x = "City") 
  theme(legend.position="none") + scale_fill_viridis_d()
## bedroom number

city_by_bedroom = table(three_cities$city, three_cities$bedrooms)
as.data.frame(city_by_bedroom)
subset(city_by_bedroom, Var1 == "San Francisco")

bed_sum = aggregate(city ~ bedrooms, three_cities, count)
as.data.frame(bed_sum)

city_by_bedroom
three_cities = three_cities[!is.na(three_cities$bedrooms),]

ggplot(three_cities, aes(x = city, y = stat(prop), group = as.character(bedrooms), fill = as.character(bedrooms))) + 
  geom_bar(position = "dodge") + 
  labs(title = "Bedroom Number by City", x = "City", y = "Proportion", fill = "Bedroom Number") 



## sq footage
sqft = aggregate(sqft ~ city, three_cities, mean)
sqft
#bar plot
ggplot(means_three_cities, aes(x = city, y = sqft, fill= city)) + geom_bar(stat = "identity") +
  geom_abline(slope = 0 , intercept = 885.3302, linetype = "dashed") + 
  labs(title = "Average Apartment Square Footage by City", x = "City", y = "Average Square Footage (sqft)") + 
  scale_fill_viridis_d() + 
  theme(legend.position="none") + 
  annotate(y = 910, x = 0.8, geom = "text", label = "(avg sqft in CA)")
#boxplot
ggplot(three_cities, aes(x = city, y = sqft)) + geom_boxplot() +
  #geom_abline(slope = 0 , intercept = 885.3302, linetype = "dashed") + 
  labs(title = "Average Apartment Square Footage by City", x = "City", y = "Average Square Footage (sqft)") + 
  scale_fill_viridis_d() + 
  theme(legend.position="none") + 
  #annotate(y = 910, x = 0.8, geom = "text", label = "(avg sqft in CA)") + 
  ylim(0, 3600)

## further questions

#rent in the bay vs elsewhere

colnames(apartment_data)
table(apartment_data$craigslist, apartment_data$price)

mean_price_by_clist = aggregate(price ~ craigslist, apartment_data, mean)
as.data.frame(mean_price_by_clist)
aggregate(price ~ craigslist, apartment_data, summary)

summary(apartment_data$price[apartment_data$craigslist == "sfbay_pen"], na.rm = TRUE)

# took out 2 outliers that were clearly a mistake - from SF BAY pen & sac
which(apartment_data$price == "34083742")
which(apartment_data$price == "9951095")
apartment_data = apartment_data[-15961,]
apartment_data = apartment_data[-4531,]

levels(mean_price_by_clist$craigslist) = c("Los Angeles", "Sacramento","San Diego", "SF - East Bay", "SF - North Bay", "SF - Peninsula", "SF - South Bay", "San Francisco")
size_fix =  order(mean_price_by_clist$price)
size_fix = factor(mean_price_by_clist$price, order(mean_price_by_clist$price))
levels(size_fix)
size_fix = factor(mean_price_by_clist$craigslist, c("2","3","1","4","5","7","6","8"))
size_fix
ggplot(mean_price_by_clist, aes(x = craigslist, y = price, fill = craigslist)) + 
  geom_bar(stat = "identity") + scale_fill_viridis_d() + 
  theme(axis.text.x = element_blank(), axis.ticks.x = element_blank()) +
  labs(x = "Craigslist Area", y = "Average Rent Price", title = "Average Rent Price by Location", fill = "Craigslist Area")
   

# do pets drive up rent price?

ap_data = subset(apartment_data, !(is.na(apartment_data$pets)))
colnames(apartment_data)
ggplot(apt_data, aes(x = pets, y = price, fill = pets)) + 
  geom_bar(stat = "identity", position = "dodge") + 
  labs(title= "Pets Allowed vs Rent Price", x = "Pets Allowed", y = "Average Rent Price", fill = "Pets") + 
  scale_fill_viridis_d()
  
apt_data$parking

# does parking availability differ between "city" and "suburbs" ? 
parking_data = table(ap_data_2$city_or_suburb, ap_data_2$parking)
parking_data = as.data.frame(parking_data)
parking_split = split(parking_data, parking_data$Var1)
parking_split

sum_suburb = sum(parking_split$suburb$Freq)
sum_suburb
parking_split$suburb$prop = parking_split$suburb$Freq / sum_suburb

sum_city = sum(parking_split$city$Freq)
parking_split$city$prop = parking_split$city$Freq / sum_city

parking_split = do.call(rbind, parking_split)
parking_split = as.data.frame(parking_split)
parking_split

ggplot(parking_split, aes(fill = Var2, x = Var1, y = prop)) + 
  geom_bar(position = "dodge", stat = "identity") +
  labs(title = "Apartment Parking Availability", x = "Location", y = "Proportion", fill = "Parking Type" ) + 
  scale_fill_viridis_d()


## Does laundry type correlate with rent price? 
apt_data = subset(apartment_data, !(is.na(apartment_data$laundry)))

laundry = as.data.frame(aggregate(price~laundry, apt_data, mean))
ggplot(laundry, aes(x = laundry, y = price, fill = laundry)) + 
  geom_bar(stat = "identity") +
  labs(title = "Laundry Fixtures and Average Rent Price", x = "Laundry Type", y = "Average Rent Price", fill = "Laundry Type") + 
  scale_fill_viridis_d()

table(apt_data$laundry)


#price & square footage

price_sqft = lm(sqft ~ price, apt_data)

ggplot(apt_data, aes(y = sqft, x = price)) + 
  geom_point(alpha = 0.5) + ylim(0, 4000) +
  labs(title = "Square Footage and Rent Price", x = " Rent Price", y = "Square Footage") 

## Limitations 

# Missing values
shadow = is.na(apartment_data)
shadow = as.data.frame(shadow)
contain_na = sapply(shadow, any,na.rm = TRUE)

names(apartment_data[!contain_na])
apartment_data[shadow]

col_sum_na = colSums(shadow)
sort(col_sum_na)
