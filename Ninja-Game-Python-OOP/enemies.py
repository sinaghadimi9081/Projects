import pygame as pg
import math
import random

from main import *
from player import *
from setting import *

class Enemy:
    def __init__(self,game):
        self.player = Player(self)
        self.game = game
        self.X_right, self.Y_right = ENEMY_ONE_POS
        self.X_left, self.Y_left = ENEMY_TWO_POS
    def movement(self):
        self.Y_right +=5
        if self.Y_right>950:
            self.Y_right=50
        if self.Y_right>100:
            self.Y_left += 5
        if self.Y_left>950:
            self.Y_left=40
    @property
    def enemy_pos_left(self):
        return self.Y_left
    @property
    def enemy_pos_right(self):
        return self.Y_right
    def draw(self):
        self.game.screen.blit(bad_ninja_img_right,(self.X_right,self.Y_right))
        self.game.screen.blit(bad_ninja_img_left,(self.X_left,self.Y_left))
    def update(self):
        self.movement()

class Wall:
    def __init__(self,game):
        self.game = game
        self.X_right, self.Y_right = WALL_ONE_POS
        self.X_left, self.Y_left = WALL_TWO_POS
    def movement(self):
        self.Y_right +=3
        if self.Y_right>900:
            self.Y_right=40
        if self.Y_right>150:
            self.Y_left +=3
        if self.Y_left>900:
            self.Y_left=40
    @property
    def wall_pos_left(self):
        return self.Y_left
    @property
    def wall_pos_right(self):
        return self.Y_right
    def draw(self):
        self.game.screen.blit(wall_img,(self.X_left,self.Y_left))
        self.game.screen.blit(wall_img,(self.X_right,self.Y_right))
    def update(self):
        self.movement()
        
# class Wall:
#     def __init__(self,game):
#         self.game = game
#         self.X_right, self.Y_right = WALL_ONE_POS
#         self.X_left, self.Y_left = WALL_TWO_POS
#     def movement(self):
#         self.Y_right +=3
#         if self.Y_right>932:
#             self.Y_right=35
#         if self.Y_right>150:
#             self.Y_left +=3
#         if self.Y_left>932:
#             self.Y_left=40
    
#     @property
#     def wall_pos_left(self):
#         return self.Y_left
#     @property
#     def wall_pos_right(self):
#         return self.Y_right
#     @property
#     def wall_pos_x_right(self):
#         return self.X_right
#     @property
#     def wall_pos_x_left(self):
#         return self.X_left
    
#     def draw(self):
#         self.game.screen.blit(wall_img,(self.X_left,self.Y_left))
#         self.game.screen.blit(wall_img,(self.X_right,self.Y_right))
#     def update(self):
#         self.movement()