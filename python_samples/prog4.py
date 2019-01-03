## Mira Mastoras
## November 4, 2016
## ECS 10
## Homework 4 Loopapalooza 2
## prog4.py

## Prob 1 *
def sumOfOdds(limit):
    'expects an int >= 1 as argument'
    'calculates sum of odds btw 1 and the int'
    total = 0 
    for i in range(1, limit + 1):
        if i % 2 == 0:
            pass
        else:
           total = total + i 
    return total

## Prob 2
def countChar(character, string):
    'expects a character and string'
    'counts number of times character appears in string'
    total = 0
    for char in string:
        if char == character:
            total = total + 1
        else:
            pass
    return total

## Prob 3
def countDiffs(string1, string2):
    'expects two strings as argument'
    'counts number of differences between the two'
    totaldiffs = 0
    for i in string1:
        index = string1.find(i)
        if string1[index] != string2[index] :
            totaldiffs = totaldiffs + 1
        else:
            pass
    return totaldiffs

## Prob 4

def avgSumOfSquares(numlist):
    'expects list of numbers as argument'
    'computes average sum of squares of the numbers'
    seq = numlist
    if seq == []:
        return None
    total = 0 
    for i in seq:
        sqrnum = (i**2)
        total = total + sqrnum
    avgsum = total / len(seq) 
    return avgsum

## Prob 5

code = [["a",".-"],["b","-..."],["c","-.-."],["d","-.."],
        ["e","."],["f","..-."],["g","--."],["h","...."],
        ["i",".."],["j",".---"],["k","-.-"],["l",".-.."],
        ["m","--"],["n","-."],["o","---"],["p",".--."],
        ["q","--.-"],["r",".-."],["s","..."],["t","-"],
        ["u","..-"],["v","...-"],["w",".--"],["x","-..-"],
        ["y","-.--"],["z","--.."]]

def is_valid(character):
    'expects string as argument'
    'checks to see if each character is part of code array'
    for char in code:
        if character == char[0]:
            return True
        else:
            pass
    return False
    
def translate_morse(sentence):
    'expects sentence as argument, translates it to morse code'
    morse = 'Morse code: '
    for char in sentence:
        if char == ' ':
            morse = morse + '   '
        elif is_valid(char) == True: 
            index = 0
            for i in code:
                if i[0] == char:
                    morse = morse + ' ' + i[1]
        else:
            morse = morse + "###"
    return morse                    
    
def morseCode():
    while True:
        string = input("Enter sentence to be translated (*** to end): ")
        if string == "***" :
            print("Program has ended")
            break
        else:
            n = translate_morse(string)
            print(n)
            

morseCode()




    
    
