#include <bits/stdc++.h>
using namespace std;

string SHOW_STATUS(int i) {
    switch (i) {
        case 0:  return "playing";
        case 1:  return "not out";
        case 2:  return "bold out";
        case 3:  return "caught out";
        case 4:  return "run out";
        default: return "unknown";
    }
}

class Team {
    string team_name;
    string p_name[12];
    int p_run[12];
    int p_status[12];
    int p_ball[12];
    int p_num;
    int Extra_run;
public:
    Team();
    int Init();
    string get_name(int i) { return p_name[i]; }
    int get_run(int i) { return p_run[i]; }
    int get_status(int i) { return p_status[i]; }
    int get_extra() { return Extra_run; }
    int get_ball(int i) { return p_ball[i]; }
    string get_t_name() { return team_name; }
    int get_Total();
    void Add_Run(int player_num, int run);
    void Set_Status(int player, int status) { p_status[player] = status; }
    void Set_Out(int out_player, int type, int new_player);
    void Set_Ball(int player) { p_ball[player]++; }
    void Set_Extra(int run) { Extra_run += run; }
};

Team::Team() {
    for (int i = 0; i < 12; i++) {
        p_name[i] = "Player" + to_string(i + 1);
        p_run[i] = 0;
        p_status[i] = 0;
        p_ball[i] = 0;
    }
    team_name = "INDIA";
    Extra_run = 0;
    p_num = 0;
}

int Team::Init() {
    cout << "Enter Team Name: ";
    cin >> team_name;
    cout << "No of players of the team: ";
    cin >> p_num;
    cout << "Enter Name of the Players.......\n";
    for (int i = 0; i < p_num; i++) {
        cout << "Player" << i + 1 << ": ";
        cin >> p_name[i];
        p_run[i] = 0;
        p_status[i] = 0;
        p_ball[i] = 0;
    }
    return p_num;
}

void Team::Add_Run(int player_num, int run) {
    p_run[player_num] += run;
}

int Team::get_Total() {
    int local_total = 0;
    for (int i = 0; i < p_num; i++) {
        local_total += p_run[i];
    }
    local_total += Extra_run;
    return local_total;
}

void Team::Set_Out(int out_player, int type, int new_player) {
    p_status[out_player] = type;
    p_status[new_player] = 1;
}

class myscore {
    int player1;
    int player2;
    int Ball_count;
    int Over;
    int Max_Over;
    int Out;
    int Max_out;
    Team team1;
    int extra;
public:
    myscore();
    void show();
    void ch();
    void dot_ball();
    void add_run();
    void wicket();
    void extra1();
    void over_complete();
};

myscore::myscore() {
    player1 = 0;
    player2 = 1;
    extra = 0;
    Over = 0;
    Out = 0;
    Max_out = 10;
    Ball_count = 0;
    Max_out = team1.Init();
    cout << "\nEnter no of Overs in one Innings: ";
    cin >> Max_Over;

    while (true) {
        cout << "\nChoose opening batsmen (0 to " << Max_out - 1 << ")\n";
        cout << "Batsman 1: ";
        cin >> player1;
        cout << "Batsman 2: ";
        cin >> player2;

        if (player1 >= 0 && player2 >= 0 && player1 < Max_out && player2 < Max_out && player1 != player2) {
            team1.Set_Status(player1, 1);
            team1.Set_Status(player2, 1);
            break;
        } else {
            cout << "Invalid input. Try again.\n";
        }
    }
}

void myscore::show() {
    cout << "\n\n//////////////////////////////////////////////////\n";
    cout << "                   " << team1.get_t_name() << " Score                     \n";
    cout << "//////////////////////////////////////////////////\n\n";

    for (int i = 0; i < Max_out; i++) {
        cout << team1.get_name(i) << "  -  ";
        cout << SHOW_STATUS(team1.get_status(i)) << "  ";
        cout << team1.get_run(i);
        if (team1.get_status(i)) cout << " (" << team1.get_ball(i) << ")";
        cout << endl;
    }

    cout << "\nExtra: " << team1.get_extra() << endl;
    cout << "--------------------------------------------------\n";
    cout << "Over " << Over << "." << Ball_count << "  Wickets " << Out;
    cout << " || Total Score: " << team1.get_Total() << "\n";

    if (Over < Max_Over && Out < Max_out) {
        ch();
    } else {
        cout << "\n\nInnings Complete\n";
    }
}

void myscore::ch() {
    int option;
    cout << "\nChoose option:\n";
    cout << "[1] Dot Ball\n[2] Add Run\n[3] Extra Run\n[4] Wicket\n[10] Exit\n> ";
    cin >> option;

    switch (option) {
        case 1: dot_ball(); break;
        case 2: add_run(); break;
        case 3: extra1(); break;
        case 4: wicket(); break;
        case 10: return;
        default:
            cout << "Invalid input. Try again.\n";
            ch();
    }
}

void myscore::dot_ball() {
    cout << "\nDot Ball\n";
    Ball_count++;
    team1.Set_Ball(player1);

    if (Ball_count == 6) {
        over_complete();
    } else {
        cin.ignore(); cin.get();
        show();
    }
}

void myscore::add_run() {
    cout << "\nEnter Runs: ";
    int runs;
    cin >> runs;
    Ball_count++;
    team1.Set_Ball(player1);
    team1.Add_Run(player1, runs);

    if (runs == 1 || runs == 3) {
        swap(player1, player2);
    }

    if (Ball_count == 6) {
        over_complete();
    } else {
        cin.ignore(); cin.get();
        show();
    }
}

void myscore::extra1() {
    cout << "\nEnter Extra Runs: ";
    cin >> extra;
    team1.Set_Extra(extra);
    cin.ignore(); cin.get();
    show();
}

void myscore::wicket() {
    int o_type, new_player;
    cout << "\nOut type? (1=Bold, 2=Caught, 3=Run Out): ";
    cin >> o_type;
    Out++;
    Ball_count++;
    team1.Set_Ball(player1);
    team1.Set_Status(player1, o_type + 1);

    if (Out >= Max_out) {
        cin.ignore(); cin.get();
        show();
        return;
    }

    cout << "New Batsman Number (0 to " << Max_out - 1 << "): ";
    cin >> new_player;

    while (new_player == player1 || new_player == player2 || new_player < 0 || new_player >= Max_out) {
        cout << "Invalid input. Try again: ";
        cin >> new_player;
    }

    team1.Set_Out(player1, o_type + 1, new_player);
    player1 = new_player;

    if (Ball_count == 6) {
        over_complete();
    } else {
        cin.ignore(); cin.get();
        show();
    }
}

void myscore::over_complete() {
    cout << "\nOver Complete\n";
    Over++;
    Ball_count = 0;
    swap(player1, player2);

    if (Over == Max_Over) {
        cout << "\nInnings Complete\n";
        cin.ignore(); cin.get();
        show();
    } else {
        cin.ignore(); cin.get();
        show();
    }
}

int main() {
    myscore MS;
    MS.show();
    return 0;
}
