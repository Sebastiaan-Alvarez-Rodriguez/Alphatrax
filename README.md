# Alphatrax
A simple relational graph analyzer to recommend movies.
Given a dataset of ratings, users and movies, analyzes the relational graphs to determine what user will enjoy what movie.

Analysis is carried out using [MDC Basic Collaborative Filtering](https://en.wikipedia.org/wiki/Collaborative_filtering).

## Requirements
The requirements are all of the following:
  * GNU Make
  * GNU Compiler Collection (gcc) 4.8.1 or greater!
  * One dataset of [grouplens](http://www.grouplens.org/)

## Compilation
Compile this program by typing `make`, while in the main directory.

## Usage
Type `exec -h` for help.  

Specify `-r <path`, `-u <path>`, `-m <path>`.
These should correspond to paths to the `ratings.dat`, `users.dat`
and `movies.dat` files of the dataset you got from [grouplens](http://www.grouplens.org/)
