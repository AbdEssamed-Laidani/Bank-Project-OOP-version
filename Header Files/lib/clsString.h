#pragma once
#include <iostream>
#include <vector>
#include <string>


class clsString
{
private:
	std::string _Value;
	static bool IsVowel(char Letter)
	{
		Letter = tolower(Letter);
		return (Letter == 'a' || Letter == 'i' || Letter == 'e' || Letter == 'u' || Letter == 'o');
	}

public:

	clsString()
	{
		_Value = "";
	}
	clsString(std::string Value)
	{
		_Value = Value;
	}

	void setValue(std::string Value)
	{
		_Value = Value;
	}
	std::string GetValue()
	{
		return _Value;
	}

	static std::string UpperFirstLetterOfEachWord(const std::string &text)
	{
		bool isFirstLetter = true;
		std::string S1 = text;
		for (int i = 0; i < (int)S1.size(); i++)
		{
			if (S1.at(i) != ' ' && isFirstLetter)
			{
				S1.at(i) = toupper(S1.at(i));
			}
			isFirstLetter = (S1.at(i) == ' ') ? true : false;
		}
		return S1;
	}
	std::string UpperFirstLetterOfEachWord()
	{
		return UpperFirstLetterOfEachWord(_Value);
	}

	static std::string UpperAllLetterOfString(const std::string& text)
	{
		std::string S1 = text;
		for (int i = 0; i < (int)S1.size(); i++)
		{
			S1.at(i) = toupper(S1.at(i));
		}
		return S1;
	}
	std::string UpperAllLetterOfString()
	{
		return UpperAllLetterOfString(_Value);
	}

	static std::string LowerAllLetterOfString(const std::string& text)
	{
		std::string S1 = text;
		for (int i = 0; i < (int)S1.size(); i++)
		{
			S1.at(i) = tolower(S1.at(i));
		}
		return S1;
	}
	std::string LowerAllLetterOfString()
	{
		return LowerAllLetterOfString(_Value);
	}

	static int CountSmallLetterInString(const std::string& text)
	{
		int counter = 0;
		for (int i = 0; i < text.size(); i++)
		{
			if (islower(text.at(i)))
				counter++;
		}
		return counter;
	}
	int CountSmallLetterInString()
	{
		return CountSmallLetterInString(_Value);
	}

	static int CountCapitalLetterInString(const std::string& text)
	{
		int counter = 0;

		for (int i = 0; i < text.size(); i++)
		{
			if (isupper(text.at(i)))
				counter++;
		}

		return counter;
	}
	int CountCapitalLetterInString()
	{
		return CountCapitalLetterInString(_Value);
	}

	static int CountLetterInString(const std::string& text)
	{
		int counter = 0;



		for (int i = 0; i < text.size(); i++)
		{

			if (!isdigit(text.at(i)) && !ispunct(text.at(i)) && !isspace(text.at(i)))
				counter++;
		}
		return counter;
	}

	int CountLetterInString()
	{
		return CountLetterInString(_Value);
	}

	static int CountSpecificLetterInString(const std::string& text, char Target)
	{
		int counter = 0;

		for (int i = 0; i < text.size(); i++)
		{
			if (toupper(text.at(i)) == toupper(Target))
				counter++;
		}

		return counter;
	}

	int CountSpecificLetterInString(char Target)
	{
		return CountSpecificLetterInString(_Value, Target);
	}


	static int CountVowelInString(const std::string& text)
	{
		int counter = 0;
		for (int i = 0; i < text.size(); i++)
		{
			if (IsVowel(text.at(i)))
				counter++;
		}
		return counter;
	}
	int CountVowelInString()
	{
		return CountVowelInString(_Value);
	}

	static int CountEachWordInString(const std::string& text)
	{
		std::string Delimiter = " ";
		std::string word = "";
		std::string S = text;
		int position = 0;
		int counter = 0;
		while ((position = static_cast<int>(S.find(Delimiter))) != std::string::npos)
		{
			word = S.substr(0, position);
			if (!word.empty())
			{
				counter++;
				word.clear();
			}
			S.erase(0, position + Delimiter.length());
		}
		if (!S.empty())
			counter++;


		return counter;
	}

	int CountEachWordInString()
	{
		return CountEachWordInString(_Value);
	}


