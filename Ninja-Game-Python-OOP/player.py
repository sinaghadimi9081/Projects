import pygame as pg
import sys

from setting import *
from main import *
from enemies import *


class Enemy:
    def __init__(self,game):
        self.game = game
    def movement(self):
        ENEMY_SPEED = 5 + ENEMY_INCREMENT[0]
        # print(f'ENEMY SPEED = {ENEMY_SPEED}')
        ENEMY_ONE_POS[1] += ENEMY_SPEED
        if math.ceil(pygame.time.get_ticks()/1000)>1:
            ENEMY_TWO_POS[1] += ENEMY_SPEED
        if (math.ceil(pygame.time.get_ticks()/1000))%15==0:
            ENEMY_INCREMENT[0] += 0.002
        # print(f'ENEMY INCREMENT = {ENEMY_INCREMENT}')
        if ENEMY_TWO_POS[1]>950:
            ENEMY_TWO_POS[1]=40
        if ENEMY_ONE_POS[1]>950:
            ENEMY_ONE_POS[1]=50
    def draw(self):
        self.game.screen.blit(bad_ninja_img_right,(ENEMY_ONE_POS))
        if math.ceil(pygame.time.get_ticks()/1000)>1:
            self.game.screen.blit(bad_ninja_img_left,(ENEMY_TWO_POS))
    def update(self):
        self.movement()

class Wall:
    def __init__(self,game):
        self.game = game
    def movement(self):
        WALL_SPEED = 3 + WALL_INCREMENT[0]
        # print(f'WALL SPEED = {WALL_SPEED}')
        WALL_ONE_POS[1] += WALL_SPEED
        if math.ceil(pygame.time.get_ticks()/1000)>1:
            WALL_TWO_POS[1] += WALL_SPEED
        if (math.ceil(pygame.time.get_ticks()/1000))%10==0:
            WALL_INCREMENT[0] += 0.004
        # print(f'WALL INCREMENT = {WALL_INCREMENT}')
        if WALL_ONE_POS[1]>928:
            WALL_ONE_POS[1]=35
        if WALL_TWO_POS[1]>928:
            WALL_TWO_POS[1]=40
    def draw(self):
        self.game.screen.blit(wall_img,(WALL_ONE_POS))
        if math.ceil(pygame.time.get_ticks()/1000)>1:
            self.game.screen.blit(wall_img,(WALL_TWO_POS))
    def update(self):
        self.movement()
        
class Player:
    def __init__(self,game):
        self.game = game
    def movement(self):
        keys = pg.key.get_pressed()
        if keys[pg.K_RIGHT]:
            PLAYER_POS[0]= 550
            PLAYER_POS[1]= 900
        if keys[pg.K_LEFT]:
            PLAYER_POS[0]= 290
            PLAYER_POS[1]= 900
    def draw(self):
        if PLAYER_POS[0]==418:
            self.game.screen.blit(ninja_img_right,(PLAYER_POS))
        if PLAYER_POS[0]==550:
            self.game.screen.blit(ninja_img_right,(PLAYER_POS))
        if PLAYER_POS[0]==290:
            self.game.screen.blit(ninja_img_left,(PLAYER_POS))
    def update(self):
        self.collision_player()
        self.movement()
    def collision_player(self):
        print(f'one - player : {ENEMY_ONE_POS[0]-PLAYER_POS[0]}')
        print(f'two - player : {ENEMY_TWO_POS[0]-PLAYER_POS[0]}')
        if (WALL_ONE_POS[0]-PLAYER_POS[0]+8==0 and PLAYER_POS[1]-WALL_ONE_POS[1]<-25) :
            HEALTH[0] -= 1
        if (WALL_TWO_POS[0]-PLAYER_POS[0]-8==0 and PLAYER_POS[1]-WALL_TWO_POS[1]<-25):
            HEALTH[0] -= 1
        if(ENEMY_ONE_POS[0]-PLAYER_POS[0]==0 and PLAYER_POS[1]-ENEMY_ONE_POS[1]<-47):
            HEALTH[0] -= 1
        if(ENEMY_TWO_POS[0]-PLAYER_POS[0]==0 and PLAYER_POS[1]-ENEMY_TWO_POS[1]<-47):
            HEALTH[0] -= 1
            
    
class Bullet:
    def __init__(self,game):
        self.game = game
    def movement(self):
        if BULLET_STATE[0]=="shot":
            BULLET_POS[1] -=2
        if BULLET_STATE[0]=="ready":
            if (PLAYER_POS[0]==550):
                BULLET_POS[0] = 560
            elif (PLAYER_POS[0]==290):
                BULLET_POS[0] = 310
        if BULLET_POS[1] < 0:
            BULLET_POS[1] =900
            BULLET_STATE[0] = "ready"
    def draw(self):
        if BULLET_STATE[0]=="shot":
            self.game.screen.blit(shuriken_img,(BULLET_POS))
    def collision_with_enemy(self):
        if BULLET_STATE[0]=="shot":
            if (BULLET_POS[0]-ENEMY_ONE_POS[0]-10==0 and BULLET_POS[1]-ENEMY_ONE_POS[1]<20): 
                SCORE[0] += 1
                BULLET_STATE[0]="ready"
                BULLET_POS[1]=900
                ENEMY_ONE_POS[1]=50
            if (BULLET_POS[0]-ENEMY_TWO_POS[0]-20==0 and BULLET_POS[1]-ENEMY_TWO_POS[1]<20):
                SCORE[0] += 1
                BULLET_STATE[0]="ready"
                BULLET_POS[1]=900
                ENEMY_TWO_POS[1]=45
            if(WALL_ONE_POS[0]-BULLET_POS[0]==-18 and BULLET_POS[1]-WALL_ONE_POS[1]<0):
                print(f'wall one - bullet: {WALL_ONE_POS[0]-BULLET_POS[0]}')
                BULLET_STATE[0]="ready"
                BULLET_POS[1]=900
            if(WALL_TWO_POS[0]-BULLET_POS[0]==-12 and BULLET_POS[1]-WALL_TWO_POS[1]<0):
                print(f'wall two - bullet: {WALL_TWO_POS[0]-BULLET_POS[0]}')
                BULLET_STATE[0]="ready"
                BULLET_POS[1]=900
    def update(self):
        self.collision_with_enemy()
        self.movement()
    
        
class Health:
    def __init__(self,game):
        self.game = game
    def draw(self):
        self.game.screen.blit(full_health_img,(HEARTS_POS[0],HEARTS_POS[1]))
        self.game.screen.blit(full_health_img,(HEARTS_POS[2],HEARTS_POS[3]))
        self.game.screen.blit(full_health_img,(HEARTS_POS[4],HEARTS_POS[5]))
        if HEALTH[0]<3:
            self.game.screen.blit(damaged_health_img,(DAMAGED_HEART_POS[0],DAMAGED_HEART_POS[1]))
            HEARTS_POS[0]= -70
            HEARTS_POS[1]= -100
        if HEALTH[0]<2:
            self.game.screen.blit(damaged_health_img,(DAMAGED_HEART_POS[2],DAMAGED_HEART_POS[3]))
            HEARTS_POS[2]= -70
            HEARTS_POS[3]= -100
        if HEALTH[0]<1:
            self.game.screen.blit(damaged_health_img,(DAMAGED_HEART_POS[4],DAMAGED_HEART_POS[5]))
            HEARTS_POS[4]= -70
            HEARTS_POS[5]= -100

    