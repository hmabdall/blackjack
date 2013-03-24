#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <stdio.h> 

using namespace std;

void create_a_border();
void clear_screen();
void fill_screen(int,int);
void gotoxy(int,int);
void graphical_arrangement();
void SetColorAndBackground(int, int);
void deal_two_cards(int);
void print_player_cards(int,int);
void print_player_cards_for_update(int,int,int[]);
void print_player_total(int,int,int[]);
void hit_another_card(int[],int);
void update_player_totals(int&,int,int,int[]);
void print_player_titles(string[]);
void print_column_separators();
void print_setup_screen_menu();
void exit_screen(int);

int main()
{
     // set var names play_again for controlling game restart
     // (user will be prompted to play again at end of game)
     char play_again = false;
     int times_played = 1;
     
     // begin the loop of "playing the game" - the code in this loop
     // will be executed at least once, and further execution will be 
     // determined by user input to continue/end the game
     do{   
           // create array of 7 player names (these will be used in the 
           // condition the user selects to not enter names manually
           string player_names[7] = {"Steven","Caleb","Jacob","Stephanie",
                                  "Ashley","Mario","Kathryn"};
           
           // create an array of 7 elements to contain the data (in forms of 
           // strings) of whether or not a player wins or loses                          
           string win_or_lose[7];
           
           // initialize the array with all players losing
           for (int i = 0; i < 7; i++)
               win_or_lose[i] = "LOSE";
               
           // create array of 7 player IDs for players 1-7. The indices of 
           // these players will be use for various assigning purposes
           // throughout the program 
           int playerID[7] = {1,2,3,4,5,6,7};
    
           // call function to fill the screen (color it's 
           // background, foreground)
           fill_screen(100,10);
        
           // call function to print the blackjack setup screen menu
           print_setup_screen_menu();
        
           // declare and initialize a var called "auto_assign" which may be
           // adjusted per user input and reflects whether or not the user
           // elects enter the names himself
           int auto_assign = 0;
           
           // store user input as answer to question (the question is asked 
           // in the print_setup_screen_menu() function)
           cin >> auto_assign;
           
           // move cursor to appropriate coordinates on console display 
           // to begin printing player names
           gotoxy(0,8);
           
           // if the user elects to enter player names, the appropriate code
           // to carry out the input and storage will be executed in this
           // if bracket
           if (auto_assign == 0)
           {
              // store input for 7 names
              for (int i = 0; i < 7; i++)
              {
                  // move cursor to appropriate coordinates
                  gotoxy(15,10+i);
                  // prompt user to input the name
                  cout << "Player" << playerID[i] << " : ";
                  // store name in array at appropriate index
                  cin >> player_names[i];
        
                  // truncate the inputted names to 7 characters if any exceed
                  // 7 characters; the graphical arrangements of the screen
                  // in this program is optimized for 7 character long names
                  if(player_names[i].length() > 7)
                       player_names[i] = player_names[i].substr(0,7);
              }
           }  
           
           // if the user elects to auto-assign player names, the appropriate 
           // to carry out the display of the default player names will be 
           // executed in this if bracket
           else if (auto_assign == 1)
           {
                // display players 1-7 names
                for (int i = 0; i < 7; i++)
                {
                    // move cursor to appropriate coordinates
                    gotoxy(15,10+i);
                    cout << "Player" << playerID[i] << " : ";
                    
                    // truncate the default names to 7 characters if any exceed
                    // 7 characters; the graphical arrangements of the screen
                    // in this program is optimized for 7 character long names
                    if(player_names[i].length() > 7)
                       player_names[i] = player_names[i].substr(0,7);
                    
                    // display the player name
                    cout << player_names[i];
                }
           }
           
           // declare string for calling user to complete setup and continue
           string s1 = "Enter any number to complete setup & continue - ";
           // display the string in a center-aligned fashion on the console
           gotoxy((80-s1.length())/2,23);
           cout << s1;
           
           // declare an int-type var and allow for user input 
           int some_int = 0;
           cin >> some_int;
    
           // call a function to clear the console display of all previous
           // print since now moving on to the playing screen
           clear_screen();
    
           // call function to color the background of the screen as the player
           // proceeds beyond the setup screen and into playing mode
           SetColorAndBackground(100,10);

           // call function to create a border on the console display
           create_a_border();  
    
           // call a function to create graphical arrangement of playing
           // environment
           graphical_arrangement();
    
           // call additional function to create column separators for an
           print_column_separators();
           
           // call a function to display the player names
           print_player_titles(player_names);
    
           // create an array of 7 int values to store the total value of 
           // every player - this will allow for flexible access to the data 
           // as needed throughout the program
           int player_totals[7];
      
           // assign each player two cards from the deck
           int picked[52], cards[52], num = 0;

           srand(time(0));   
    
           // "create" and initialize all 52 cards in deck to their index value
           // and declare each element in the parallel "picked" array as 0,
           // which signifies the cards have not been chosen yet
           for (int i = 0; i < 52;i++)
           {
               cards[i] = i;
               picked[i] = 0;
           }    
           
           // deal two cards to each player
           int total = 0;
           
           // declare and initialize to zero the two variables dealer_total and
           // dealer_first_card so that these can be assigned values which can
           // be used later in the program as needed since the values will be
           // hidden by a "?" on the console
           int dealer_total = 0;
           int dealer_first_card = 0;
           bool repeat_for_dealer = false;
           // begin at the x value i = 9 and move along 9 spaces every time
           // when printing the cards of each player
           for (int i = 9; i < 80 ;i += 9)
           {    
                // repeat the pass out of cards two times
                for (int j = 0; j < 2; j++)
                {
                    gotoxy(i, 7 + j);
                    
                    num = rand()%52;
                
                    // only assign cards who have been marked as non-picked
                    while(picked[num] == 1)
                    {     
                          num = rand()%52;  
                    }   
                    // mark the picked number as picked
                   picked[num] = 1;          
            
                   // call function to print the card on console
                      print_player_cards(num,i);

                   
                   // gives number between 0 -12
                   num %= 13;            
            
                   // adjust J,Q,K as necessary for computational purposes
                   // i.e. J,Q,K == 10           
                   if ((num >= 0) && (num < 10))
                      num++;
                   if ((num == 11) || (num == 12))
                      num = 10;        
                   
                   // store the value of the dealer's first card for use in
                   // later parts of the program
                   if (i == 9 && j == 0)
                   {
                      dealer_first_card = num;
                   }
                   
                   // adjust the total as necessary to reflect each additional number
                   total += num;
                }                
                
                // store the dealer's total in a variable for use in later
                // parts of the program
                if (i == 9)
                   dealer_total = total;           
          
                // call function to print the player's total (combination of
                // two cards on the console display
                print_player_total(total, i, player_totals);
          
                // reset total to 0 between player so that data is surely not
                // recycled
                total = 0;
                
          }
          
          int x = 9;
          int y = 9;
          while (dealer_total < 17)
          {
                gotoxy(x,y);
                num = rand()%52;
                
                    // only assign cards who have been marked as non-picked
                    while(picked[num] == 1)
                    {     
                          num = rand()%52;  
                    }   
                    // mark the picked number as picked
                   picked[num] = 1;          
            
                   // call function to print the card on console
                      print_player_cards(num,9);

                   // gives number between 0 -12
                   num %= 13;            
            
                   // adjust J,Q,K as necessary for computational purposes
                   // i.e. J,Q,K == 10           
                   if ((num >= 0) && (num < 10))
                      num++;
                   if ((num == 11) || (num == 12))
                      num = 10;        

                   // adjust the total as necessary to reflect each additional number
                   dealer_total += num;
                 
                // call function to print the dealer's total (combination of
                // two cards on the console display
                print_player_total(dealer_total, 9, player_totals);
                // increment the y-value in case another card is to be printed
                y++;
          }
          
                
                // hide one of the dealer's cards
                //gotoxy(9,7);
                //cout << " ? ";
                // hide the dealer's total
                //gotoxy(9,18);
                //cout << " ? ";
    
         // prompt each player to hit or run for as many times as long as they
         // are still under 21
         for (int i = 0; i < 7; i++)
         {   
             // declare and initialize this variable which will be responsible
             // for adjusting the y value of each additional card being dealt 
             // and printed to the console. it begins at zero at every time
             // the card is being passed out
             int k = 0;
                          
             // clear up the space on the display where the question will be
             // asked
             gotoxy(1,23);
             for (int j = 1; j < 78;j++)
                 cout << " ";
            
            string s7 = player_names[i]+", would you like to hit (H) or stay (S)? ";
            gotoxy((80-s7.length())/2,23);
            cout << s7;
            char player_decision;
        
            cin >> player_decision;
        
            // pass out a card to the player if he/she elects to hit
            while ((player_decision == 'H' || player_decision == 'h') && (player_totals[i] < 21))
            {
                 gotoxy(18 + 9*i ,9 + k);

                 num = rand()%52;

                      while(picked[num] == 1)
                      {     
                            num = rand()%52;  
                      }   
            
                 picked[num] = 1;          
            
                 // print the card on console
                 print_player_cards_for_update(num,i,player_totals);

                 // gives number between 0 -12
                 num %= 13;            
            
                 // adjust J,Q,K as necessary for computational purposes
                 // i.e. J,Q,K == 10
                 if ((num >= 0) && (num < 10))
                    num++;
                 if ((num == 11) || (num == 12))
                    num = 10;        
            
                  // adjust the total as necessary to reflect each additional number
                  total += num;
                  
                  if((player_totals[i] >= 21 || player_decision == 'S') && (i != 6))
                  {   
                      //i++;
                      k = -1;
                  }  
                  
                  gotoxy(1,23);
                  if (player_totals[i] < 21)
                  {
                     for (int h = 1; h < 78;h++)
                         cout << " ";
                     gotoxy((80-s7.length())/2,23);
                     cout << player_names[i] << ", would you like to hit (H) or stay (S)? ";
                     cin >> player_decision;
                  }
                  
                  k++;                  
            }
            
                  // print_player_total(total, i, player_totals);
                  total = 0;                    
        }
        
        
        // show the dealer's hidden first card
        gotoxy(9,7);
           cout << dealer_first_card << char((dealer_first_card/13)+3);
        
        // show the dealer's hidden total
        gotoxy(10,18);
           cout << dealer_total;
        
        // display whether or not each player wins
        for (int i = 0; i < 7; i++)
        {
            // players win if they remain under 21 and above the dealer total
            // or automatically win if the dealer busts (over 21)
            if (((player_totals[i] > dealer_total) && player_totals[i] <= 21) || (dealer_total > 21))
            {   
                win_or_lose[i] = "WIN!";
                gotoxy(16 + 9*i,20);
                cout << win_or_lose[i];
            }
            
            // otherwise, the players lose
            else if (player_totals[i] < dealer_total)
            {
                 // win_or_lose[] has been initialed to "LOSE"
                gotoxy(16 + 9*i,20);
                cout << win_or_lose[i];
            }
        }
     
        // set the default user choice to 'N'
        char user_choice = 'N';
     
        // clear the area and prompt the user to play again or not
        gotoxy(1,23);
        for(int i = 0; i < 78; i++)
             cout << " ";
        
        // go to the center of the screen, keeping in mind the length of the 
        // message; clear the area again in case anything gets left behind
        string play_again_message = "Would you like to play again (Y/N)?: ";
        gotoxy((80-play_again_message.length())/2,22);
        for (int i = 1; i < 78; i++)
            cout << " ";
            
        // display the message of whether or not to play again
        cout << play_again_message;
        cin >> user_choice;
     
        // change the plag_again condition to true if the player enters Y for 
        // yes and also increment the number of times the player has played 
        // the game
        if (user_choice == 'Y' || user_choice == 'y')
        {   
            play_again = true;
            times_played++;     
        }
        
        // if the player's choice is no, then call the exit screen function
        // and also stop the entire do-while loop so that the player does not
        // play again
        if (user_choice == 'N' || user_choice == 'n')
        {   
            exit_screen(times_played);
            play_again = false;
        }
     
         // dealer keeps taking cards until over 17
}  while(play_again == true);
    
    system("PAUSE");
    return 0;
}


