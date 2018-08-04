changelog:
fixed bug with Arcade mode going on in storymode instead
added healthbar effect
redesigned shots: implemented 2nd shot type
changed NULL to nullptr, changed define to constants
fixed Pattern bug, due to adjustments on LaserBloom breaking other patterns like Shooter4
implemented proper deletes on pointers. (Still not used to RAII smart pointers yet, but will work on it)
added Blitz shot and one secret Echo shot, shown how to unlock at end game
Game now asks whether you want to start a new game if you have a previous save file
rebalanced stages to match with new bullet types
release stable version of arcade mode (just need to add a lot more levels)
changed how arcade difficulty switching works
changed a bit on ZONE2
reworked cursor movement due to previous abnormality
cursor position shown when paused/frozen.
arcade mode disabled, changed to beta mode instead
greatly reduced difficulty for easy and medium levels (except Level_A)
*added removeIValue in List class
healthbar disabled after game over
