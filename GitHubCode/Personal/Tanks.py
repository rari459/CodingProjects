import pygame
import sys
import random

pygame.init()
clock = pygame.time.Clock()
font = pygame.font.Font('freesansbold.ttf', 20)

#Screen
screen_width = 750
screen_height = 500
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption('Tanks')

#Rectangles
player = pygame.Rect(40, screen_height-50, 40, 20)
opponent = pygame.Rect(screen_width - 80, random.randint(0, screen_height), 40, 20)

#Projectile
projectile_dx = 5
projectile_state = "ready"
projectile_x = player.x + 40
projectile_y = player.y
projectile = pygame.Rect(projectile_x, player.y, 10, 10)

#Opponent Bullets
bullet_dx = -5
bullet_x = opponent.x - 40
bullet_y = opponent.y
bullet = pygame.Rect(bullet_x, opponent.y, 10, 10)

def fire_bullet(y):
    pygame.draw.ellipse(screen, (255,0,0),  bullet)
    bullet.y = y
    bullet.x += bullet_dx


def fire_projectile(y):
    global projectile_state
    projectile_state = "fire"
    pygame.draw.ellipse(screen, (255,255,0),  projectile)
    projectile.y = y

player_dy = 0
def player_animation():
    global player_dy
    player.y += player_dy
    if player.top <= 0:
        player.top = 0
    if player.bottom >= screen_height:
        player.bottom = screen_height


opponent_dy = random.randint(2, 5)
opponent_dx = -random.uniform(0,1)
def opponent_animation(opponent):
    global opponent_dy, opponent_dx
    opponent.x += opponent_dx
    opponent.y += opponent_dy
    if opponent.top <= 0:
        opponent_dy *= -1
    if opponent.bottom >= screen_height:
        opponent_dy *= -1

player_score = 0
lives = 3
def collisions(opponent, bullet):
    global player_score, lives
    if opponent.left <= 0:
        opponent.x = screen_width
        lives -= 1
    if opponent.colliderect(projectile):
        opponent.x = screen_width
        player_score += 1
    if player.colliderect(bullet):
        lives -= 1
        bullet.x = opponent.x - 20

def text():
    text = font.render('Tanks', True, (255, 255, 255))
    screen.blit(text, (screen_width / 2 - 24, 40))
    pscore_text = font.render('Player Score: ' + str(player_score), True, (255, 255, 255))
    lives_text = font.render('Lives: ' + str(lives), True, (255, 255, 255))
    screen.blit(pscore_text, (40, screen_height - 40))
    screen.blit(lives_text, (screen_width / 2 + 80, screen_height - 40))


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_DOWN:
                player_dy += 7
            if event.key == pygame.K_UP:
                player_dy -= 7
            if event.key == pygame.K_SPACE:
                fire_projectile(player.y)
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_DOWN:
                player_dy -= 7
            if event.key == pygame.K_UP:
                player_dy += 7

    if lives >= 0:
        collisions(opponent, bullet)
        opponent_animation(opponent)
        player_animation()

        # Visuals
        screen.fill((0, 0, 0))
        pygame.draw.rect(screen, (255, 255, 0), player)
        pygame.draw.rect(screen, (255, 0, 0), opponent)
        fire_bullet(bullet.y)

        if bullet.x <= 0:
            bullet_x = opponent.x - 20
            bullet = pygame.Rect(bullet_x, opponent.y, 10, 10)

        # Text
        text()

        if projectile.x >= screen_width:
            projectile.x = player.x + 50
            projectile_state = "ready"

        if projectile_state is "fire":
            fire_projectile(projectile.y)
            projectile.x += 15

    else:
        screen.fill((0, 0, 0))
        end_text = font.render('GAME OVER', True, (255, 255, 255))
        screen.blit(end_text, (screen_width/2-40, screen_height/2))
        pscore_text = font.render('Player Score: ' + str(player_score), True, (255, 255, 255))
        screen.blit(pscore_text, (40, screen_height - 40))


    pygame.display.flip()
    pygame.display.update()
    clock.tick(60)