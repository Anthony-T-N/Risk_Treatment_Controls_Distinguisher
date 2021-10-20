#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>

void duplication_check(std::vector<std::string> controls_vector)
{
    std::cout << "[!] Performing duplication check of current vector;" << "\n";
    std::sort(controls_vector.begin(), controls_vector.end());
    auto it = std::unique(controls_vector.begin(), controls_vector.end());
    bool wasUnique = (it == controls_vector.end());
    if (wasUnique == 1)
    {
        std::cout << "|-> [+] No duplicate controls discovered;" << "\n";
    }
    else
    {
        std::cout << "|-> [-] Duplicate controls discovered;" << "\n";
    }
}

int control_sorter()
{
    std::vector<std::string> controls_vector;
    std::string constructed_text;
    std::string user_input;
    std::cout << "Enter/Paste text: (Type 'qqqq' and press enter to process text | Type 'exit' and press enter to exit program safely);" << "\n";
    while (std::getline(std::cin, user_input))
    {
        /*
        if (user_input == "K\n")
        {
            break;
        }
        */
        if (user_input == "qqqq")
        {
            break;
        }
        else if (user_input == "exit")
        {
            return 1;
        }
        constructed_text += user_input;
    }
    std::cout << "\n";
    //std::cout << input << "\n";
    // TODO: Break when 4 digit numbers are not located in string.
    if (constructed_text.find_first_of("0123456789") == std::string::npos)
    {
        std::cout << "[-] No 4 digit number found in following text. Please try again." << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
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
    std::ofstream output_file;
    if (std::filesystem::exists("sorted_controls.csv") == false)
    {
        std::cout << "[!] Unable to locate 'sorted_controls.csv'. Creating new csv file;" << "\n";
        std::cout << "[+] Created at: " << std::filesystem::current_path() << "\n";
    }
    output_file.open("sorted_controls.csv", std::ios::app);
    std::cout << "[+] Opened sorted_controls.csv successfully;" << "\n\n";
    // Comma used as seperator in csv files.
    std::cout << "Result: " << "\n";
    for (int i = 0; i <= controls_vector.size() - 1; i++)
    {
        if (i == 0)
        {
            output_file << "Control(s) Entry:,";
        }
        if (i != controls_vector.size() - 1)
        {
            std::cout << controls_vector[i] << ",";
            output_file << controls_vector[i] << ",";
        }
        else
        {
            std::cout << controls_vector[i];
            output_file << controls_vector[i];
        }
    }
    output_file << "\n\n";
    output_file.close();
    std::cout << "\n\n";
    std::cout << "============================= Additional Info =============================" << "\n";
    std::cout << "Number of control(s) counted: " << controls_vector.size() << "\n";
    duplication_check(controls_vector);
    std::cout << "===========================================================================" << "\n";
    std::cout << "\n";
    return 0;
}

int main()
{
    std::cout << "=======================================" << "\n";
    std::cout << "- Risk_Treatment_Controls_Distinguisher console application" << "\n";
    std::cout << "- Console Application Version: 1.0" << "\n";
    std::cout << "- Created By: Anthony N." << "\n";
    std::cout << "- Current location of executable: " << std::filesystem::current_path() << "\n";
    std::cout << "=======================================" << "\n\n";

    int flag = 0;
    while (flag == 0)
    {
        flag = control_sorter();
    }
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
    system("pause");
    return 0;
}