	static int FindTextPositionInArray(std::string arr[], int arrLength, std::string Target) {
		for (int i = 0; i < arrLength; i++) {
			if (Target == arr[i]) {
				return i;
			}
		}
		return -1;
	}


	static  std::vector <std::string> SplitText(const std::string &text, std::string Delimiter)
	{
		 std::vector <std::string> vString;

		std::string word = "";
		int position = 0;
		std::string S = text;

		while ((position = static_cast<int>(S.find(Delimiter))) != std::string::npos)
		{
			word = S.substr(0, position);
			if (!word.empty())
			{
				vString.push_back(word);

				word.clear();
			}
			S.erase(0, position + Delimiter.length());
		}
		if (!S.empty())
		{
			vString.push_back(S);

		}
		return vString;
	}
	std::vector <std::string> SplitText(std::string Delimiter)
	{
		return SplitText(_Value, Delimiter);
	}

	static std::string ReverseString(const std::string& text)
	{
		std::string result = "";
		std::string Delimiter = " ";
		std::string S1 = text;
		 std::vector <std::string> vSplitString = clsString::SplitText(S1, " ");
		if (!vSplitString.empty())
		{
			for (int i = static_cast<int>(vSplitString.size()) - 1; i >= 0; i--)
			{
				result += vSplitString.at(i) + Delimiter;
			}
		}
		else
			return result;

		return result.substr(0, result.size() - Delimiter.length());
	}
	std::string ReverseString()
	{
		return ReverseString(_Value);

	}

	static std::string JoinString(std::string arrNames[], short arrLength, const std::string& Delimiter)
	{
		std::string text = "";

		for (int i = 0; i < arrLength; i++)
		{
			text += arrNames[i] + Delimiter;
		}


		return text.substr(0, text.size() - Delimiter.length());
	}

	static std::string JoinString( std::vector <std::string>& vText, const std::string& Delimiter)
	{
		std::string text = "";

		for (const std::string& i : vText)
		{
			text += i + Delimiter;

		}
		return text.substr(0, text.size() - Delimiter.length());
	}


	

	static std::string ReplaceWordInString(const std::string& text, const std::string& Target, const std::string& NewWord)
	{
		if (text.empty())
			return "";

		std::string Delimiter = " ";
		 std::vector <std::string> vSplitString = clsString::SplitText(text, Delimiter);
		for (int i = 0; i < vSplitString.size(); i++)
		{
			if (Target == vSplitString.at(i))
			{
				vSplitString.at(i).assign(NewWord);

			}
		}

		return clsString::JoinString(vSplitString, Delimiter);
	}

    std::string ReplaceWordInString(const std::string& Target, const std::string& NewWord)
	{
		return ReplaceWordInString(_Value, Target, NewWord);

	}



	static std::string RemovePunctInString(const std::string& text)
	{
		std::string S = "";
		for (int i = 0; i < text.size(); i++)
		{
			if (!ispunct(text.at(i)))
			{
				S += text.at(i);
			}
		}

		return S;
	}
	std::string RemovePunctInString()
	{
		return RemovePunctInString(_Value);
	}


	static std::string TrimLeft(std::string text)
	{
		std::string space = " ";
		int position = 0;
		while ((position = static_cast<int>(text.find(space))) == 0)
		{

			text.erase(0, position + space.length());
		}
		return text.substr(0, text.size());

	}
	std::string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static int IndexFirstCharacterFromRight(std::string text)
	{
		if (!text.empty())
		{
			for (int i = static_cast<int>(text.size()) - 1; i >= 0; i--)
			{
				if (!isspace(text.at(i)) && !ispunct(text.at(i)) && !isdigit(text.at(i)))
				{
					return i;
				}
			}
		}
		return 0;
	}
	int IndexFirstCharacterFromRight()
	{
		return IndexFirstCharacterFromRight(_Value);
	}


	static std::string TrimRight(std::string text)
	{
		int LastLetterPosition = clsString::IndexFirstCharacterFromRight(text);
		return text.substr(0, LastLetterPosition + 1);
	}
	std::string TrimRight()
	{
		return TrimRight(_Value);
	}

	static std::string TrimText(std::string text)
	{
		return clsString::TrimRight(clsString::TrimLeft(text));
	}
	std::string TrimText()
	{
		return TrimText(_Value);
	}


};

