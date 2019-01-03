# Mira Mastoras
# STA141A HW 5

library(ggplot2)

# Question 1
library(stringr)
read_posts = function(file) { # parameter "file" is full file path 
  text = readLines(file)
  text = str_c(text, collapse = '\n') # return value is a string with the text from the file
} 

#test for read_posts 
desc = read_posts("/Users/miramastoras/sta141a/messy/losangeles/_ant_apa_d_1-bd-1-bd-water-paid-utility_6718641721.txt")
desc

# Question 2

read_all_posts = function(directory) { # parameter is full path to craigslist location directory ie "losangeles"
  files = list.files(directory, full.names = T )
  posts = sapply(files, read_posts)
  newposts = data.frame(text = posts, region = basename(directory))
}

# gets list of files from messy directory
area_list = list.files(messy_cl, full.names = TRUE) 
area_list
#applies the read_all_posts function to each directory 
posts = lapply(area_list, read_all_posts)
head(posts)
#combines list of data frames in "posts" into a data frame of data frames
posts_df = do.call(rbind, posts)
str(posts_df)

# remove duplicate rows from DF
posts_df[!duplicated(posts_df$text), ]

# Question 4 -- Rental Prices

test = posts_df$text[[1]]
message(test)

# extract price from title and store it back in posts_df

result = str_split_fixed(posts_df$text, "\n", 2)
posts_df$title = result[, 1]
posts_df$text = result[, 2]

str(posts_df)

#gets title price from each post
title_price = lapply(posts_df$title, str_match, "\\$[0-9]+")
head(title_price)
new_title_price = unlist(title_price, recursive=FALSE)

new_title_price = lapply(new_title_price, str_remove_all, "[\\$]")
new_title_price = unlist(new_title_price)
new_title_price
new_title_price = as.numeric(new_title_price)

#checking the new title price Df matches the posts 
head(title_price_df)
nrow(posts_df)
nrow(title_price_df)


# extract price from the attribute: 

attribute_price = lapply(posts_df$text, str_extract, regex("Price:\\s\\$[0-9,]+", ignore_case = TRUE))
attribute_price_new = lapply(attribute_price, str_split, regex("Price: " , ignore_case = TRUE))
# removing nested lists 
attribute_1 = unlist(attribute_price_new, recursive=FALSE )
attribute_2 = unlist(attribute_1, recursive=FALSE )

attribute_price = attribute_2[!attribute_2 == ""]
attribute_price = lapply(attribute_price, str_remove_all, "[\\$]")
attribute_price = unlist(attribute_price)

attribute_price = as.numeric(attribute_price)

shadow = is.na(attribute_price)
table(shadow)

#adding prices to DF
posts_df$attribute_price = attribute_price
posts_df$title_price = new_title_price

posts_df$price_diff = posts_df$title_price - posts_df$attribute_price

#getting rid of the NA's: 

shadow = !(is.na(posts_df$price_diff))
shadow
posts_na_rm = posts_df[shadow,]
nrow(posts_na_rm)

#subset based on those with price difference btw title and attribute

price_is_diff = posts_na_rm[!posts_na_rm$price_diff == "0", ]
price_is_diff[ select =c(posts_na_rm$title_price, posts_na_rm$attribute_price)]

#subset data based on just those two columns
subset(price_is_diff, select = c(title_price, attribute_price))

#Do all of the titles have prices? 

shadow = is.na(new_title_price)
table(shadow) # 176 do not have prices in title - they are NA

shadow_na_title = (is.na(posts_df$title_price)) # find posts with na in their title 
posts_just_na = posts_df[shadow_na_title,] # subset by posts with na in title
nrow(posts_just_na)
colnames(posts_just_na)

#none of these have NA in their text 
table(is.na(posts_just_na$text))
table(is.na(posts_just_na$attribute_price))
posts_just_na$title[1]


# Question 5-- deposit price

contains_deposit_TF = str_detect(posts_df$text, regex("deposit", ignore_case = T)) #how many have deposit in them? 18303

#subset by posts with the word deposit
contains_dep_df = posts_df[contains_deposit_TF,] 

#subset by all posts without pet deposits, reg ex code from Piazza 
no_pets = str_detect(contains_dep_df$text, regex("(pets?|dogs?|cats?|animals?)(friendly|allowed|additional|.*)(deposit|fee)",ignore_case = TRUE))

only_correct_dep = contains_dep_df[!no_pets,] 
nrow(only_correct_dep) #8172 posts have apartment deposit info 

