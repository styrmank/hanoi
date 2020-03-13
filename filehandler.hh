/*
 *   COURSE: Ohjelmointi 2
 *   ASSIGNMENT: Final project
 *   MODULE: FileHandler
 *   AUTHOR: Kasper Styrman, student# 284971
 *
 *   File handler class used for reading from and writing to files.
 *   The class' main responsibility is fetching and updating the
 *   high score file if needed.
*/

#ifndef FILEHANDLER_HH
#define FILEHANDLER_HH


#include <string>
#include <fstream>

// default filenames
std::string const HIGH_SCORES_FILENAME = "highscores.txt";
std::string const INSTRUCTIONS_FILENAME = "instructions.txt";

// strings used if files are empty/can't be read
std::string const NO_HIGH_SCORE = "No previous highscore.";
std::string const NO_INSTRUCTIONS = "Instructions missing.";


// enum used in selecting way to read file
enum mode{highscore,instruction};

class FileHandler
{
public:

    // Construct an instance of filehandler.
    FileHandler();

    /* Read file and return contents in a string.
     * param - filename (string) : name of file to be read.
     * param - mode (int) : declares if reading high score or instructions.
     * param - inseconds (bool) : should data be fetched without formatting
     * return - (string) : file contents returned in a string.
     * default texts are the NO_... strings declared above.
     * */
    std::string readFile(const std::string filename,
                         int mode,
                         bool inseconds = false);

    /* Compare time score for this game. If it's smaller, it's saved
     * as a new high score (seconds) in the default high score file.
     * param - time (int) : time score for this game.
      */
    void saveHighScore(int const &time);
};

#endif // FILEHANDLER_HH
