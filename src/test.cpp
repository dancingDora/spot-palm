#include <iostream>
#include <fstream>
using namespace std;
string nameBase[] = {
        "Abigail",
        "Adam",
        "Addison",
        "Adrian",
        "Aidan",
        "Aiden",
        "Alan",
        "Albert",
        "Alex",
        "Alexander",
        "Alexandra",
        "Alexis",
        "Alice",
        "Alicia",
        "Alison",
        "Allan",
        "Allen",
        "Allison",
        "Alyssa",
        "Amanda",
        "Amber",
        "Amelia",
        "Amy",
        "Andrea",
        "Andrew",
        "Angela",
        "Angelina",
        "Anna",
        "Anne",
        "Annie",
        "Anthony",
        "Antonio",
        "April",
        "Arthur",
        "Ashley",
        "Audrey",
        "Austin",
        "Autumn",
        "Ava",
        "Avery",
        "Bailey",
        "Barbara",
        "Beatrice",
        "Benjamin",
        "Beth",
        "Betty",
        "Beverly",
        "Bianca",
        "Bill",
        "Blake",
        "Bonnie",
        "Bradley",
        "Brandon",
        "Brenda",
        "Brett",
        "Brian",
        "Brianna",
        "Brittany",
        "Brooke",
        "Brooklyn",
        "Bruce",
        "Bryan",
        "Caleb",
        "Cameron",
        "Camila",
        "Candice",
        "Carla",
        "Carlos",
        "Caroline",
        "Carolyn",
        "Carter",
        "Catherine",
        "Cathy",
        "Cecilia",
        "Chad",
        "Charles",
        "Charlotte",
        "Chelsea",
        "Cheryl",
        "Chris",
        "Christian",
        "Christina",
        "Christine",
        "Christopher",
        "Cindy",
        "Claire",
        "Clara",
        "Clarence",
        "Claudia",
        "Clayton",
        "Cody",
        "Colleen",
        "Connor",
        "Cooper",
        "Corey",
        "Courtney",
        "Craig",
        "Crystal",
        "Cynthia",
        "Daisy"
        "Dale",
        "Damian",
        "Damon",
        "Dana",
        "Daniel",
        "Danielle",
        "Danny",
        "Daphne",
        "Darlene",
        "Darren",
        "Dave",
        "David",
        "Dawn",
        "Dean",
        "Deanna",
        "Debbie",
        "Deborah",
        "Declan",
        "Deirdre",
        "Delilah",
        "Denise",
        "Dennis",
        "Derek",
        "Desiree",
        "Destiny",
        "Devin",
        "Diana",
        "Diane",
        "Diego",
        "Dillon",
        "Dina",
        "Dionne",
        "Dirk",
        "Dominic",
        "Dominique",
        "Don",
        "Donald",
        "Donna",
        "Dora",
        "Dorian",
        "Dorothy",
        "Doug",
        "Douglas",
        "Drake",
        "Drew",
        "Duane",
        "Dylan",
        "Earl",
        "Ed",
        "Eddie",
        "Edgar",
        "Edith",
        "Edna",
        "Edward",
        "Edwin",
        "Eileen",
        "Elaine",
        "Eleanor",
        "Elena",
        "Eli",
        "Elias",
        "Elijah",
        "Elise",
        "Elizabeth",
        "Ella",
        "Elle",
        "Ellen",
        "Ellie",
        "Elliot",
        "Elliott"
};
int main() {
    ofstream fout("case_test.txt");
    for(int i = 1; i <= 168; i++) {
        fout << "add_user -n " << nameBase[i] << " -v 1 -g 1 -m abc -i " << i + 1 << " -p " << i + 1 << endl;
    }
    for(int i = 1; i <= 168; i++) {
        fout << "login -i " << i << " -p " << i << endl;
    }
    for(int i = 1; i <= 168; i++) {
        fout << "modify_graph -u " << i;
        fout << " -swim " << rand() % 1;
        fout << " -run " << rand() % 1;
        fout << " -cycle " << rand() % 1;
        fout << " -basketball " << rand() % 1;
        fout << " -football " << rand() % 1;
        fout << " -tennis " << rand() % 1;
        fout << " -table_tennis " << rand() % 1;
        fout << " -box " << rand() % 1;
        fout << " -shoot " << rand() % 1;
        fout << " -volleyball " << rand() % 1;
        fout << " -baseball " << rand() % 1;
        fout << " -gymnastic " << rand() % 1;
        fout << " -sky " << rand() % 1;
        fout << " -ice_skating " << rand() % 1;
        fout << " -marathon " << rand() % 1;
        fout << " -row " << rand() % 1;
        fout << " -surf " << rand() % 1;
        fout << " -IC 8bit " << rand() % 1;
        fout << " -classical " << rand() % 1;
        fout << " -jazz_blues " << rand() % 1;
        fout << " -folk " << rand() % 1;
        fout << " -pop " << rand() % 1;
        fout << " -rock " << rand() % 1;
        fout << " -dance " << rand() % 1;
        fout << " -rap " << rand() % 1;
        fout << " -electronic " << rand() % 1 << endl;
    }
}