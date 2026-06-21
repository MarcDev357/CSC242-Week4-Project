/*
 * ============================================================
 * Program Name : crypt.cpp
 * Course       : CSC 242
 * Assignment   : Signature Assignment (Group Project)
 * Team Members : Marcus Wiggs, David Cruz, Cassius Miller
 * Date         : June 2026
 *
 * Description  :
 *   Monoalphabet substitution cipher — P8.7
 *   Encrypts or decrypts a file using a keyword-derived cipher
 *   alphabet. The keyword letters (de-duplicated) are placed
 *   first; the remaining letters follow in reverse order (Z..A).
 *   This file contains argument parsing, file processing, and
 *   the program entry point. It works together with david.cpp,
 *   which implements the cipher-alphabet and character-mapping
 *   functions.
 *
 * Usage        :
 *   crypt -kKEYWORD input.txt output.txt        (encrypt)
 *   crypt -d -kKEYWORD input.txt output.txt     (decrypt)
 *
 *   Example:
 *     crypt -kFEATHER plain.txt encrypted.txt
 *     crypt -d -kFEATHER encrypted.txt recovered.txt
 *
 * Work split   :
 *   David Cruz     — buildCipherAlphabet, transformChar
 *   Cassius Miller — parseArguments, processFile, main
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <string>

// ============================================================
// DAVID CRUZ'S FUNCTIONS — declarations only.
// Implementations belong to David; do not edit these blocks.
// ============================================================

// ----- Author: David Cruz -----
// Builds the 26-character substitution alphabet from keyword.
// Keyword letters (uppercased, de-duplicated) come first,
// then unused letters appended in reverse order (Z down to A).
// Example: "FEATHER" -> "FEATHRZYXWVUSQPONMLKJIGDCB"
std::string buildCipherAlphabet(const std::string& keyword);

// ----- Author: David Cruz -----
// Maps a single character through the cipher alphabet.
// decryptMode = false -> encrypt (plain->cipher index lookup)
// decryptMode = true  -> decrypt (find cipher letter, return plain)
// Non-letter characters are returned unchanged. Case is preserved.
char transformChar(char ch, const std::string& cipher, bool decryptMode);

// ============================================================
// CASSIUS MILLER'S FUNCTIONS
// ============================================================

// ============================================================
// FUNCTION: parseArguments
// ----- Author: Cassius Miller -----
//
// Purpose : Parses command-line arguments to extract the mode
//           flag (-e/-d), the keyword (-k<WORD>), and the
//           input/output file paths.
//
//           Flags may appear in any order before the filenames.
//           The last two bare arguments (not starting with '-')
//           are treated as inputFile and outputFile respectively.
//
// Params  : argc, argv   — standard command-line arguments
//           decryptMode  — (out) true if -d flag present
//           keyword      — (out) keyword string extracted from -k
//           inputFile    — (out) path to the source file
//           outputFile   — (out) path to the destination file
//
// Returns : true on success, false if required args are missing
// ============================================================
bool parseArguments(int argc, char* argv[],
                    bool& decryptMode,
                    std::string& keyword,
                    std::string& inputFile,
                    std::string& outputFile)
{
    decryptMode = false;   // Default: encrypt mode
    keyword     = "";
    inputFile   = "";
    outputFile  = "";

    // Collect the two positional filenames separately from flags
    std::string files[2];
    int fileCount = 0;

    // Scan every argument after the program name
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg.size() > 2 && arg[0] == '-' && arg[1] == 'k')
        {
            // Keyword immediately follows -k with no space (e.g., -kFEATHER)
            keyword = arg.substr(2);
        }
        else if (arg == "-d")
        {
            decryptMode = true;   // Decrypt mode
        }
        else if (arg == "-e")
        {
            decryptMode = false;  // Encrypt mode (explicit)
        }
        else if (arg[0] != '-')
        {
            // Any non-flag argument is a filename (input first, then output)
            if (fileCount < 2)
                files[fileCount++] = arg;
        }
        else
        {
            // Unrecognized flag
            std::cerr << "Error: Unknown flag '" << arg << "'\n";
            return false;
        }
    }

    // Keyword is required — program must error if omitted
    if (keyword.empty())
    {
        std::cerr << "Error: A keyword is required. Supply it with -k, "
                     "e.g. -kFEATHER\n";
        return false;
    }

    // Both an input file and an output file are required
    if (fileCount < 2)
    {
        std::cerr << "Error: An input file and an output file are required.\n";
        std::cerr << "Usage: crypt -kKEYWORD [-d] input.txt output.txt\n";
        return false;
    }

    inputFile  = files[0];
    outputFile = files[1];

    return true;  // All required arguments present and valid
}

// ============================================================
// FUNCTION: processFile
// ----- Author: Cassius Miller -----
//
// Purpose : Reads every character from inputFile and writes the
//           transformed character to outputFile. Each character
//           is passed through transformChar (David's function)
//           which handles both encryption and decryption.
//           Non-letter characters (spaces, punctuation, newlines)
//           pass through unchanged per the cipher specification.
//
// Params  : inputFile   — path to the source file
//           outputFile  — path to the destination file
//           cipher      — 26-char substitution alphabet from
//                         buildCipherAlphabet
//           decryptMode — true = decrypt, false = encrypt
//
// Returns : void; exits program on file open failure
// ============================================================
void processFile(const std::string& inputFile,
                 const std::string& outputFile,
                 const std::string& cipher,
                 bool decryptMode)
{
    // Open source file for character-by-character reading
    std::ifstream inFile(inputFile);
    if (!inFile.is_open())
    {
        std::cerr << "Error: Cannot open input file: " << inputFile << "\n";
        std::exit(1);
    }

    // Open destination file for writing
    std::ofstream outFile(outputFile);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Cannot open output file: " << outputFile << "\n";
        std::exit(1);
    }

    char ch;

    // Read one character at a time and write the transformed result
    while (inFile.get(ch))
    {
        // transformChar handles encrypt/decrypt and case preservation
        outFile.put(transformChar(ch, cipher, decryptMode));
    }

    inFile.close();
    outFile.close();
}

// ============================================================
// FUNCTION: main
// ----- Author: Cassius Miller -----
//
// Purpose : Entry point. Parses command-line arguments, builds
//           the cipher alphabet (David's function), then calls
//           processFile to encrypt or decrypt the input.
// ============================================================
int main(int argc, char* argv[])
{
    bool        decryptMode;
    std::string keyword;
    std::string inputFile;
    std::string outputFile;

    // Parse and validate command-line arguments
    if (!parseArguments(argc, argv, decryptMode, keyword, inputFile, outputFile))
        return 1;  // Error message already printed by parseArguments

    // Build the cipher alphabet from the keyword (David Cruz)
    std::string cipher = buildCipherAlphabet(keyword);

    // Encrypt or decrypt the file
    processFile(inputFile, outputFile, cipher, decryptMode);

    // Confirm what was done
    std::string mode = decryptMode ? "Decryption" : "Encryption";
    std::cout << mode << " complete. Output written to: " << outputFile << "\n";

    return 0;
}
