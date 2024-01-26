// for the application
#include <iostream>
#include <string>
#include <conio.h>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
// just for the loading screen
#include <unistd.h>
#include <chrono>
#include <thread>
#include <math.h>


using namespace std;

void loading1(vector<string> words){
    for(int i=1;i<=1000;i++){
        system("cls");
        char loadingBar[53] = "[                                                  ]";
        cout << "\n\n\t\t           - - - Initialization Sequence - - - " << endl << "\t\t\t      Importing Valid Words: " << words[int(i*(float((size(words)-1))/1000))] << endl;
        // we are indexing words using i times a scaler value derived from the size of words. This way, the user sees all the words as the loading sceen loads!! so cool!
        cout<<"\n\t\t\t\t        Loading "<<'\n'<<'\t'<<'\t';
        int j = 1;
        while(j<=i){
            if(j%20==0)
                loadingBar[j/20] = '|';
            j++;
        }
        cout << loadingBar;
        cout<<" "<<i/10<<"%";
        if( i > 0 && i < 190)
            cout<<"\n\n\tFinding all of the 4 letter words on the internet... ";
        else if( i >= 190 && i<280)
            cout<<"\n\n\tWAIT. Bad idea, bad idea... ";
        else if(i >=280 && i<500)
            cout<<"\n\n\tNow, finding all of the 5 letter words on the internet... ";
        else if(i >=500 && i<760)
            cout<<"\n\n\tGetting rid of most of the bad words... ";
        else if(i >=760 && i<850)
            cout<<"\n\n\tTidying things up... ";
        else if(i >=850 && i<1000)
            cout<<"\n\n\tAlmost there... ";
        else
            cout<<"\n\n\tComplete. Press Enter to Continue ";
        this_thread::sleep_for(std::chrono::microseconds(8500 - int(360*std::sqrt(i) - 4*i) ));
        // this ridiculous line scales the loading time with a function, so it loads at a cool non-linear rate.
    }
    getch();
    system("cls");
}

void loading2(vector<string> words){
    for(int i=1;i<=1000;i++){
        system("cls");
        cout << "\n\n\t\t           - - - Initialization Sequence - - - " << endl << "\t\t\t      Importing Valid Words: " << words[int(i*(float((size(words)-1))/1000))] << endl;
        // we are indexing words using i times a scaler value derived from the size of words. This way, the user sees all the words as the loading sceen loads!! so cool!
        cout<<"\n\t\t\t\t        Loading "<<'\n'<<'\t'<<'\t';
        int j = 1;
        while(j<=i){
            if(j%20==0)
                cout << '|';
            j++;
        }
        cout<<" "<<i/10<<"%";
        if( i > 0 && i < 190)
            cout<<"\n\n\tFinding all of the 4 letter words on the internet... ";
        else if( i >= 190 && i<280)
            cout<<"\n\n\tWAIT. Bad idea, bad idea... ";
        else if(i >=280 && i<500)
            cout<<"\n\n\tNow, finding all of the 5 letter words on the internet... ";
        else if(i >=500 && i<760)
            cout<<"\n\n\tGetting rid of most of the bad words... ";
        else if(i >=760 && i<850)
            cout<<"\n\n\tTidying things up... ";
        else if(i >=850 && i<1000)
            cout<<"\n\n\tAlmost there... ";
        else
            cout<<"\n\n\tComplete. Press Enter to Continue ";
        this_thread::sleep_for(std::chrono::microseconds(8500 - int(360*std::sqrt(i)- 4*i) ));
        // this ridiculous line scales the loading time with a function, so it loads at a cool non-linear rate.
    }
    getch();
    system("cls");
}

vector<string> read_file(const string& filename){
    ifstream inputFile(filename);
    if(!inputFile.is_open())
        throw runtime_error("File Not Found!");

    vector<string> myWords;
    string line;
    int i=0;
    while(getline(inputFile, line, inputFile.widen('\n'))){
        string m(line);
        myWords.push_back(m);
        i++;
    }
    return myWords;
}

bool invalidCharacters(string word){
    for(int i{};  i<5; i++){
        if(word[i] < int('a') || word[i] > int('z'))
            return true;
    }
    return false;
}