/**This function displays an exit screen on the console if the player
elects to not play again when prompted at the end of the game it is passed
an int value which has stored in it a value reflecting the number of times
the user has played the game*/
void exit_screen(int times_played)
{
     // recolor the console display
     fill_screen(100,10);
     
     // print some strings as messages
     string s1 = "Thank you for playing MetaQuant BlackJack!";
     string s2 = "(COPYLEFT 2178 MetaQuant Software,Inc.)";
     string s3 = "Number of times played: ";
     string s4 = "If you have any comments or suggestions,";
     string s5 = "please direct them to hussein.m.abdallah@gmail.com";
     
     gotoxy((80-s1.length())/2,2);
     cout << s1;
     gotoxy((80-s2.length())/2,3);
     cout << s2;
     gotoxy((80-s3.length())/2,5);
     cout << s3 << times_played;
     gotoxy((80-s4.length())/2,7);
     cout << s4;
     gotoxy((80-s5.length())/2,8);
     cout << s5 << endl << endl << endl << endl << endl << endl;  
}

/**this is a function which prints out various messages and column borders
in the welcome screen*/
void print_setup_screen_menu()
{
     // declare, print some strings
    string line1 = "WELCOME TO MetaQuant BLACKJACK SETUP";
    string line2 = "To input player names, enter 0";
    string line3 = "To auto-assign the player names, enter 1";
    //string line2 = "In the fields below, please enter the";
    string line4 = "(note: entries will be parsed to 7 characters)";
    string line5 = "Enter your choice here: ";

    for (int i = 0; i < 80; i++)
        cout << "-";
    gotoxy((80-line1.length())/2,1);
    cout << line1 << endl << endl;
    gotoxy(0,2);
    for (int i = 0; i < 80; i++)
        cout << "-";
    gotoxy((80-line2.length())/2,3);
    cout << line2 << endl;
    gotoxy((80-line3.length())/2,4);
    cout << line3 << endl;
    gotoxy((80-line4.length())/2,5);
    cout << line4 << endl;
    gotoxy(0,6);
    for (int i = 0; i < 80; i++)
        cout << "-";
    gotoxy((80-line5.length())/2,7);
    cout << line5;
    gotoxy(0,8);
    for (int i = 0; i < 80; i++)
        cout << "-";
    
    for (int k = 8; k < 75; k +=64 )
    {
        // print table columns
        for (int i = 0; i < 25; i++)
        {    
             gotoxy(k,i);
             cout << "|";
        }
    }
    
    gotoxy(((80-line5.length())/2) + line5.length(),7);
    //gotoxy(67,7);   
}