#now extracting the deposit price 

deposit_price = str_match(only_correct_dep$text, regex("deposit\\s\\$([0-9,]+)", ignore_case = TRUE ))
num_dep_price = deposit_price[,2]
deposit_price_clean = str_remove(deposit_price[,2], ",")
table(is.na(deposit_price_clean))
deposit_price_clean = as.numeric(deposit_price_clean)

deposit_price

only_correct_dep$deposit_price = deposit_price_clean #extracted 608 prices 

# graph looking at relationship btw title and deposit
ggplot(only_correct_dep, aes( y = title_price, x = deposit_price)) +
  geom_point() + ylim(0,7000) +
  xlim(0, 10000) +
  
  labs(title = "Relationship between Title Price and Deposit Price", x = "Title Price", y = "Deposit Price")

# looking at attribute price & deposit , looks the same 

ggplot(only_correct_dep, aes( y = attribute_price, x = deposit_price, alpha = 0.3)) +
  geom_point() + ylim(0,7000) +
  xlim(0, 10000) +
  labs(title = "Relationship between Attribute Price and Deposit Price", x = "Title Price", y = "Deposit Price")

# random code 
table(is.na(deposit_price))
only_correct_dep$deposit_price = deposit_price
table(is.na(only_correct_dep$deposit_price))
shadow_1 = ! (is.na(deposit_price))
newnew = posts_df[shadow_1,]
newnew$text[1]
posts_df[shadow_1,]


# Question 6: 

# extracting pets allowed feature 

parse_pets = function(text) {
  status = NA
  pets_sent = str_extract(text, regex("((\\w+ ){0,5})pets? ((\\w+ ){0,5})|((\\w+ ){0,5})dogs? ((\\w+ ){0,5})|((\\w+ ){0,5}) cats?((\\w+ ){0,5})", ignore_case = T)) # regex from piazza
  if (!is.na(pets_sent)) {
    both_yes = str_detect(pets_sent,  regex("(pets?\\s?|animals?\\s?|dogs? and cats?\\s?|cats? and dogs?)\\s?( friendly | allowed | yes | welcome .*)", ignore_case = T))
    cat_yes = str_detect(pets_sent, regex(" cats?\\s(allowed|okay|deposit)|\\s?no dogs?|\\s?dogs not allowed\\s?", ignore_case = T))
    dog_yes = str_detect(pets_sent, regex("dogs?\\s(allowed|okay|deposit)|\\s?no cats?|\\s?cats not allowed\\s?", ignore_case = T))
    no_pets = str_detect(pets_sent, regex("\\s?no pets?|\\s?no pets? allowed\\s?|\\s?pets not allowed\\s|\\s?pets? prohibited\\s", ignore_case = T))
    if (both_yes == T) {
      status = "both"
      return(status)}
    if (cat_yes == T){
      status = "cats"
      return(status)}
    if (dog_yes == T) {
      status = "dogs"
      return(status)} 
    if (no_pets == T) {
      status = "none"
      return(status)}
    return(status)
  }
  return(status)
}

#testing function as i build it 
old_regex = "^.*\\b( pets?|animals?|dogs?|cats?.)\\b.*$"

test_str = "-Dogs and Cats Welcome (select apartments). "
test_patt = regex("(pets?\\s|animals?\\s|dogs? and cats?\\s|cats? and dogs?)\\s( friendly | allowed | yes | welcome .*)", ignore_case = T)

str_extract(tester, regex("(pets?\\s?|animals?\\s?|dogs? and cats?\\s?|cats? and dogs?)\\s?( friendly | allowed | yes | welcome .*)", ignore_case = T))

tester = posts_df$text[800]
str_detect(test_str, test_patt)
posts_df$text[8000]
parse_pets(tester)
debug(parse_pets)

# use lapply to build a list matching the DF of categories 

pet_policy = lapply(posts_df$text, parse_pets)
pet_policy_2 = unlist(pet_policy)
table(pet_policy_2) # it worked! thank god! 

# here is where i append the categories for pet policy back onto the original data frame
posts_df$pet_policy = pet_policy_2

posts_df$pet_policy
# extracting pet deposit 

