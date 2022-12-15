#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <random>
#include <unistd.h>

using namespace std;

class State {
private:
    void fill_map(int number_of_buildings = 10) {
        building_remain = number_of_buildings;
        for (int it = 0; it < number_of_buildings; it++) {
            int x = rand() % n;
            int y = rand() % m;
            if (state_map[x][y] == s_empty) {
                state_map[x][y] = s_building;
            } else {
                it--;
            }
        }
    }
    void fill_map_with_zeros() {
        state_map = vector<vector<char>>(n, vector<char>(m, s_empty));
    }

public:
    vector<vector<char>> state_map;
    string country_name;
    int n = 5, m = 25;
    int building_remain;
    int shot_count = 0;

    char s_empty = ' ';
    char s_border = '.';
    char s_destroyed = 'x';
    char s_building = '#';

    int ammo_price = 300;
    int building_price = 180;
    State(string name = "anon", int building_count = 20) {
        country_name = name;
        fill_map_with_zeros();
        fill_map(building_count);
    }
    void print_map() {
        cout << "\t MAP OF " << country_name << ":\t\t\n";
        for (int y = 0; y < m + 2; y++) {
            cout << s_border;
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << s_border;
            for (int j = 0; j < m; j++) {
                cout << state_map[i][j];
            }
            cout << s_border;
            cout << endl;
        }

        for (int y = 0; y < m + 2; y++) {
            cout << s_border;
        }
        cout << endl
             << endl;
    }
    bool attack_check(const State &other) const {
        return other.building_remain * other.building_price > this->ammo_price * this->shot_count;
    }
    void attack(State &other) {
        cout << country_name << " is aiming for the " << shot_count + 1 << " time....\n";
        bool shot_made = false;
        while (!shot_made) {
            int x = rand() % other.n;
            int y = rand() % other.m;
            if (other.state_map[x][y] == other.s_empty) {
                other.state_map[x][y] = other.s_border;
                cout << country_name << " attacked " << other.country_name << ": miss on coords " << x + 1 << " " << y + 1 << "\n";
                shot_made = true;
            } else if (other.state_map[x][y] == other.s_building) {
                other.state_map[x][y] = other.s_destroyed;
                other.building_remain--;
                cout << country_name << " attacked " << other.country_name << ": HIT on coords " << x + 1 << " " << y + 1 << "\n";
                shot_made = true;
            }
        }
        shot_count++;
    }
};

State Anchuaria("Anchuaria", 30);
State Taranteria("Taranteria", 40);

struct Params {
    State *attacker;
    State *defender;
};

void *Anchuaria_attack(void *args) {
    while (Anchuaria.attack_check(Taranteria)) {
        Anchuaria.attack(Taranteria);
    }
    return nullptr;
}
void *Taranteria_attack(void *args) {
    while (Taranteria.attack_check(Anchuaria)) {
        Taranteria.attack(Anchuaria);
    }
    return nullptr;
}

void input() {
    cout << "If you want to enter prices manually, enter 1, else 0:";
    int cmd;
    cin >> cmd;
    if (cmd == 1) {
        cout << "Enter price of ammo in Anchuaria:";
        cin >> Anchuaria.ammo_price;
        cout << "Enter reward for building in Anchuaria:";
        cin >> Anchuaria.building_price;
        cout << "Enter price of ammo in Taranteria:";
        cin >> Taranteria.ammo_price;
        cout << "Enter reward for building in Taranteria:";
        cin >> Taranteria.building_price;
    } else if (cmd != 0) {
        throw invalid_argument("Invalid input");
    }
}

int main(int argc, char **argv) {
    try {
        input();
    } catch (exception &e) {
        throw invalid_argument("Invalid input");
    }

    srand(time(nullptr));

    Anchuaria.print_map();
    Taranteria.print_map();

    pthread_t thread_A, thread_T;
    pthread_create(&thread_A, nullptr, Anchuaria_attack, nullptr);
    pthread_create(&thread_T, nullptr, Taranteria_attack, nullptr);

    pthread_join(thread_A, nullptr);
    pthread_join(thread_T, nullptr);
    Anchuaria.print_map();
    Taranteria.print_map();

    return 0;
}