void print_column_separators()
{
     for (int i = 5; i < 80; i +=8)
     {
         for (int j = 3; j < 22; j++)
         {
             gotoxy(i,j);
             cout << "|";
         }
     
         if(i !=5)
              i++;
     }
     
     gotoxy(1,21);
     for (int i = 1; i < 78; i++)
         cout << "-";
}

void print_player_titles(string player_names[])
{
     for (int i = 0,k = 14; i < 7;i++,k += 9)
     {   
         gotoxy(k,3);
         cout << setw(7) << player_names[i];
     }
}

void print_player_total(int total,int i,int player_totals[])
{
     player_totals[(i/9) - 2] = total;
     gotoxy(i,18);
     cout << player_totals[(i/9) - 2];
}

void clear_screen()
{
     for (int i = 0; i < 80; i++)
     {
         for (int j = 0; j < 25; j++)
         {
             gotoxy(i,j);
             cout << " ";
         }
     }
     gotoxy(0,0);
}

void fill_screen(int forg, int backgr)
{
     for (int i = 0; i < 80; i++)
     {
         for (int j = 0; j < 25; j++)
         {
             gotoxy(i,j);
             SetColorAndBackground(forg,backgr);
             cout << " ";
         }
     }
     gotoxy(0,0);
}

void create_a_border()
{
     // print the top border
    for (int i = 0; i < 80; i++)
    {
        cout << "*";
    }
    
    // print the side borders
    for (int i = 0; i < 23; i++)
    {
        cout << "*";
        for (int i = 0; i < 78; i++)
        {
            cout << " ";
        }
        cout << "*";
    }    
    
    // print the lower border
    for (int i = 0; i < 80; i++)
    {
        cout << "*";
    }
}