find_pet_deposit = function (text) {
  deposit_num = NA
  pet_dep_after = str_match(text, regex("(\\s?pets?\\s?|\\s?cats?\\s?|\\s?dogs?\\s?)[A-Za-z :]+(deposit)[A-Za-z :]+[$]([0-9]+)", ignore_case = T))
  pet_dep_before = str_match(text, regex("[$]([0-9]+)[A-Za-z :]+(\\s?pets?\\s?|\\s?cats?\\s?|\\s?dogs?\\s?)[A-Za-z :]+(deposit)", ignore_case = T))
  if (!is.na(pet_dep_before[1])){
    deposit_num = as.numeric(pet_dep_before[2])
    return(deposit_num)
  }
  if (!is.na(pet_dep_after[1])){
    deposit_num = as.numeric(pet_dep_after[4])
    return(deposit_num)
  }
  return(deposit_num)
}

# Below are ways i was testing this function
find_pet_deposit(posts_df$text[224])
posts_df$text[224]
debug(find_pet_deposit)
str_detect(posts_df$text, "pet deposit")



str_901 = "$500 per pet deposit"

str_match(str_901, regex("[$]([0-9]+)[A-Za-z :]+(\\s?pets?\\s?|\\s?cats?\\s?|\\s?dogs?\\s?)[A-Za-z :]+(deposit)", ignore_case = T))

str_match_all(str_ex, regex("\\s?pets?\\s?| cats?\\s?| dogs?\\s?(\\$([0-9,]+))?\\s?deposit//s?(:|\\s)?\\$([0-9,]+)", ignore_case = T))
str_match("cat deposit $500", regex("(pets?\\s?| cats?\\s?| dogs?\\s?)(deposit)[A-Za-z :]+[$]([0-9]+)", ignore_case = T))

pet_dep = str_match("deposit pet $500 pet deposit", regex("[$]([0-9]+)( pets?\\s?| cats?\\s?| dogs?\\s?)(deposit)", ignore_case = T))

as.numeric(pet_dep[2])
str_extract(posts_df$text[992], str_ex)

pet_dep_after = str_match("pet $500", regex("(\\bpets?\\s?|\\bcats?\\s?|\\bdogs?\\s?)(deposit)[A-Za-z :]+[$]([0-9]+)", ignore_case = T))
pet_dep_after
posts_df$text[992]
str_ex = "Dogs and Cats are welcome with a $500 pet deposit per pet and a monthly pet rent of $50. "


# lapply over data set as before
pet_deposit = lapply(posts_df$text, find_pet_deposit)
pet_deposit_2 = unlist(pet_deposit)
posts_df$pet_deposit = pet_deposit_2
table(pet_deposit_2)

#how many pet deposits did i isolate? 2108 numbers 
how_many_did_i_get = posts_df[!is.na(pet_deposit_2),]
nrow(how_many_did_i_get)


#graphing pet deposit information 

# first: between the dogs, cats, none and both, which are more likely to have a pet deposit? 

posts_df$detect_deposit = is.na(posts_df$pet_deposit)
detect_dep_df = as.data.frame(table(posts_df$detect_deposit, posts_df$pet_policy))

detect_dep_df_split = split(detect_dep_df, detect_dep_df$Var2)

#getting sums for all categories, prob could have used lapply here?
detect_dep_df_split$both$sum = sum(detect_dep_df_split$both$Freq)
detect_dep_df_split$dogs$sum = sum(detect_dep_df_split$dogs$Freq)
detect_dep_df_split$cats$sum = sum(detect_dep_df_split$cats$Freq)
detect_dep_df_split$none$sum = sum(detect_dep_df_split$none$Freq)

#getting props for all categories
detect_dep_df_split$both$new = detect_dep_df_split$both$Freq / detect_dep_df_split$both$sum
detect_dep_df_split$dogs$new = detect_dep_df_split$dogs$Freq / detect_dep_df_split$dogs$sum
detect_dep_df_split$cats$new = detect_dep_df_split$cats$Freq / detect_dep_df_split$cats$sum
detect_dep_df_split$none$new = detect_dep_df_split$none$Freq / detect_dep_df_split$none$sum
detect_dep_df_split


detect_dep = as.data.frame(do.call(rbind, detect_dep_df_split))
detect_dep
ggplot(detect_dep, aes(x = Var2, y =new, fill = factor(Var1, labels = c("Pet Deposit Provided", "No Pet Deposit Info")))) +
  geom_bar(stat = "identity", position = position_dodge()) +
  labs(title = "Apartment Posts with a Pet Deposit by Pet Policy", x = "Pet Policy", y = "Percentage of Posts with Pet Deposit Information", fill = "Pet Deposit?")+
  scale_fill_viridis_d() +
  geom_text(aes(label=sprintf("%0.2f", round(new, digits = 2))), position=position_dodge(width=0.9), vjust=-0.25)

