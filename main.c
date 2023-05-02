 
bool isValidChar(char c){
    return (c>='a' && c<='z')||(c>='A'&& c<='Z');
}

void print_asterisks(char now_guess[], const char *word, char input, int n){
    for (int i = 0; i < n; ++i){
            if((now_guess[i] == '*' && word[i] == input)||word[i] == toupper(input)){
                now_guess[i] = word[i];
            }
        }
    printf("%s\n",now_guess);
}

bool char_in_string(char c, char* str) {
    int length = strlen(str);
    for (int i = 0; i < length; i++){ 
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}

bool playgame(bool endgame, int max_words){
    while(!endgame){
        int strike = 0;
        int n;
        printf(enter_game_number, max_words);
        while (scanf("%d", &n) != 1 || n > max_words || n < 1) {
            //show an erro messege.
            printf("%s",invalid_game_number);
            //ask again for a valid number
            printf(enter_game_number, max_words);
            
        }
        const char *word = get_word(n);
        n = strlen(word);
        char *lower_word = malloc((n+1) * sizeof(char));//** 修改
        for(int i = 0; i<strlen(word); i++){
           lower_word[i] = tolower(word[i]);
        }
        lower_word[n] = '\0'; 
        
        print_hangman(strike);
        //prompt the user to enter a letter and a series of asterisk per letter
        // in the word, or phrase we are trying to guess.
        
        char *guessed = malloc(sizeof(char));
        guessed[0] = '\0';
        char *now_guess = malloc((n+1) * sizeof(char));
        now_guess[n] = '\0';
        for(int i = 0; i < n; i++){
                if(isValidChar(word[i])){
                    now_guess[i] = '*';
                }
                else{
                    now_guess[i] = word[i];
                }
            }
        printf("%s\n",now_guess);

        while(strike < max_strikes&&!endgame){
            printf("%s",letter_prompt);
            char input;
            while (scanf("%c", &input) != 1 || !isValidChar(input)|| char_in_string(tolower(input), guessed)) {
                //show an error messege.
                if(!isValidChar(input)){
                    printf(not_a_letter, input);
                }
                else if(char_in_string(tolower(input), guessed)){
                    printf(already_guessed_letter, input);
                }
                //ask again for a valid number
                printf("%s",letter_prompt);
            }
            input = tolower(input);
            int guesslen = strlen(guessed);    
            guessed = realloc(guessed, (guesslen + 2) * sizeof(char)); 
            sizeof(char);
            guessed[guesslen] = input; 
            guessed[guesslen+1] = '\0';

            if(char_in_string(input, lower_word)){             
                print_asterisks(now_guess, word, input, n);
                print_hangman(strike);
                if(strcmp(now_guess, word) == 0){
                    endgame = true;
                    printf(congratulations, word);
                }
            }
            else{
                printf(not_in_word, toupper(input));
                strike++;
                printf(not_last_guess, max_strikes-strike);
                print_hangman(strike);
                if(strike == max_strikes){
                    endgame = true;
                    printf(game_over, word);
                }
            }   
        }
        //play again? 
        if(endgame){
            printf("%s",play_again);
            char play;
            while (scanf(" %c", &play) != 1 || (play!='Y' && play!='N')) {
                printf("%c", play);
                //show an erro messege.
                printf("%s",invalid_play_again_response);
                //ask again for a valid number
                printf("%s",play_again);
            }
            if(play == 'Y'){
                endgame = false;
            }
            else{
                endgame = true;
            }
        }
        free(guessed); 
        free(now_guess); 
        free(lower_word);   
    }
    
    return endgame;
}

int main(void) {
    //prompt the use to enter a number N from 1 to max_word
    bool endgame = false;
    while(!endgame){
        endgame = playgame(endgame, max_words);
    }
    printf("End Game.\n");
    return 0;
}
