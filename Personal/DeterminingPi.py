import random
import math

def random_ball_drop():
    # Drops a ball at random location on 20x20 grid
    global ballx
    global bally
    ballx = random.uniform(-10,10)
    bally = random.uniform(-10,10)

def square(n):
    # Gives value of 1 when ball in within square with edge length n
    # n must be less <= 10
    global in_square
    in_square = 0
    if abs(ballx) <= float(n/2) and abs(bally) <= float(n/2):
        in_square = 1

def circle(n):
    # Gives value of 1 when ball in within circle with radius n
    # n must be less <= 10
    global in_circle
    in_circle = 0
    if math.sqrt(((ballx)**2 + (bally)**2)) <= n:
        in_circle = 1

number_of_simulations = 100_000


circle_count = 0
square_count = 0
for n in range(number_of_simulations):
        random_ball_drop()
        square(10)
        circle(10)
        circle_count = circle_count + in_circle
        square_count = square_count + in_square

pi = circle_count / square_count
print(pi)
