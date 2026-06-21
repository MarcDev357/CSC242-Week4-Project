/*
 * ============================================================
 * Program Name : david.cpp
 * Course       : CSC 242
 * Assignment   : Signature Assignment (Group Project)
 * Team Members : Marcus Wiggs, David Cruz, Cassius Miller
 * Date         : June 2026
 *
 * Description  :
 *   Monoalphabet substitution cipher — P8.7
 *   Implementation file for David Cruz's functions. Builds the
 *   keyword-derived cipher alphabet and maps individual
 *   characters for encryption and decryption. Compiles together
 *   with crypt.cpp, which provides argument parsing, file
 *   processing, and the program entry point.
 *
 * Work split   :
 *   David Cruz — buildCipherAlphabet, transformChar
 * ============================================================
 */

// Implementations for David Cruz's functions
#include <string>
#include <cctype>

// Builds the 26-character substitution alphabet from keyword.
// Keyword letters (uppercased, de-duplicated) come first,
// then unused letters appended in reverse order (Z down to A).
std::string buildCipherAlphabet(const std::string& keyword)
{
	bool used[26] = {false};
	std::string result;

	// Process keyword: uppercase, skip non-letters, de-duplicate
	for (char ch : keyword)
	{
		if (!std::isalpha(static_cast<unsigned char>(ch)))
			continue;
		char up = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
		int idx = up - 'A';
		if (!used[idx])
		{
			used[idx] = true;
			result.push_back(up);
		}
	}

	// Append remaining unused letters in reverse order Z..A
	for (char c = 'Z'; c >= 'A'; --c)
	{
		int idx = c - 'A';
		if (!used[idx])
			result.push_back(c);
		if (c == 'A') break; // avoid char underflow in some environments
	}

	return result;
}

// Maps a single character through the cipher alphabet.
// decryptMode = false -> encrypt (plain->cipher index lookup)
// decryptMode = true  -> decrypt (find cipher letter, return plain)
// Non-letter characters are returned unchanged. Case is preserved.
char transformChar(char ch, const std::string& cipher, bool decryptMode)
{
	if (!std::isalpha(static_cast<unsigned char>(ch)))
		return ch;

	bool isLower = std::islower(static_cast<unsigned char>(ch));
	char up = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));

	if (!decryptMode)
	{
		int idx = up - 'A';
		if (idx < 0 || idx >= 26 || cipher.size() < 26)
			return ch;
		char mapped = cipher[idx];
		return isLower ? static_cast<char>(std::tolower(static_cast<unsigned char>(mapped))) : mapped;
	}
	else
	{
		// Find the character in the cipher alphabet
		size_t pos = cipher.find(up);
		if (pos == std::string::npos)
			return ch;
		char mapped = static_cast<char>('A' + pos);
		return isLower ? static_cast<char>(std::tolower(static_cast<unsigned char>(mapped))) : mapped;
	}
}
