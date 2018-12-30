## Mira Mastoras
## October 5, 2016
## Homework 2, ECS 10
## prog2.py


## Problem 1
def inchesToMeters(inches):
    """ Converts inches to meters, expects parameter inches """
    conversion_factor = 0.0254
    meters = conversion_factor * inches
    return(meters)

## Problem 2
def poundsToKgs(pounds):
    """ Converts pounds to kilograms, expects parameter pounds """
    conversion_factor = 0.453592
    kgs = conversion_factor * pounds
    return(kgs)

## Problem 3
def bmi(meters,kilograms):
    """ Computes body mass index, expects parameters height in meters, weight in kilograms """
    bmi = kilograms / (meters * meters)
    return(bmi)
    
## Problem 4
def bodyMassIndex():
    """ Computes subject's body mass index, expects no parameters """
    name = input("Please enter the subject's name: ")
    height_inch = float(input("Please enter the subject's height in inches: "))
    weight_lbs = float(input("Please enter the subject's weight in pounds: "))
    height_m = float(inchesToMeters(height_inch))
    weight_kgs = float(poundsToKgs(weight_lbs))
    body_mass_index = float(bmi(height_m, weight_kgs))
    print(name, "has a body mass index of", body_mass_index)
    if body_mass_index < 18.5 :
        print(name, "is underweight.")
    elif 18.5 <= body_mass_index < 25 :
        print(name, "is normal weight.")
    elif 25 <= body_mass_index < 30 :
        print(name, "is overweight.")
    else :
        print(name, "is obese.")

bodyMassIndex()

    
   
        
    
