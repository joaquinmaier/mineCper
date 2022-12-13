# HOW TO PLAY:

Beggining
---------

At the beggining of the game, you must choose your desired width and height of the board. Some common values are:

- 8x8 or 9x9:   Beginner
- 16x16:        Intermediate
- 30x16:        Advanced

Although you may choose whichever resolution you desire.

---

In-Game Basics
--------------

During the game, every action is indicated with the corresponding X and Y position you wish to change, separated by a space. However, the format is not strict, so additional spaces will be ignored.[^1]

For example, if you wanted to clear an **X** on the top left corner, you would specify `0 0`, thus selecting the position zero *horizontally*, and then the position zero *vertically*.

Moreover, a few commands are available, selected by putting the corresponding letter first:

* Set Flag (**f**):
    By placing the letter _f_ (lowercase f) before the coordinates, the game will place a flag instead of revealing it.
    This safeguards you from mistakingly selecting it and losing.

    You cannot place flags on spots you have already revealed.

* Unset Flag (**F**):
    By placing the letter _F_ (uppercase f) before the coordinates, the game will attempt to remove a flag instead of revealing, or placing another one.
    This allows you to correct any mistakes you may have done regarding a flag's position.

    This command does is simply ignored if no flags are set in the position specified.

* Exit Game (**e** OR **E**):
    By placing the letter _e_ or _E_ before ANYTHING, the game will close.

    Usage of this command is recommended instead of using Ctrl+C since it frees up used memory.

[^1]: This is with the exception of commands, which are strict.
    All commands MUST be set in the first character, and will be ignored otherwise.

