#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <vector>
#include <mutex>

using namespace std;

int player_num, round_num, random_num, min_bound, max_bound,winner;
mutex game_mutex;
bool game_status,round_status;

//thread-safe random number generator (from lecture notes)
int random_range(int min, int max)
{
    static mt19937 generator(time(0));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void player_thread(int id, tm *start_time)
{
    //sleep the all threads 3 secs
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(start_time)));
    //thread will work until the end of game
    while (game_status)
    {
        //thread will work until the end of round
        while (round_status)
        {
            //after waiting for 3 secs , get the current time again
            time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            tm *current_time = new tm;
            localtime_r(&tt, current_time);

            //until the end of the round thread will make guess
            int guess = random_range(min_bound, max_bound);

            //here mutex should be locked since after a thread finds correctly others will not continue to guess
            game_mutex.lock();
            if (round_status)
            {
                //printing the required information part
                cout << "Player with id " << id << " guessed " << guess;
                if (guess == random_num)
                {
                    cout << " correctly at: " << put_time(current_time, "%X") << endl;
                    round_status = false;
                    winner = id;
                }
                else
                {
                    cout << " incorrectly at: " << put_time(current_time, "%X") << endl;
                }
            }
            //end of the critic part son I unlocked the mutex
            game_mutex.unlock();
            //at end of the each round , each thread will wait 1 sec
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void host_thread()
{
    //create a score array
    int scores [player_num];

    //get the current time
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm *ptm = new tm;
    localtime_r(&tt, ptm);

    //host_thread will work only for count of round number
    for (int i = 0; i < round_num; ++i)
    {
        //since round is started , set round status to true in each beginning of the round;
        round_status = true;

        //in each round
        tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
        localtime_r(&tt, ptm);

        random_num = random_range(min_bound, max_bound);
        cout << endl << "---------------------------------------------------" << endl;
        //if this is initial round , specific outputs
        if (i == 0)
        {
            cout << "Game started at: " << put_time(ptm, "%X") << endl;
            cout << "Round 1 will start 3 seconds later" << endl;
            ptm->tm_sec += 3;
        }
        //if this is not initial round , specific outputs
        else
        {
            cout << "Round " << i + 1 << " started at: " << put_time(ptm, "%X") << endl;
        }
        cout << "Target is " << random_num << endl << endl;

        //wait for the round being finished
        while (round_status)
        {
            this_thread::sleep_for(chrono::milliseconds (1));
        }
        //increase the winner's score by one
        scores[winner]++;
        winner = -1;
    }
    //game ends since all raunds are over
    //set the game status to false and print the leaderboard
    game_status = false;
    cout << endl << "Game is over!" << endl;
    cout << "Leaderboard:" << endl;
    for (int j = 0; j < player_num; ++j)
    {
        cout << "Player " << j << " has won " << scores[j] << " times" << endl;
    }
}

int main()
{
    //input check part starts **
    do
    {
        cout << "Please enter number of players" << endl;
        cin >> player_num;
    } while (player_num < 1);

    do
    {
        cout << "Please enter number of rounds" << endl;
        cin >> round_num;
    } while (round_num < 1);

    do
    {
        cout << "Please enter the randomization range" << endl;
        cin >> min_bound >> max_bound;
    } while (min_bound > max_bound);
    //input check part ends **

    //take the curren time
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm *start_time = new tm;
    localtime_r(&tt, start_time);
    //add 3 seconds to the current time , this is for each threand to start together and 3 sec later from current time
    start_time->tm_sec += 3;

    //set game status to true
    game_status = true;

    //thread initialization part starts **
    thread threads[player_num];
    for (int j = 0; j < player_num; ++j)
    {
        threads[j] = thread(&player_thread, j, start_time);
    }
    thread host = thread(&host_thread);
    //thread initialization part ends **

    //join all threads if they are joinable **
    for (int j = 0; j < player_num; ++j)
    {
        if (threads[j].joinable())
        {
            threads[j].join();
        }
    }

    if (host.joinable())
    {
        host.join();
    }
    //thread join ends **

    return 0;
}
