package Project1;
import java.util.Scanner;
public class Blackjack extends P1Random{
    public static void main (String[] args) {
        P1Random rng = new P1Random();
        Scanner scan = new Scanner(System.in);
        boolean runGame = true;  //defining variables
        boolean current = true;
        int playerWins = 0;
        int computerWins = 0;
        int tieGames = 0;
        int totalGames = 0;
        int hand = 0;
        int dealerHand = 0;
        while (runGame) {  //main while loop for the game
            if (totalGames > 0) {
                System.out.println();
            }
            System.out.println("START GAME #" + (totalGames + 1)); //changes to reflect number of games played
            hand = 0;
            dealerHand = 0;

            System.out.println();
            int playerCard = rng.nextInt(13) + 1;   //this section of code determines whether the card is a royal card
            if (playerCard == 1) {
                System.out.println("Your card is a ACE!");
                hand += playerCard;
                System.out.println("Your hand is: " + hand);
            } else if (playerCard == 11) {
                System.out.println("Your card is a JACK!");
                hand += 10;
                System.out.println("Your hand is: " + hand);
            } else if (playerCard == 12) {
                System.out.println("Your card is a QUEEN!");
                hand += 10;
                System.out.println("Your hand is: " + hand);
            } else if (playerCard == 13) {
                System.out.println("Your card is a KING!");
                hand += 10;
                System.out.println("Your hand is: " + hand);
            } else {
                System.out.println("Your card is a " + playerCard + "!");
                hand += playerCard;
                System.out.println("Your hand is: " + hand);
            }
            while (current) {  //current game loop
                System.out.println();
                choiceMethod();
                int choice = scan.nextInt();
                System.out.println();
                if (choice == 1) { //executes if user chooses to be dealt another card
                    playerCard = rng.nextInt(13) + 1;
                    if (playerCard == 1) {  //executes if player is dealt an ACE
                        System.out.println("Your card is a ACE!");
                        hand += playerCard;

                        if (hand == 21) { //checks for blackjack
                            System.out.println(" Your hand is: " + hand);
                            System.out.println();
                            System.out.println("BLACKJACK! You win!");
                            System.out.println();
                            playerWins++;
                            totalGames++;
                            break;
                        } else if (hand > 21) { //checks for bust
                            System.out.println("Your hand is: " + hand);
                            System.out.println();
                            System.out.println("You exceeded 21! You lose.");
                            computerWins++;
                            totalGames++;
                            break;
                        } else {
                            System.out.println("Your hand is: " + hand);
                        }

                    } else if (playerCard <= 10 && playerCard >= 2) {  //executes for all non-royal cards
                        System.out.println("Your card is a " + playerCard + "!");
                        hand += playerCard;
                        if (hand == 21) {
                            System.out.println(" Your hand is: " + hand);
                            System.out.println();
                            System.out.println("BLACKJACK! You win!");
                            System.out.println();
                            playerWins++;
                            totalGames++;
                            break;
                        } else if (hand > 21) {
                            System.out.println("Your hand is: " + hand);
                            System.out.println();
                            System.out.println("You exceeded 21! You lose.");
                            computerWins++;
                            totalGames++;
                            break;
                        } else {
                            System.out.println("Your hand is: " + hand);
                        }
                    } else if (playerCard == 11) {  //executes for JACK
                        System.out.println("Your card is a JACK!");
                        hand += 10;
                        if (hand == 21) {
                            System.out.println(" Your hand is: " + hand);
                            System.out.println();
                            System.out.println("BLACKJACK! You win!");
                            System.out.println();
                            playerWins++;
                            totalGames++;
                            break;
                        } else if (hand > 21) {
                            System.out.println("Your hand is: " + hand);
                            System.out.println();
                            System.out.println("You exceeded 21! You lose.");
                            computerWins++;
                            totalGames++;
                            break;
                        } else {
                            System.out.println("Your hand is: " + hand);
                        }
                    } else if (playerCard == 12) { //executes for QUEEN
                        System.out.println("Your card is a QUEEN!");
                        hand += 10;
                        if (hand == 21) {
                            System.out.println(" Your hand is: " + hand);
                            System.out.println();
                            System.out.println("BLACKJACK! You win!");
                            System.out.println();
                            playerWins++;
                            totalGames++;
                            break;
                        } else if (hand > 21) {
                            System.out.println("Your hand is: " + hand);
                            System.out.println();
                            System.out.println("You exceeded 21! You lose.");
                            computerWins++;
                            totalGames++;
                            break;
                        } else {
                            System.out.println("Your hand is: " + hand);
                        }
                    } else { //executes for KING
                        System.out.println("Your card is a KING!");
                        hand += 10;
                        if (hand == 21) {
                            System.out.println(" Your hand is: " + hand);
                            System.out.println();
                            System.out.println("BLACKJACK! You win!");
                            System.out.println();
                            playerWins++;
                            totalGames++;
                            break;
                        } else if (hand > 21) {
                            System.out.println("Your hand is: " + hand);
                            System.out.println();
                            System.out.println("You exceeded 21! You lose.");
                            computerWins++;
                            totalGames++;
                            break;
                        } else {
                            System.out.println("Your hand is: " + hand);
                        }
                    }

                } else if (choice == 2){  //executes if user decides to hold
                    dealerHand = rng.nextInt(11) + 16;
                    if (dealerHand > 21) { //dealer bust
                        System.out.println("Dealer's hand: " + dealerHand);
                        System.out.println("Your hand is: " + hand);
                        System.out.println();
                        System.out.println("You win!");
                        playerWins++;
                        totalGames++;
                        break;

                    } else if (dealerHand == hand){  //tie
                        System.out.println("Dealer's hand: " + dealerHand);
                        System.out.println("Your hand is: " + hand);
                        System.out.println();
                        System.out.println("It's a tie! No one wins!");
                        tieGames++;
                        totalGames++;
                        break;
                    } else { //dealer win
                        if (dealerHand > hand){
                            System.out.println("Dealer's hand: " + dealerHand);
                            System.out.println("Your hand is: " + hand);
                            System.out.println();
                            System.out.println("Dealer wins!");
                            computerWins++;
                            totalGames++;
                            break;
                        } else { //player win
                            System.out.println("You win!");
                            playerWins++;
                            totalGames++;
                            break;
                        }

                    }

                } else if (choice == 3){ //executes to show stats
                    System.out.println("Number of Player wins: " + playerWins);
                    System.out.println("Number of Dealer wins: "+ computerWins);
                    System.out.println("Number of tie games: " + tieGames);
                    System.out.println("Total # of games played is: " + totalGames);
                    System.out.println("Percentage of Player wins: " + ((1.0*playerWins/totalGames)*100)+ "%");
                } else if (choice == 4){ //quits main while loop
                    current = false;
                    runGame = false;
                    break;
                } else { // Shows error statement if user enters invalid number
                    System.out.println("Invalid input!");
                    System.out.println("Please enter an integer value between 1 and 4.");
                }

            }


        }
    }


    public static void choiceMethod(){ //method that print out the various choices available to player
        System.out.println("1. Get another card");
        System.out.println("2. Hold hand");
        System.out.println("3. Print statistics");
        System.out.println("4. Exit");
        System.out.println();
        System.out.print("Choose an option: ");
    }

}