# now, how to the actual deposit prices differ between the categories

price_by_cat = aggregate(posts_df$pet_deposit, by=list(Category=posts_df$pet_policy), FUN=sum, na.rm = T)
price_by_cat = as.data.frame(price_by_cat)
price_by_cat$total = (table(posts_df$pet_policy))
price_by_cat = as.data.frame(price_by_cat)
price_by_cat
price_by_cat$avg_dep_price = price_by_cat$x / price_by_cat$total
price_by_cat

ggplot(price_by_cat, aes(x = Category, y = avg_dep_price, fill = Category)) +
  geom_bar(stat = "identity") +
  labs(title = "Pet Deposit Prices By Pet Policy", x = "Pet Policy", y = "Average Pet Deposit Price") +
  scale_fill_viridis_d() +
  geom_text(aes(label=sprintf("%0.2f", round(avg_dep_price, digits = 2))), position=position_dodge(width=0.9), vjust=-0.25)

ggplot(posts_df[!is.na(posts_df$pet_policy),], aes(x = pet_policy, y = pet_deposit )) + 
  geom_boxplot() + ylim(0,800) + 
  labs(title = "Pet Deposit Prices By Pet Policy", x = "Pet Policy", y = "Pet Deposit Price") 

table(posts_df$pet_policy)
  
new = posts_df[is.na(posts_df$pet_policy),]
table(new$pet_deposit)

# unusual pets

lol = str_detect(posts_df$text, regex("rabbit", ignore_case = TRUE))
rabbits = posts_df[lol,]
rabbits$text


#Question 7 

# function to extract air conditioning 

has_ac = function(text) {
  ac_status = NA
  ac_yes = str_extract(text, regex("\\s?air conditioning\\s?|\\s?central air\\s?|\\s?AC\\s?", ignore_case = T))
  ac_no = str_extract(text, regex("\\s?no AC\\s?|\\s?no central air\\s?|\\s?no air conditioning\\s?"))
  if (!is.na(ac_yes)) {
    ac_status = "AC"
  }
  if (!is.na(ac_no)){
    ac_status = "No AC"
  }
  return(ac_status)
}

# testing the function
table(str_detect(posts_df$text, "\\s?no AC\\s?|\\s?no central air\\s?|\\s?no air conditioning\\s?"))

ac_yes = str_detect(posts_df$text, ac_pattern)

str_extract(posts_df$text[865], regex("\\s?air conditioning\\s?|\\s?central air\\s?|\\s?AC\\s?"))
posts_df$text[745]
has_ac(posts_df$text[745])

#lapply over the data set
AC_status = lapply(posts_df$text, has_ac)

AC_status_2 = unlist(AC_status)
posts_df$AC_status = AC_status_2
table(AC_status_2)

# Now extracting the heating variable

has_heat = function(text) {
  heat_status = NA
  heat_yes = str_extract(text, regex("\\s?heating\\s?|\\s?heater\\s?|\\s?central heat\\s?|\\s?heat\\s?(^heated pool)", ignore_case = T))
  fire_yes = str_extract(text, regex("\\s?fireplace\\s?|\\s?wood burning stove\\s?", ignore_case = T))
  neither = str_extract(text, regex("\\s?no fireplace\\s?"))
  if (!is.na(heat_yes)) {
    heat_status = "heater"
  }
  if (!is.na(fire_yes)) {
    heat_status = "fireplace"
  }
  if(!is.na(neither)){
    heat_status = "neither"
  }
  if(!is.na(heat_yes) & !is.na(fire_yes)) {
    heat_status = "both"
  }
  return(heat_status)
}

#testing the heat function
table(str_detect(posts_df$text, "fireplace not"))
posts_df$text[517]

heat_pattern = regex("heating | heater | wood burning stove | fireplace | central heat| heat", ignore_case = T)
posts_df$heat = str_extract_all(posts_df$text, heat_pattern)

# now use lapply to extract

heat_status = lapply(posts_df$text, has_heat)

heat_status_2 = unlist(heat_status)
posts_df$heat_status = heat_status_2
table(heat_status_2)

# now the graphs: is air conditioning more common than heating? 

comparing_AC_Heat = as.data.frame(table(posts_df$heat_status, posts_df$AC_status))
AC_table =table(posts_df$heat_status, posts_df$AC_status)
AC_table