int binarySearch(vector<string> validWords, string theWord){

    unsigned int n = size(validWords);
    unsigned int l = 0;
    unsigned int r = n - 1;
    // Loop to implement Binary Search
    while (l <= r) {
        // Calculating mid
        int m = l + (r - l) / 2;
        // Some random value assigned
        // as 0 belongs to index
        int res = -1000;
        if (theWord == (validWords[m]))
            res = 0;
        // Check if x is present at mid
        if (res == 0)
            return m;
        // If x greater, ignore left half
        if (theWord > (validWords[m]))
            l = m + 1;
            // If x is smaller, ignore right half
        else
            r = m - 1;
    }
    return -1; // return -1 if the word is not in the list
}

int main() {

    int guesses = 0, wordChoice;
    string guess, theWord, theHint;
    char playAgain, gameMode;
    bool guessIsWrong = true;
    vector<string> validWords;
    vector<char> invalidLetters = {};

    validWords = read_file("5_letter_wordle_words.txt");
    sort(validWords.begin(), validWords.end());

    //  the loading sequences

    loading1(validWords);
    //loading2(validWords);

    AGAIN:
    cout << "\n\nOne Player or Two Player? (Enter 1 or 2): ";
    cin >> gameMode;
    while (gameMode != '1' && gameMode != '2') {
        cout << "\nIncorrect input. Please try again. \nOne Player or Two Player? (Enter 1 or 2): ";
        cin >> gameMode;
    }
    if(gameMode == '2') {
        RETRY:
        cout << "\n\nEnter a five letter word for your friend to guess. Make sure it is 5 letters..." << endl;
        cin >> theWord;
        while (theWord.length() != 5) {
            cout << "Sorry, your word must only have 5 letters. Try again, please." << endl;
            cin >> theWord;
        }
        transform(theWord.begin(), theWord.end(), theWord.begin(), ::tolower);

        auto it = binarySearch(validWords, theWord);
        char retry = 'n';
        while(it == -1 || retry != 'n'){
            cout << "Your word is not in our library of 5 letter words. If you are sure you spelled it correctly, enter 'y'. \nOtherwise, enter 'n' to reenter your word. ";
            cin >> retry;
            if(retry == 'n')
                goto RETRY;
        }
        // this is where they enter a hint for their friend
        cout << "Enter a hint for your friend:" << endl;
        cin.ignore();
        getline(cin, theHint);
        cout << endl;
        cout << "Your word and hint have been accepted and you may press enter to move onto the next stage: guessing. \nPress ENTER. ";
        getch();
        system("cls");
    }
    else{
        // this picks a random word from the library for the single player mode
        srand(time(NULL));
        wordChoice = rand()%(size(validWords)-1);
        theWord = validWords[wordChoice];
    }

    // GUESSING USER INSTRUCTION
    cout << endl;
    cout << "Welcome to Wordle! The word of the day is always 5 letters long." << endl;
    cout << "The following characters describe the validity of your answers based upon their placement in your word guess: " << endl << endl;
    cout << "\t'*' means that letter is correct and in the right spot. \n\t'#' means that letter is in the word but in the wrong spot. \n\t'-' means that letter is not in the word.\n" << endl;
    cout << "If you are not notified that your word is correct (and all of your letters indicators aren't stars), then guess again!" << endl;
    cout << R"(Type "hint" for a hint if you are in Two Player Mode and type "quit" to quit.)" << endl << endl; // the R allows for quotations inside quotations
    cout << "You get 6 guesses. Guess the word of the day: " << endl;

    // GUESS EVALUATION
    do {
        vector<string> theGuesses;
        cin >> guess;
        transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

        // guess fits parameters, y/n
        while (guess.length() != 5 && guess.compare("hint") != 0 && guess.compare("quit") != 0) {
            cout << "Sorry, your guess must have 5 letters. Guess again, please." << endl;
            cin >> guess;
        }
        // quit or hint
        if (guess.compare("hint") == 0) {
            if(gameMode == '2')
                cout << endl << "Hint: " << theHint << endl << endl;
            else
                cout << "Remember, this is Single Player Mode where there are no hints. Guess again!\n";
            continue;
        }
        if (guess.compare("quit") == 0)
            break;
        while(invalidCharacters(guess)){
            cout << "Sorry, your guess can only have letters. Guess again, please." << endl;
            cin >> guess;
        }
        while(binarySearch(validWords, guess) == -1 && gameMode == '1'){
            cout << "Your word is not in our library of 5 letter words.\nPlease re-enter your guess: ";
            cin.ignore();
            cin >> guess;
        }

        if(guesses>0){ // check if guessed before
            bool is_equal = false;
            do{
                for(int i=0; i<theGuesses.size(); i++){
                    if (guess.size() == theGuesses[i].size())
                        is_equal = equal(guess.begin(), guess.end(), theGuesses[i].begin());
                    if(is_equal){
                        cout << "You have entered a previous guess. Please try again: " << endl;
                        cin >> guess;
                        break;
                    }
                }
            }while(is_equal);
        }
        theGuesses.push_back(guess);

        int letters[5][2];

        // checking for duplicate letters for counting purposes
        for (int i = 0; i < 5; i++) {
            letters[i][0] = int(uint8_t(theWord[i]));
            letters[i][1] = 0;
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (letters[i][0] == letters[j][0])
                    letters[i][1]++;
            }
        }

        // BEGIN WORD CHECK
        int lettersRight = 0;
        int letterRightness[5] = {0, 0, 0, 0, 0}; // 0 means that the letter is not present in the word
        for (int i = 0; i < 5; i++) { // checking for right letter, right spot
            if (int(guess[i]) == letters[i][0]) {
                letterRightness[i] = 2;
                for (int j = 0; j < 5; j++) {
                    if (letters[j][0] == letters[i][0])
                        letters[j][1]--;
                }
                continue;
            }
        }

        for (int i = 0; i < 5; i++) { // checking for right letter, wrong spot
            for (int j = 0; j < 5; j++) {
                if (int(guess[i]) == letters[j][0] && letters[j][1] != 0 && letterRightness[i] != 2) {
                    letterRightness[i] = 1;
                    for (int k = 0; k < 5; k++) {
                        if (letters[k][0] == letters[j][0])
                            letters[k][1]--;
                    }
                }
            }
        }
        bool allLettersRight = true;
        // this section adds the invalid letters, sorts the list, then removes duplicates!
        for(int i{}; i<5; i++){
            if(letterRightness[i] == 0) {
                invalidLetters.push_back(guess[i]);
                allLettersRight = false;
            }
        }
        sort(invalidLetters.begin(), invalidLetters.end());
        int i=0;
        while(!allLettersRight && i<(size(invalidLetters)-1)){
            if(invalidLetters[i] == invalidLetters[i+1])
                invalidLetters.erase(next(invalidLetters.begin(), i+1));
            else
                i++;
        }

        if (guess.compare("hint") != 0) { // we won't count hints against you...
            guesses++;
        }

        for (int i = 0; i < 5; i++)
            cout << guess[i] << " ";
        cout << "\t  Guess #" << guesses << "\t  Letters not included: ";
        if(allLettersRight)
            cout << "N/A ... that's crazy bro";
        else {
            for (int i{}; i < size(invalidLetters); i++)
                cout << invalidLetters[i] << " ";
        }
        cout << endl;

        // PRINTING TO SCREEN THE LETTER VALIDATION/REJECTION
        for (int i = 0; i < 5; i++) {
            if (letterRightness[i] == 2)
                cout << '*' << " ";
            else if (letterRightness[i] == 1)
                cout << '#' << " ";
            else
                cout << "-" << " ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++) { // checking to see if the guesser has 5 correct letters
            if (letterRightness[i] == 2)
                lettersRight++;
        }
        if (lettersRight == 5)
            guessIsWrong = false;
    } while (guessIsWrong && guesses < 6);

    if (guessIsWrong)
        cout << endl << "So sorry... you have not won the Wordle. The correct word was: " << theWord;
    else if (guesses == 1)
        cout << endl << "CONGRATS! You won the Wordle FIRST TRY. Cheater.";
    else if (guesses == 2)
        cout << endl << "Congrats! You won the Wordle in TWO guesses! That's impressive.";
    else
        cout << endl << "Congrats! You won the Wordle and it only took you " << guesses << " guesses! So cool.";
    cout << endl;

    cout << "If this word was inappropriate or should not be included in our word bank for other reasons, enter the letter 'Y'. Otherwise, enter 'N'.\n";
    cin >> playAgain;
    if((playAgain == 'Y' || playAgain == 'y') && gameMode == '1') {
        validWords.erase(next(validWords.begin(), wordChoice));
        ofstream nFile("5_letter_wordle_words.txt");
        int n = 0;
        while (n < size(validWords)) {
            nFile << validWords[n] << endl;
            n++;
        }
        nFile.close();
    }
    cout << "Would you like to play again? Y/N" << endl;
    cin.ignore();
    cin >> playAgain;
    if (playAgain == 'Y' || playAgain == 'y'){
        guessIsWrong = true;
        guesses = 0;
        invalidLetters.clear();
        goto AGAIN;
    }
    else
        cout << "Bye, Bye!";

    cout << endl << endl;
    return 0;
}
