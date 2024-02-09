import random

def play_magic8Ball():
    name = str(input("What is your name?: "))
    while name.isalpha() == False:
        print("Please try again, using a valid name.\n")
        name = str(input("What is your name?: "))

    def askQuestion():
        question = input("What is your y/n question?: ")
        questionFormated = question.replace(" ", "")
        questionPart = questionFormated[0:len(questionFormated) - 1]        
        #Test for question split
        #print(questionPart, "and", question[len(question) - 1])

        while questionPart.isalnum() == False or question[len(question) - 1] != "?":
            print("Please retype your question; ensure it is alphanumeric and ends with a question mark.\n")
            #print(questionFormated.isalnum(), question[len(question) - 1])
            question = str(input("What is your y/n question?: "))
            questionFormated = question.replace(" ", "")
            questionPart = questionFormated[0:len(questionFormated) - 1]
            #Test for question split
            #print(questionPart, "and", question[len(question) - 1])

        answer = ""

        number = random.randint(1,8)

        if name.isspace() != True and question.isspace() == False and question:
            print(name, "asks: ", question)
        elif name.isspace() == True and question.isspace() != True:
            print("You ask: ", question)
        else:
            print("Please provide a proper question in the form of a string...")

        if number == 1:
            answer = "Very doubtful"
        elif number == 2:
            answer = "Yes - definitely"
        elif number == 3:
            answer = "It is decidedly so"
        elif number == 4:
            answer = "Without a doubt"
        elif number == 5:
            answer = "Reply hazy, try again"
        elif number == 6:
            answer = "Ask again later"
        elif number == 7:
            answer = "My sources say no"
        elif number == 8:
            answer = "Outlook not so good"
        else:
            print("Error")

        print("Magic 8-Ball's answer: ", answer)

        playAgain = str(input("\nWould you like to ask another question? y/n:"))
        while playAgain not in ["y", "n", "Y", "N", "yes", "no", "YES", "NO", "Yes", "No"]:
            playAgain = str(input("Would you like to ask another question? y/n: "))
        if playAgain in ["y", "Y", "yes", "YES", "Yes"]:
            askQuestion()
        else:
            exit()
    askQuestion()

play_magic8Ball()
