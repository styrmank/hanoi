#include "filehandler.hh"

FileHandler::FileHandler()
{

}

std::string FileHandler::readFile(std::string const filename,
                                  int mode,
                                  bool inseconds)
{
    std::string text = "";
    std::string line = "";
    std::ifstream file;
    file.open(filename);

    if(file.is_open())
    {
        if(mode == instruction)
        {
            while(std::getline(file,line))
            {
                text += line + '\n';
            }
            return text;
        }
        // case of getting previous high score
        else
        {
            std::getline(file,line);
            text = line;
        }
        if(text.empty())
        {
            text = NO_HIGH_SCORE;
        }
        else if(!inseconds)
        {
            // formatting previous high score to readable form.
            int time = std::stoi(text);
            int hours = time/3600;
            int minutes = (time-3600*hours)/60;
            int seconds = time%60;
            text = std::to_string(hours) + "hh "
                 + std::to_string(minutes) + "mm "
                 + std::to_string(seconds) + "s.";
        }
    }
    // case file couldn't be opened.
    else
    {
        text = (mode == highscore) ? NO_HIGH_SCORE : NO_INSTRUCTIONS;
    }
    file.close();

    return text;
}

void FileHandler::saveHighScore(const int &time)
{
    std::string previous_highscore = readFile(HIGH_SCORES_FILENAME,
                                              highscore,
                                              true);
    std::ofstream file;
    // case no previous or a smaller score
    if(previous_highscore == NO_HIGH_SCORE ||
       std::stoi(previous_highscore)> time)
    {
       file.open(HIGH_SCORES_FILENAME);
       file << time;
    }
    file.close();
}
