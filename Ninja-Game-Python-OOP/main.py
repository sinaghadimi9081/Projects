import pygame
import sys
import math
from setting import *
from player import *
class Game:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode(RES)
        self.time =pygame.time.Clock()
        self.new_game()
    def new_game(self):
        self.font = pygame.font.Font('freesansbold.ttf',32)
        self.player = Player(self)
        self.enemy = Enemy(self)
        self.wall = Wall(self)
        self.bullet = Bullet(self)
        self.health = Health(self)
        
    
    def update(self):
        self.bullet.update()
        self.wall.update()
        self.enemy.update()
        self.player.update()
        pygame.display.flip()
        self.time.tick(60)
    
    def draw(self):
        CLOCK = math.ceil(pygame.time.get_ticks()/1000)
        Title_icon()
        self.screen.blit(sky,(300,0))
        self.screen.blit(boundary_picture,(0,0))
        self.screen.blit(boundary_picture,[600,0])
        self.screen.blit(self.font.render(f'score : {SCORE[0]}', True, (0,0,0)),SCORE_POS)
        self.screen.blit(self.font.render(f'time : {CLOCK}', True, (0,0,0)),(300,50))
        self.enemy.draw()
        self.wall.draw()
        self.player.draw()
        self.bullet.draw()
        self.health.draw()
        self.game_over()
        
    def game_over(self):
        if HEALTH[0]<1:
            PLAYER_POS[0] = -100
            PLAYER_POS[1] = -100
            WALL_ONE_POS[0] = -100
            WALL_ONE_POS[1] = -100
            WALL_TWO_POS[0] = -100
            WALL_TWO_POS[1] = -100
            ENEMY_ONE_POS[0] = -100
            ENEMY_TWO_POS [1] = -100
            self.screen.blit(self.font.render('GAME OVER', True, (0,0,0)),(355,500))
    def check_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    if BULLET_STATE[0] == "ready":
                        BULLET_STATE[0] = "shot"
                        self.bullet.movement()         
    def run(self):
        while True:
            self.check_events()
            self.draw()
            self.update()

class Menu:
    def __init__(self):
        self.screen = pygame.display.set_mode(RES)
    def draw(self):
        # box = pg.Rect(323,456,256,256)
        # start_font = pygame.font.Font('freesansbold.ttf', 24)
        # text = start_font.render("PRESS TO START", True, (0,0,0))
        self.screen.blit(sky,(300,0))
        self.screen.blit(boundary_picture,(0,0))
        self.screen.blit(boundary_picture,(600,0))
        self.screen.blit(start_button,(323,456))
        # pg.draw.rect(self.screen,(0,0,0),box,2)
        # self.screen.blit(text,(350,605))
    def run(self):
        while True:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if event.type == pg.MOUSEBUTTONDOWN:
                    if pg.Rect(323,456,256,256).collidepoint(event.pos):
                        game = Game()
                        game.run()
            self.draw()
            self.update()
    def update(self):
        pygame.display.flip()
if __name__ == '__main__' :
    menu = Menu()
    menu.run()
    