#heat graph
ggplot(posts_df[!is.na(heat_status),], aes(x = heat_status, fill = heat_status)) +
  geom_bar(position = position_dodge()) +
  geom_text(stat = "count",aes(label=..count..), position=position_dodge(width=0.9), vjust=-0.5)+
  labs(title = "Heat Status Of Posts", x = "Heat Status", y = "Count") +
  scale_fill_viridis_d() + ylim(0,45000) + guides(fill = FALSE) + facet_wrap(region~.)



#AC graph
ggplot(posts_df[!is.na(AC_status),], aes(x = AC_status, fill = AC_status)) +
  geom_bar(position = position_dodge()) +
  geom_text(stat = "count",aes(label=..count..), position=position_dodge(width=0.9), vjust=-0.5)+
  labs(title = "Air Conditioning Status Of Posts", x = "AC Status", y = "Count") +
  scale_fill_viridis_d()+ ylim(0,45000) +guides(fill = FALSE)

# heat & AC together 
ggplot(posts_df[!is.na(heat_status) & !is.na(AC_status),], aes(x = heat_status, fill = AC_status)) +
  geom_bar(position = position_dodge()) +
  geom_text(stat = "count",aes(label=..count..), position=position_dodge(width=0.9), vjust=-0.5) +
  facet_wrap(AC_status ~ .) +
  labs(title = "Air Conditioning Status by Heat Status", x = "Heat Status", y = "Count") +
  scale_fill_viridis_d()

ggplot(posts_df[!is.na(heat_status) & !is.na(AC_status),], aes(fill = heat_status, x = AC_status)) +
  geom_bar(position = position_dodge()) +
  geom_text(stat = "count",aes(label=..count..), position=position_dodge(width=0.5), vjust=-0.1) +
  facet_wrap(heat_status~.)
  

# heat and AC by location: 
ggplot(posts_df[!is.na(heat_status),], aes(x = heat_status, fill = heat_status)) +
  geom_bar(position = position_dodge()) +
  geom_text(stat = "count",aes(label=..count..), position=position_dodge(width=0.5), vjust=-0.24)+
  labs(title = "Heat Status Of Posts", x = "Heat Status", y = "Count") +
  scale_fill_viridis_d() + ylim(0,1500) + guides(fill = FALSE) + facet_wrap(region~.)

ggplot(posts_df[!is.na(AC_status),], aes(x = AC_status, fill = AC_status)) +
  geom_bar(position = position_dodge()) +
  geom_text(stat = "count",aes(label=..count..), position=position_dodge(width=0.9), vjust=-0.5)+
  labs(title = "Air Conditioning Status Of Posts", x = "AC Status", y = "Count") +
  scale_fill_viridis_d()+guides(fill = FALSE) + facet_wrap(region~.) +
  ylim(0, 8000)

ggplot(posts_df[!is.na(heat_status) & !is.na(AC_status) ,], aes(fill = heat_status, x = AC_status)) +
  geom_bar(position = position_dodge()) +
  facet_wrap(region~.) + labs(title = "AC and Heat Status of Apartments By Craigslist Region", x = "AC Status", y = "Count", fill = "Heat Status") +
  scale_fill_viridis_d()

#Question 8

#detecting email addresses: 

#regular expression did not detect emails 
str_detect(posts_df$text, regex("\\w+\\@\\.w{3}", ignore_case = T))

#detecting an @ sign sandwiched between two word characters - 308 of them 
table(str_detect(posts_df$text, regex("\\w\\@\\w", ignore_case = T)))
the_at = str_detect(posts_df$text, regex("\\w\\@\\w", ignore_case = T))

whats_the_at = str_extract(posts_df$text, regex("[A-Za-z]{4}\\@\\w", ignore_case = T))

whats_the_at[!is.na(whats_the_at)]

table(whats_the_at)
whats_at = posts_df[whats_the_AT,]

#detecting phone numbers: 

table(str_detect(posts_df$text, regex("\\(?\\d{3}\\)?[.-]? *\\d{3}[.-]? *[.-]?\\d{4}", ignore_case = T)))

has_phone_subset = posts_df[has_phone_num,]
has_phone_subset$text
# which posts contain "show contact info"
hide_nums = str_detect(posts_df$text, regex("show contact info", ignore_case = T))
table(hide_nums)

hidden_nums = posts_df[hide_nums,] 
