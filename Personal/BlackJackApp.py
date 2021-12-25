ask_again = True
import random
print("This is a game of Black Jack against the computer")

buy_in = int(input("Enter your buy in amount for the tournament: "))
play_again = True
while (buy_in) > 0 and play_again is True:
    print("This is how much money you have left: " , buy_in)
    bet = int(input("Place your bet for this round: "))

    user_card1 = random.randint(0, 12)
    user_card2 = random.randint(0, 12)
    computer_card1 = random.randint(0, 12)
    computer_card2 = random.randint(0, 12)
    user_card_total = 0
    computer_card_total = 0

    if user_card1 > 9 and user_card2 > 9:
        user_card_total = 20
    elif user_card1 > 9:
        user_card_total = 10 + user_card2 + 1
    elif user_card2 > 9:
        user_card_total = 10 + user_card1 + 1
    else:
        user_card_total = user_card1 + user_card2 + 2

    if computer_card1 > 9 and computer_card2 > 9:
        computer_card_total = 20
    elif computer_card1 > 9:
        computer_card_total = 10 + computer_card2 + 1
    elif computer_card2 > 9:
        computer_card_total = 10 + computer_card1 + 1
    else:
        computer_card_total = computer_card1 + computer_card2 + 2

    cards = ["A", 2, 3, 4, 5, 6, 7, 8, 9, 10, "J", "Q", "K"];

    print("These are your cards: ", cards[user_card1], cards[user_card2])
    print("These are the the computer's cards: ", cards[computer_card1], "X")
    ask_again = True

    while user_card_total < 22 and 22 > computer_card_total > 16:
        if ask_again is True:
            deal = input("Would you like another card? Enter 'Y' for Yes, 'N' for No.")
        if deal is "Y":
            new_user_card = random.randint(0, 12)
            print("Additional Card: ", cards[new_user_card])
            if new_user_card > 9:
                user_card_total = 10 + user_card_total
            else:
                user_card_total = new_user_card + user_card_total + 1
            print("Total Card Value: ", user_card_total)
        elif deal is "N":
            ask_again = False
            break

    while user_card_total < 22 and computer_card_total < 17:
        if ask_again is True:
            deal = input("Would you like another card? Enter 'Y' for Yes, 'N' for No.")
        if deal is "Y":
            new_user_card = random.randint(0, 12)
            print("Additional Card: ", cards[new_user_card])
            if new_user_card > 9:
                user_card_total = 10 + user_card_total
            else:
                user_card_total = new_user_card + user_card_total + 1
            print("Total Card Value: ", user_card_total)
        elif deal is "N":
            new_computer_card = random.randint(0, 12)
            ask_again = False
            print("Computer Additional Card: ", cards[new_computer_card])
            if new_computer_card > 9:
                computer_card_total = 10 + computer_card_total
            else:
                computer_card_total = new_computer_card + computer_card_total + 1
            print("Computer Total Card Value: ", computer_card_total)

    if user_card_total > 21:
        print("You crossed 21, you lose!")
        buy_in = buy_in - bet
    elif computer_card_total > 21:
        print("The computer crossed 21, you win!")
        buy_in = buy_in + bet
    elif user_card_total > computer_card_total:
        print("This was the computer card total", computer_card_total)
        print("This was your card total: ", user_card_total)
        print("You beat the computer!")
        buy_in = buy_in + bet
    elif user_card_total < computer_card_total:
        print("This was the computer card total", computer_card_total)
        print("This was your card total: ", user_card_total)
        print("The computer beat you!")
        buy_in = buy_in - bet
    elif user_card_total == computer_card_total:
        print("You tied!")

    round = input(" Would you like to play another round? Enter (Y/N): ")
    if round is "Y":
        play_again is True
    elif round is "N":
        break

print("This is how much money you have left: " , buy_in)
print("Thank you for playing!")