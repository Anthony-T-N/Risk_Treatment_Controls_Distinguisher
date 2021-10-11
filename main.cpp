#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

void duplication_check(std::vector<std::string> controls_vector)
{
    std::cout << "[!] Performing duplication check of current vector;" << "\n";
    std::sort(controls_vector.begin(), controls_vector.end());
    auto it = std::unique(controls_vector.begin(), controls_vector.end());
    bool wasUnique = (it == controls_vector.end());
    if (wasUnique == 1)
    {
        std::cout << "[+] No duplicate controls discovered;" << "\n";
    }
    else
    {
        std::cout << "[-] Duplicate controls discovered;" << "\n";
    }
}

int main()
{
    std::vector<std::string> controls_vector;
    std::string constructed_text;
    std::string user_input;
    std::cout << "Enter text: " << "\n";
    while (std::getline(std::cin, user_input))
    {
        /*
        if (user_input == "K\n")
        {
            break;
        }
        */
        if (user_input == "exit")
        {
            break;
        }
        constructed_text += user_input;
    }
    std::cout << "\n";
    //std::cout << input << "\n";
    // TODO: Break when ints located in string.
    if (constructed_text.find_first_of("0123456789") == std::string::npos)
    {
        std::cout << "[-] No numbers found in following text. Please try again:" << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
        system("pause");
        return 0;
    }
    std::string temp_store;
    for (int i = 0; i <= constructed_text.length() - 1; i++)
    {
        if (isdigit(constructed_text[i]) && isdigit(constructed_text[i + 1]) && isdigit(constructed_text[i + 2]) && isdigit(constructed_text[i + 3]))
        {
            temp_store = constructed_text.substr(i, 4);
            //std::cout << temp_store << "\n";
            controls_vector.push_back(temp_store);
            i = i + 4;
        }
    }
    std::cout << "Result: " << "\n";
    for (int i = 0; i <= controls_vector.size() - 1; i++)
    {
        if (i != controls_vector.size() - 1)
        {
            std::cout << controls_vector[i] << ",";
        }
        else
        {
            std::cout << controls_vector[i];
        }
    }
    std::cout << "\n\n";
    duplication_check(controls_vector);
    std::cout << "\n\n";
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
    system("pause");
    return 0;

}
