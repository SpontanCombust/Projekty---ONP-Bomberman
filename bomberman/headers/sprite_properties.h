#ifndef BOUNDING_BOXES_H
#define BOUNDING_BOXES_H

#define TILE_SIZE 32

// nalezy ustawiac koordynaty dokladnie, by uniknac naruszenia ochrony pamieci przy sprawdzaniu kolizji, bo moze np. sprawdzac pole, ktore nie istnieje
#define CBX_PLAYER 7    // Collision box x origin
#define CBY_PLAYER 11   // Collision box y origin
#define CBW_PLAYER 18   // Collision box width
#define CBH_PLAYER 21   // Collision box height

#endif