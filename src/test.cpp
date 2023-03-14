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
        "Daisy",
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
    for(int i = 0; i <= 169; i++) {
        fout << "add_user -n " << nameBase[i] << " -v 1 -g 1 -m abc -i " << i + 1 << " -p " << i + 1 << endl;
    }
    for(int i = 1; i <= 170; i++) {
        fout << "login -i " << i << " -p " << i << endl;
    }
    for(int i = 1; i <= 170; i++) {
        fout << "modify_graph -i " << i;
        fout << " -swim " << (rand() % 2);
        fout << " -run " << (rand() % 2);
        fout << " -cycle " << (rand() % 2);
        fout << " -basketball " << (rand() % 2);
        fout << " -football " << (rand() % 2);
        fout << " -tennis " << (rand() % 2);
        fout << " -table_tennis " << (rand() % 2);
        fout << " -box " << (rand() % 2);
        fout << " -shoot " << (rand() % 2);
        fout << " -volleyball " << (rand() % 2);
        fout << " -baseball " << (rand() % 2);
        fout << " -gymnastic " << (rand() % 2);
        fout << " -sky " << (rand() % 2);
        fout << " -ice_skating " << (rand() % 2);
        fout << " -marathon " << (rand() % 2);
        fout << " -row " << (rand() % 2);
        fout << " -surf " << (rand() % 2);
        fout << " -classical " << (rand() % 2);
        fout << " -jazz_blues " << (rand() % 2);
        fout << " -folk " << (rand() % 2);
        fout << " -pop " << (rand() % 2);
        fout << " -rock " << (rand() % 2);
        fout << " -dance " << (rand() % 2);
        fout << " -rap " << (rand() % 2);
        fout << " -electronic " << (rand() % 2) << endl;
    }
    for(int i = 1; i <= 170; i++) {
        fout << "query_graph -i " << i << " -q " << i << endl;
    }
//    for(int i = 1; i <= 170; i++) {
//        fout << "recommend_graph -i " << i << endl;
//    }
}