void update_player_totals(int& i,int num,int original_total,int player_totals[])
{
     player_totals[i] = original_total + num;
     gotoxy(18 + 9*i,18);
     cout << player_totals[i];
     if(player_totals[i] > 21)
     {
        gotoxy(16 + 9*i,19);
        cout << "BUST!";
        i++;
     }
}

void print_player_cards_for_update(int num, int i,int player_totals[])
{
     int num_printing = num;
     num %= 13;
   
     if (num == 0)
     {  
        cout << 'A' << char((num_printing/13)+3);
        update_player_totals(i,1,player_totals[i],player_totals);
     }
     else if ((num > 0) && (num < 10))
     {
        cout << num + 1 << char((num_printing/13)+3);
        update_player_totals(i,num+1,player_totals[i],player_totals);
     }
     else if (num == 10)
     {
        cout << 'J' << char((num_printing/13)+3);
        update_player_totals(i,10,player_totals[i],player_totals);
     }
     else if (num == 11)
     {
        cout << 'Q' << char((num_printing/13)+3);
        update_player_totals(i,10,player_totals[i],player_totals);
     }
     else if (num == 12)
     {
        cout << 'K' << char((num_printing/13)+3);
        update_player_totals(i,10,player_totals[i],player_totals);
     }
}

// num comes in as 0-12
void print_player_cards(int num, int i)
{
     int num_printing = num;
     num %= 13;
   
     if (num == 0)
        cout << 'A';
     else if ((num > 0) && (num < 10))
        cout << num + 1;
     else if (num == 10)
        cout << 'J';
     else if (num == 11)
        cout << 'Q';
     else if (num == 12)
        cout << 'K';
        
     // results in 0/1/ + 3
     cout << char((num_printing/13)+3);
     
     // hide one of the dealer's cards
     // gotoxy(9,7);
        //cout << '?' << " ";
}

void gotoxy(int x, int y) 
{ 
     COORD coord;
     coord.X = x; coord.Y = y; 
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
//http://www.physicsforums.com/showthread.php?t=209526
}

void graphical_arrangement()
{
    
    // print the welcome string
    gotoxy(27,1);
    cout << "Welcome to MetaQuant BlackJack!" << endl;

    gotoxy(1,2);
    for (int i = 0; i <78; i++)
        cout << "-";
    gotoxy(1,5);
    for (int i = 0; i <78; i++)
        cout << "-";

    for (int i = 5, x = 1; i < 70; i += 9, x++)
    {
    
    gotoxy(i,6);
          if (x != 1)
          {
              cout << "Player" << (x-1);
              cout << "    ";
          }  
        else if (x == 1)
        {   
            cout << " Dealer";
            cout << "     ";
        }      
    }
    
    // print each player plus the dealer's line
    for (int i = 5; i < 70; i += 9)
    {
    gotoxy(i,17);
    cout << "_______";
    cout << "    ";
    }
}

//This will set the forground and background color for printing in a console window.
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);     
     return;
}
