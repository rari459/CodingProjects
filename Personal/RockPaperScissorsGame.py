import tkinter
import random

print("This is a Rock, Paper, and Scissors game. Enter R, P, or S and play against the computer.")

lives = 0
lives_limit= 3
score = 0

while lives < lives_limit:
    user_input = input("Enter your selection here: ")
    computer_guess = random.randint(1, 3)

    if user_input is "R":
        user_guess = 1
    if user_input is "P":
        user_guess = 2
    if user_input is "S":
        user_guess = 3

    if user_guess == 1:
        print("You chose Rock")
    elif user_guess == 2:
        print("You chose Paper")
    else:
        print("You chose Scissors")


    if computer_guess == 1:
        print("The computer chose Rock")
    elif computer_guess == 2:
        print("The computer chose Paper")
    else:
        print("The computer chose Scissors")


    if user_guess == 3 and computer_guess == 1 or user_guess == 1 and computer_guess == 2 or user_guess == 2 and computer_guess == 3:
        print("You lose a life!")
        lives = lives ++ 1
    elif user_guess == computer_guess:
        print("Guess Again!")
    else:
        print("The computer strikes out")
        score = score + + 1

    print("Lives Left:")
    print(lives_limit-int(lives))
    print("Score: " + str(score))

    if lives == 3:
        print("Game Over")
        break




