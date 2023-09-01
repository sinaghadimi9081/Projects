
import pygame, sys
import math
import random
from pygame.locals import *
from pathlib import Path
pygame.init()

RES = width, height = 900,1000

PLAYER_POS = [418,900]

ENEMY_ONE_POS= [550,30]
ENEMY_TWO_POS= [290,30]

WALL_ONE_POS =[542,40]
WALL_TWO_POS= [298,200]

BULLET_STATE = ["ready"]
BULLET_POS = [418,900]

HEALTH = [3]
HEARTS_POS=[50,50,120,50,190,50]
DAMAGED_HEART_POS= [50,50,120,50,190,50]

SCORE = [0]
SCORE_POS=[650,50]

ENEMY_INCREMENT = [0]
WALL_INCREMENT = [0]

ACTIVE = False
# input pictures
address=str(Path.cwd())
print(f'{address}python_rep\My_First_game\pictures\wood.png')
start_button = pygame.image.load('C:\Programming\python_rep\My_First_game\pictures\start-button.png')

icon = pygame.image.load('C:\Programming\python_rep\My_First_game\pictures\\ninja-blade.png')
boundary_picture = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\wood.png')
sky = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\sky.png')

ninja_img_right = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\\ninja_right.png')
ninja_img_left = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\\ninja_left.png')

bad_ninja_img_right = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\\bad_ninja_right.png')
bad_ninja_img_left = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\\bad_ninja_left.png')

wall_img = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\wall.png')

shuriken_img = pygame.image.load(f'{address}\python_rep\My_First_game\pictures\shuriken.png')

full_health_img=pygame.image.load(f'{address}\python_rep\My_First_game\pictures\heart.png')
damaged_health_img=pygame.image.load(f'{address}\python_rep\My_First_game\pictures\heart_empty.png')
def Title_icon():
    pygame.display.set_caption("Ninja jump")
    pygame.display.set_icon(icon)


# timer
# clock = pygame.time.Clock()
# font = pygame.font.Font('freesansbold.ttf',32)
# time = clock.tick(100)
# timer_screen =font.render(f'Time : {time}', True, (255,255,255))

    
    
    