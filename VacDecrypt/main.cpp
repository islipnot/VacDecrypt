#include <iostream>
#include <string>

#define DECRYPTION_KEY 3

#define DECRYPTION_MODE 'r'

// 1: 38 >> XOR
// 2: 94 >> XOR
// 5: 19 >> XOR
// 8: 3  >> ROL

inline void RolDecrypt(std::string& str, int key)
{
    uint8_t last;

    for (char& ch : str)
    {
        last = static_cast<uint8_t>(ch);
        ch = (last << key) | (last >> (8 - key));
    }
}

inline void XorDecrypt(std::string& str, int key)
{
    char last;

    for (char& ch : str)
    {
        last = ch;
        ch = last ^ key;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "Argument format: <string> <type> <key>\n";
        std::cout << "Types: r == ROL, x == XOR\n";
        std::cout << "String should be surrounded by quotes for safety\n";
        return 0;
    }

    // Formatting input

    std::string str = argv[1];
    std::string FormattedStr;

    for (size_t i = 0, const sz = str.size(); i < sz; ++i)
    {
        char FirstCh = str[i];

        if (FirstCh == '\\' && i + 1 < sz)
        {
            ++i;

            FirstCh = str[i];
            char CurrCh = -1;

            switch (FirstCh)
            {
            case '\'': CurrCh = '\''; break;
            case '\"': CurrCh = '\"'; break;
            case '\?': CurrCh = '\?'; break;
            case '\\': CurrCh = '\\'; break;
            case 'a':  CurrCh = '\a'; break;
            case 'b':  CurrCh = '\b'; break;
            case 'f':  CurrCh = '\f'; break;
            case 'n':  CurrCh = '\n'; break;
            case 'r':  CurrCh = '\r'; break;
            case 't':  CurrCh = '\t'; break;
            case 'v':  CurrCh = '\v'; break;
            case '0':  CurrCh = '\0'; break;
            }

            if (CurrCh != -1)
            {
                FormattedStr += CurrCh;
            }
            else if (i + 2 < sz && str[i] == 'x')
            {
                FormattedStr += static_cast<char>(std::stoi(str.substr(i + 1, 2), nullptr, 16));
                i += 2;
            }
        }
        else FormattedStr += str[i];
    }


    // Getting decryption type

    char DecryptionMode;

    if (argc > 2) DecryptionMode = argv[2][0];
    else DecryptionMode = DECRYPTION_MODE;

    // Getting decryption key

    int DecryptionKey;

    if (argc > 3) DecryptionKey = std::stoi(argv[3]);
    else DecryptionKey = DECRYPTION_KEY;

    // Decrypting string

    if (DecryptionMode == 'r')
    {
        RolDecrypt(FormattedStr, DecryptionKey);
    }
    else
    {
        XorDecrypt(FormattedStr, DecryptionKey);
    }

    std::cout << "RESULT: \"" << FormattedStr << "\"\n";

    return 0;
}