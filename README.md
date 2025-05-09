# ProjetIF2B

##2 personnes

1. Start game

-> Ask board size (6x6 to 12x12)
    ex : 'printf();
         Do {
         Size = scanf();
         } With Size control.'

    Tab[Size][Size], with  6<Size<12 or 7<13 if we do A B C 1 2 3 borders, or 2x that if |_|.

-> Random player chosen to start

    ex : Rand(time=NULL);
         starting_Player = Rand()%2
    //Keep the flag until game start.


-> both player have same number of chest pieces.

For a) and b) : Maybe have them flag conquest = 0 connect = 1 and when creating chest pieces
structures : have a flag control to see if we add special rules in them ???

ex :
Struct Piece {
    char name[] ? // not useful ?
    int color ?
    int position[][]
}

fct {
if chest piece (name) {      //ou switch

    }
}

a) Conquest

/*




*/

/*

b) Connect


2. Load existing game
    // We'll see later

3. Leave
    ex : if {3} return 0;

*/



/*
2 modes : Conquest et Connect

|──────────────|
|   Conquest   |  ==>
|──────────────|

|──────────────|
|   Connect    |  ==>
|──────────────|



Structname tab[Xmax][Xmax];
tab[][X].var = Valeur;
safecopy(tab[][X].var, "Str ex");


=> fin : fct comptage points.
