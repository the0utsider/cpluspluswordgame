#include "FKelimeOyunu.h"
#include <map>
#include <vector>
#include <time.h>
#define TMap std::map

FKelimeOyunu::FKelimeOyunu()  // runtime values (defaults)
{
	Reset();
}

int32 FKelimeOyunu::GetCurrentTry() const { return MyCurrentTry; }
int32 FKelimeOyunu::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FKelimeOyunu::IsGameWon() const { return bGameIsWon; }


int32 FKelimeOyunu::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {4, 6}, { 5, 8 }, { 6, 10 },{ 7, 12 }, { 8, 14 },{ 9, 18 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FKelimeOyunu::Reset()
{
	FKelimeOyunu::GetMaxTries();
	const FString HIDDEN_WORD = SelectIsogram();
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FKelimeOyunu::CheckGuessValidity(FString Guess) const 
{
	if (!bIsIsogram(Guess)) // if the guess isnt an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!bIsLowercase(Guess)) // if the guess isnt all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length() )	// if the guess length is  wrong
	{ 
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//recieves a valid guess, increases try number returns count
FBullCowCount FKelimeOyunu::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	//setup a return value
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same len

	//loop through all the letters in the hidden word

	for (int32 MyHWChar = 0; MyHWChar < WordLength; MyHWChar++)
	{
		//compare letters against the guess
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++)
		{
			//if they match then
			if (Guess[GuessChar] == MyHiddenWord[MyHWChar])
			{
				if (MyHWChar == GuessChar)
				{
					BullCowCount.Bulls++; //increase bulls for same place
				}
				else
				{
					BullCowCount.Cows++; //increase cows if they are not
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{ 
		bGameIsWon = true; 
	}
	if (BullCowCount.Bulls != WordLength)
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FKelimeOyunu::bIsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}


bool FKelimeOyunu::bIsIsogram(FString Word) const
{	
	// treat 0 and 1 letter words as isogram
	if (Word.length() < 2) { return true; }

	TMap<char, bool> LetterSeen;	// setting up the map
	for (auto Letter : Word)		// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixedcAsE
		if (LetterSeen[Letter]) {	//if letter is in the map
			return false;		// we dont have an isogram
		} else {
			LetterSeen[Letter] = true;	//add the letter to the map as seen
		}
	}
	return true;		//for in cases  where /0 is entered 
}

FString FKelimeOyunu::SelectIsogram()
{
	std::vector<FString> Dictionary = {
		"burek", "pita", "kebap", "lehmacun", "doner", "chermoula", "khobz", "shebaki"
	};
	int32 iNumberOfIsograms = size(Dictionary);

	// ----- validate dictionary ONCE ONLY ----- //
	// this is somewhat anachronistic, as now the secret word is validated immediately prior to use (as well)
	// but there's no harm keeping it for extra data, i.e. in a case where new words are added to the dictionary...
	// in one run of the program they will all be immediately flagged on the console.

	FString sSelection;
	int32 iSelection;

	srand(unsigned(time(NULL)));
	iSelection = rand() % iNumberOfIsograms;
	sSelection = Dictionary[iSelection];

	// TODO word-length discrimination, leading to:
	// TODO challenege-level system...
	return sSelection; // Break and watch here to cheat
}


