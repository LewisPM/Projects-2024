# Doodlebug Simulator


## About:

A two-dimensional preadator-prey simulation. Watch how the Doodlebug population changes with ants as prey.

* _The Doodlebugs and Ants exist in a 20x20 grid._
* _The simulation starts with five Doodlebugs and one hundred Ants._
* _The user presses 'Enter' to run a day in the simulation._
* _Ants breed after surviving three days._
* _Doodlebugs breed after surviving eight days. If they don't eat within three days they starve and pass away._

Project parameters originate from an NYU Bridge Course assignment.

## Implementation:

* We will initalize the the world in a 20x20 grid using 'X' to represent Doodlebugs, 'o' to represent Ants and '-' to represent empty spaces.
* We will use an abstract class 'Organism' to setup the 'Ant' and 'Doodlebug' classes.
* Organisms will have a 'Move' method that keeps them within the bounds of the grid.
    * Movement for Doodlebugs will either be 1. to eat an ant or 2. to a random empty space. If there are no ants or free spaces the Doodlebug will not move that day.
    * Movement for Ants will be to a random empty space. If there are no free spaces the ant will not move that day.

## Technologies/ Languages:

C++
VSCode (V1.86.0)
Git Bash (V2.34.1.windows.1)
GitHub CLI

**Status: In Progress**

_Created 07.2024_
_© Pauline Lewis NY, NY 2024_
