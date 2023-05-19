#include <iostream>

void getData(char &element, int &global, int &last, std::string &str, int &i) {
    element = str[i++];
    std::string str_amount;

    while (isdigit(str[i])) {
        str_amount += str[i++];
    }
    int amount = std::stoi(str_amount);

    last = global;
    global += amount;
}

void handleEnding(int &difference, char &element, char &other_element, int &global, int &last) {
    if (element != other_element) {
        difference += global - last;
    }
}

int calculateDifference(std::string &i_string, std::string &j_string, int &n, int &m) {
    int difference = 0;

    int i = 0;
    int j = 0;
    char i_element, j_element;
    int i_global = 0;
    int j_global = 0;
    int last;


    getData(i_element, i_global, last, i_string, i);
    getData(j_element, j_global, last, j_string, j);

    while (i < n || j < m) {
        if (i < n && j < m) {
            if (i_element != j_element) {
                difference += std::min(i_global - last, j_global - last);
            }

            if (j_global < i_global) {
                getData(j_element, j_global, last, j_string, j);
            } else if (i_global < j_global) {
                getData(i_element, i_global, last, i_string, i);
            } else {
                getData(i_element, i_global, last, i_string, i);
                getData(j_element, j_global, last, j_string, j);
            }
        } else if (i < n) { // j ended
            handleEnding(difference, j_element, i_element, j_global, last);
            break;
        } else if (j < m) { // i ended
            handleEnding(difference, i_element, j_element, i_global, last);
            break;
        }
    }

    return difference;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::string first;
    std::string second;

    std::cin >> n >> m >> k;
    std::cin >> first;
    std::cin >> second;

    if (calculateDifference(first, second, n, m) < k) {
        std::cout << "Yes";
    } else {
        std::cout << "No";
    }

    return 0;
}
