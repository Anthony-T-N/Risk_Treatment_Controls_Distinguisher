#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>

// TEMP FOR SLEEP
#include <windows.h>

// https://stackoverflow.com/questions/21873048/getting-an-error-fopen-this-function-or-variable-may-be-unsafe-when-complin/21873153
#pragma warning(disable:4996);

std::string print_time()
{
    // https://stackoverflow.com/questions/16357999/current-date-and-time-as-string/16358264
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;

}

std::vector<std::string> duplication_check(std::vector<std::string> controls_vector)
{
    std::cout << "[!] Performing duplication check of current vector;" << "\n";
    std::sort(controls_vector.begin(), controls_vector.end());
    controls_vector.erase(std::unique(controls_vector.begin(), controls_vector.end()), controls_vector.end());
    auto it = std::unique(controls_vector.begin(), controls_vector.end());
    bool wasUnique = (it == controls_vector.end());
    if (wasUnique == 1)
    {
        std::cout << "|-> [+] No duplicate controls discovered;" << "\n";
    }
    else
    {
        std::cout << "|-> [-] Duplicate controls discovered;" << "\n";
        std::cout << "    |-> [+] Removing duplicate controls;" << "\n";
        controls_vector.erase(std::unique(controls_vector.begin(), controls_vector.end()), controls_vector.end());
    }
    return controls_vector;
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
        std::cout << "[-] No number(s) found in following text. Please try again." << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
        return 0;
    }
    std::string temp_store;
    bool digit_set_found = false;
    for (int i = 0; i <= constructed_text.length() - 1; i++)
    {
        if (isdigit(constructed_text[i]) && isdigit(constructed_text[i + 1]) && isdigit(constructed_text[i + 2]) && isdigit(constructed_text[i + 3]))
        {
            temp_store = constructed_text.substr(i, 4);
            controls_vector.push_back(temp_store);
            i = i + 4;
            digit_set_found = true;
        }
    }
    if (digit_set_found == false)
    {
        std::cout << "[-] No 4 digit number found in following text. Please try again." << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
        return 0;
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

int sanity_check(std::vector<std::string> vul_ID_vector, std::vector<std::vector<std::string>> controls_vector)
{
    int total_control_rows = 0;;
    for (int i = 0; i <= controls_vector.size() - 1; i++)
    {
        total_control_rows += 1;
    }
    std::cout << "============================== Sanity Check ===============================" << "\n";
    std::cout << "Current number vulnerability IDs: " << vul_ID_vector.size() << "\n";
    std::cout << "Total number of control rows: " << total_control_rows << "\n";
    if (total_control_rows < vul_ID_vector.size())
    {
        std::cout << "[-] Total number of control rows mismatch with number of provided vulnerability IDs;" << "\n";
        std::cout << "[-] Proceed with caution;" << "\n";
    }
    if (total_control_rows > vul_ID_vector.size())
    {
        std::cout << "[-] Warning! Total number of control rows exceed number of provided vulnerability IDs;" << "\n";
        std::cout << "[-] The program will now exit;" << "\n";
        return 0;
    }
    std::cout << "===========================================================================" << "\n\n";
    return 1;
}

int mod_control_sorter(std::vector<std::string> vul_ID_vector)
{
    std::vector<std::vector<std::string>> controls_vector;
    std::string constructed_text;
    std::string user_input;
    std::cout << "Enter/Paste text of controls: (Type 'qqqq' and press enter to process text | Type 'exit' and press enter to exit program safely);" << "\n";
    while (std::getline(std::cin, user_input))
    {
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
    if (constructed_text.find_first_of("0123456789") == std::string::npos)
    {
        std::cout << "[-] No number(s) found in following text. Please try again." << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
        return 0;
    }
    else if (constructed_text.find_first_of('!') == std::string::npos)
    {
        std::cout << "[-] No '!' found in the followng text. Please try again." << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
        return 0;
    }
    std::string temp_store;
    bool digit_set_found = false;
    bool exclamation_mark_found = false;
    std::vector<std::string> short_term_controls_vector;
    for (int i = 0; i <= constructed_text.length() - 1; i++)
    {
        if (isdigit(constructed_text[i]) && isdigit(constructed_text[i + 1]) && isdigit(constructed_text[i + 2]) && isdigit(constructed_text[i + 3]))
        {
            temp_store = constructed_text.substr(i, 4);
            short_term_controls_vector.push_back(temp_store);
            i = i + 4;
            digit_set_found = true;
        }
        if (constructed_text[i] == '!')
        {
            exclamation_mark_found = true;
            controls_vector.push_back(short_term_controls_vector);
            short_term_controls_vector.clear();
        }
    }
    if (digit_set_found == false)
    {
        std::cout << "[-] No 4 digit number found in following text. Please try again." << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
        return 0;
    }
    if (exclamation_mark_found == false)
    {
        std::cout << "[-] Exclamation mark not found. Please try again." << "\n";
        std::cout << "[!] END" << "\n";
        std::cout << "[!] Exiting..." << "\n\n";
        return 0;
    }
    if (0 == sanity_check(vul_ID_vector, controls_vector))
    {
        return 0;
    }

    std::ofstream output_file;
    if (std::filesystem::exists("vul_sorted_controls.csv") == false)
    {
        std::cout << "[!] Unable to locate 'vul_sorted_controls.csv'. Creating new csv file;" << "\n";
        std::cout << "[+] Created at: " << std::filesystem::current_path() << "\n";
    }
    output_file.open("vul_sorted_controls.csv", std::ios::app);
    std::cout << "[+] Opened vul_sorted_controls.csv successfully;" << "\n\n";

    // EXCEL DETAILS:
    int excel_row = 3;

    std::cout << "[!] Result: " << "\n";
    std::cout << print_time() << "\n\n";
    output_file << print_time() << "\n\n";
    for (int i = 0; i <= controls_vector.size() - 1; i++)
    {
        std::cout << "\n\n";
        std::cout << "============================= Additional Info =============================" << "\n";
        std::cout << "Number of control(s) counted: " << controls_vector[i].size() << "\n";
        controls_vector[i] = duplication_check(controls_vector[i]);
        std::cout << "ROUND 2: Number of control(s) counted: " << controls_vector[i].size() << "\n";
        std::cout << "Performing 2nd duplication check" << "\n";
        controls_vector[i] = duplication_check(controls_vector[i]);
        std::cout << "===========================================================================" << "\n";
        std::cout << "\n";
        // Comma used as seperator in csv files.
        if (controls_vector[i].empty())
        {
            std::cout << vul_ID_vector[i] << ",";
            output_file << vul_ID_vector[i] << ",";
            std::cout << "EMPTY";
            output_file << "EMTPY";
        }
        else
        {
            for (int j = 0; j <= controls_vector[i].size() - 1; j++)
            {
                if (j == 0)
                {
                    std::cout << vul_ID_vector[i] << ",";
                    output_file << vul_ID_vector[i] << ",";
                }
                if (j != controls_vector[i].size() - 1)
                {
                    std::cout << controls_vector[i][j] << ",";
                    output_file << controls_vector[i][j] << ",";
                }
                else
                {
                    std::cout << controls_vector[i][j];
                    output_file << controls_vector[i][j];
                }
            }
            /* Originally placed here. However, requirement to remove duplicates beforehand.
            std::cout << "\n\n";
            std::cout << "============================= Additional Info =============================" << "\n";
            std::cout << "Number of control(s) counted: " << controls_vector[i].size() << "\n";
            duplication_check(controls_vector[i]);
            std::cout << "===========================================================================" << "\n";
            std::cout << "\n";
            */
            std::cout << "\n";
        }
        // Increase excel row by 4.
        output_file << "\n";
        std::string test;
        std::vector<std::string> alphabet({ "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","@"});
        int alphabet_increment = 1;
        int alphabet_increment_second = -1;
        bool second_iteration = false;
        std::string cell_letter;
        for (int k = 0; k < controls_vector[i].size(); k++)
        {
            if (alphabet[alphabet_increment] == "@")
            {
                alphabet_increment = 0;
                second_iteration = true;
                alphabet_increment_second++;
            }
            if (second_iteration == true)
            {
                cell_letter = alphabet[alphabet_increment_second];
                cell_letter.append(alphabet[alphabet_increment]);
            }
            else
            {
                cell_letter = alphabet[alphabet_increment];
            }
            //std::cout << test << "\n";
            // Commented out because program kept printing out a column of letters.
            //std::cout << alphabet[alphabet_increment] << "\n";
            test.append(",=TEXT(" + cell_letter + std::to_string(excel_row) + "#\"0000\")");
            //output_file << ",=TEXT(B" << excel_row << "#\"0000\"),";
            alphabet_increment++;
        }
        output_file << test;
        output_file << "\n\n";
        excel_row += 3;
    }
    output_file << "\n\n";
    output_file.close();
    return 0;
}

int mass_vul()
{
    std::string user_input;
    std::vector<std::string> vul_ID_vector;
    std::string constructed_text;

    std::cout << "STAGE 1: Compile all vul IDs " << "\n";
    std::cout << "Enter/Paste your full list of vul IDs: (Type 'qqqq' and press enter to process text | Type 'exit' and press enter to exit program safely);" << "\n";
    while (std::getline(std::cin, user_input))
    {
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

    std::string temp_str_store;
    bool digit_set_found = false;
    bool char_v_found = false;
    int starting_v_pos = 0;
    // {INFO} Identify VXXX_XXXXXXXX_01
    for (int i = 0; i <= constructed_text.length() - 1; i++)
    {
        // {INFO} Individually goes through character of constructed text.

        if (constructed_text[i] == 'V' && char_v_found == false)
        {
            // https://stackoverflow.com/questions/14544043/operand-types-are-incompatible-char-and-const-char/14544047
            // {INFO} Detect character "v".
            std::cout << "[!] Letter 'V' found" << "\n";
            char_v_found = true;
            starting_v_pos = i;
        }
        else if (isdigit(constructed_text[i]) && char_v_found == true)
        {
            // {INFO} After locating the char "V". Identify the next digital in string.
            std::cout << "[!] Number found" << "\n";
            int j = 0;
            while (isdigit(constructed_text[i + j]))
            {
                j += 1;
                std::cout << constructed_text[i + j] << "+";
            }
            temp_str_store = constructed_text.substr(starting_v_pos, (i + j) - starting_v_pos);
            std::cout << "Storing: " << temp_str_store << "\n\n";
            vul_ID_vector.push_back(temp_str_store);
            char_v_found = false;
            // Once the end of the vul ID has been reached. Skip iteration(s) to prevent for loop from looping through the same numbers/characters again.
            i = (i + j) - 1;
        }
    }
    std::cout << "[!] Printing back stored vector:" << "\n";
    for (int i = 0; i <= vul_ID_vector.size() - 1; i++)
    {
        std::cout << vul_ID_vector[i] << "\n";
    }
    std::cout << "\n";
    std::cout << "STAGE 2: Associating controls with vul IDs " << "\n";
    std::cout << "Ensure controls/text in the same row as vul IDs contain an \"!\" at the end" << "\n";
    std::cout << "EXAMPLE: =XX&\"!\"" << "\n";
    mod_control_sorter(vul_ID_vector);
    return 0;
}

int main()
{
    std::cout << "=======================================" << "\n";
    std::cout << "- Risk_Treatment_Controls_Distinguisher console application" << "\n";
    std::cout << "- Console Application Version: 3.5" << "\n";
    std::cout << "- Created By: Anthony N." << "\n";
    std::cout << "- Current location of executable: " << std::filesystem::current_path() << "\n";
    std::cout << "=======================================" << "\n\n";

    while (true)
    {
        std::cout << "Select an option:" << "\n";
        std::cout << "[0] Control_sorter" << "\n";
        std::cout << "[1] Controls & Vulnerability association" << "\n";
        std::cout << "[exit] Exit" << "\n";
        std::cout << "Selection ?:" << "\n";
        std::cout << "> ";
        std::string user_input;
        std::getline(std::cin, user_input);
        std::cout << "\n";
        if (user_input == "0")
        {
            std::cout << "WARNING: DOES NOT PERFORM DUPLICATION REMOVAL" << "\n";
            int flag = 0;
            while (flag == 0)
            {
                flag = control_sorter();
            }
        }
        else if (user_input == "1")
        {
            mass_vul();
        }
        else if (user_input == "exit")
        {
            break;
        }
    }
    std::cout << "[!] END" << "\n";
    std::cout << "[!] Exiting..." << "\n\n";
    std::cout << "Press enter to continue . . ." << "\n";
    std::cin.get();
    return 0;
}
