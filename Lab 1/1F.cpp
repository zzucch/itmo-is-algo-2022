#include <iostream>

using namespace std;

struct fridge {
    int milkL;
    int meatKg;
    int cheesePcs;
    int sweetPcs;
};

int main() {
    struct fridge myFridge = {3, 4, 1, 12};
    struct fridge friendsFridge = {0, 10, 2, 15};

    printf("My friend's fridge is a mess! Maybe I should buy him a bit of meat?\n"
           "y/n?\n");
    char opinion1;
    int meatDonation = 0;

    cin >> opinion1;
    if (opinion1 == 'y') {
        printf("Really? How much kg?\n");
        cin >> meatDonation;
    } else if (opinion1 == 'n') {
        printf("Well, that's ok too...");
    } else {
        printf("What are you saying? I don't understand!\n"
               "Well, why would I want your opinion on the topic...\nGuess I'll just buy 2 kg.\n");
               meatDonation += 2;
    }
    friendsFridge.meatKg += meatDonation;

    printf("\nHow do i say it.. Now my friend has no milk! How much L should I give him?\nI have 3 L currently.\n");
    int milkDelta = 30;
    while (milkDelta > 3) {
        cin >> milkDelta;
        if (milkDelta > 3) {
            printf("I don't have THAT much milk!! Try one more time.\n");
        }
    }

    myFridge.milkL -= milkDelta;
    friendsFridge.milkL += milkDelta;

    printf("\nHe bought me 30 sweets for each L of milk.\n");
    myFridge.sweetPcs += 30 * milkDelta;
    printf("Now I have %d sweets!\n", myFridge.sweetPcs);

    printf("\nAt the start he promised me 1 kg of meat for each candy that I had at the moment.\n"
           "Now he has %d kg.\nWould he buy more meat?\n", friendsFridge.meatKg);

    char opinion2;
    cin >> opinion2;

    if ((opinion2 == 'y' && friendsFridge.meatKg < 12) || (opinion2 == 'n' && friendsFridge.meatKg >= 12)) {
        printf("\nCorrect!");
    } else {
        printf("\nIncorrect!");
    }
  
    return 0;
}
