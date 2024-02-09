import random

# IDE does not support input, and returns EOFError
name = input("What is your name?: ")
question = input("What is your question?: ")

answer = ""

number = random.randint(1,9)

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
  answer = "Better not tell you now"
elif number == 8:
  answer = "My sources say no"
elif number == 9:
  answer = "Outlook not so good"
else:
  print("Error")

print("Magic 8-Ball's answer: ", answer)
