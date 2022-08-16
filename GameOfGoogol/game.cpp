#include <iostream>
#include<vector>
#include<ctime>

using namespace std;

#define u32 unsigned int



void SetDeck(u32 size, vector<int>* deck, vector<int>::iterator iter);

int main()
{
	srand(time(0));

	u32 deck_size;
	vector<int> deck;
	vector<int>::iterator iter;
	

	cout << "Welcome to the game of googol! Please enter a deck size between 1 and 100. \n\n";
	cin >> deck_size;

	while (deck_size > 100 || deck_size < 1)
	{
		cout << "Invalid input, please try again. Enter a deck size between 1 and 100.\n\n";
		deck_size = 0;
		cin >> deck_size;
	}

	SetDeck(deck_size, &deck, iter);

	bool gameover = false;
	u32 hits = 0;
	u32 highcard = 0;
	u32 guess = 0;
	iter = deck.begin();
	while (!gameover)
	{
		
		cout << endl << endl << endl << endl;
		cout << " Cards in deck: " << deck.size() - hits;
		cout << "\n\n Cards burned: " << hits;

		if (hits > 0)
		{
			iter = deck.begin() + (hits - 1);
			if (*iter > highcard)
				highcard = *iter;
		}

		cout << "\n\n Highest Card Burned: " << highcard;

		if (hits > 0)
			cout << "\n\n Top Card of the Deck: " << *(iter + 1);
		else cout << "\n\n Top Card of the Deck: " << *iter;

		bool decided = false;
		while (!decided)
		{
			cout << "\n\n\n Would you like to BURN or STOP?" << endl << endl;
			string action;
			cin >> action;

			if (action == "BURN" || action == "burn")
			{
				cout << "\n\n Burning top Card...";
				if (hits < deck_size - 1)
					hits++;
				else
				{
					cout << "\n\n No more cards left in the deck! Selecting the final number, " << *(iter + 1) <<  ", as your guess...";
					guess = *(iter + 1);
				}
				decided = true;
			}
			else if (action == "STOP" || action == "stop")
			{
				if (hits == 0)
					guess = *iter;
				else 
					guess = *(iter + 1);

				if (hits == 0)
					cout << "\n\n You've selected number " << *iter << " as your guess...";
				else
					cout << "\n\n You've selected number " << *(iter + 1) << " as your guess...";
				decided = true;
			}
			else
				cout << "\n\n Invalid respone. Try to use either all or no caps when you respond.";
		}

		cout << endl << endl;
		if (guess != 0)
		{
			gameover = true;

			bool win = true;
			for (iter = deck.begin(); iter != deck.end(); ++iter)
			{
				if (guess < *iter)
				{
					win = false;
					guess = *iter;
				}
			}
			if (win)
				cout << "\n\n You WIN! " << guess << " was the highest number in the deck!";
			else
				cout << "\n\n You LOSE... " << guess << " was the highest number in the deck!";

			char again;
			cout << "\n\n Would you like to play again? [y]es [n]o ";
			cin >> again;

			while (again != 'y' && again != 'n')
			{
				cout << "\n\n Invalid input, please try again. Enter a deck size between 1 and 100.\n\n";
				again = 'e';
				cin >> again;
			}

			if (again == 'y')
			{
				guess = 0;
				hits = 0;
				highcard = 0;
				deck.clear();

				cout << "\nPlease enter a deck size between 1 and 100. \n\n";
					cin >> deck_size;

				while (deck_size > 100 || deck_size < 1)
				{
					cout << "Invalid input, please try again. Enter a deck size between 1 and 100.\n\n";
					deck_size = 0;
					cin >> deck_size;
				}

				srand(time(0));
				SetDeck(deck_size, &deck, iter);
				iter = deck.begin();
				gameover = false;
			}
			else
				cout << "\n\n Thanks for playing! Press Any button to close the app.";	
		}
	}

	

		
		

}

void SetDeck(u32 size, vector<int>* deck, vector<int>::iterator iter)
{
	cout << "Setting Deck size...";

	for (u32 i = 0; i < size; i++)
	{
		u32 n = rand() % 10000;
		
		bool unique = true;
		for (iter = deck->begin(); iter != deck->end(); ++iter)
		{
			if (n == *iter)
				unique = false;
		}
		
		if (unique)
			deck->push_back(n);
		else
			i--;
	}

	cout << "\n\nDeck is Ready!";
}
