TEST [SO_LONG]
- [X] if file does not exist
- [x] if file does not have .ber extension
- [x] if file is empty
- [x] if map is too small (at least > 3 in width or length so the map can be surrounded by '1's)
- [x] if map does not have 'P'
- [x] if map does not have 'C'
- [x] if map does not have 'E'
- [x] if map has more than one 'P'
- [x] if map has more than one 'E'
- [x] path: exit not accessible
- [x] path: exit LEAKS
- [x] path: collectible(s) is/are not accessible
- [x] path: collectibles(s) LEAKS
- [x] path: player is locked
- [x] path: player LEAKS
- [x] if map is surrounded by walls
- [x] if map is not square
- [x] if map's lines are all same length 

TEST [BONUS]
- [ ] if file does not exist
- [ ] if file does not have .ber extension
- [ ] if file is empty
- [ ] if map is too small (at least > 3 in width or length so the map can be surrounded by '1's)
- [ ] if map does not have 'P'
- [ ] if map does not have 'C'
- [ ] if map does not have 'E'
- [ ] if map has more than one 'P'
- [ ] if map has more than one 'E'
- [ ] path: exit not accessible
- [ ] path: exit LEAKS
- [ ] path: collectible(s) is/are not accessible
- [ ] path: collectibles(s) LEAKS
- [ ] path: player is locked
- [ ] path: player LEAKS
- [ ] if map is surrounded by walls
- [ ] if map is not square
- [ ] if map's lines are all same length 

ALL
- [X] missing!:!:!:! path check OMGOMG
- [X] structure in files
- [X] put order to bonus (&genenerator) && no bonus functions (-lz)

MANDATORY
- [x] basic execution leaks
- [x] C_PAUSE && bonus keys count as n_moves++

BONUS
- [ ] add enemies
- [ ] add "sprite animation"
- [ ] add *cool* end()

BOTH
- [x] in ft_ismovekey, LEAKS
- [x] load_game (when exit circumstantially), LEAKS

GENERATOR
- [ ] ~~add empty/random character option(key X, for example)~~
- [x] (argc == 2): if file does not exist or is empty, generate map
- [ ] generate random map option
- [x] write_empty_map() is FFFFFFF empty :(
- [x] position (player) should be displayed at window launch, not after first movement. 