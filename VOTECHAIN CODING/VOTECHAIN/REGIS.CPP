#include <iostream>
using namespace std;

class RegisterVoter {
private:
    string voterId;
    string voterInfo;
    string fingerprintTemplate;

public:
    void reg(string id, string info, string finger) {
        voterId = id;
        voterInfo = info;
        fingerprintTemplate = finger;
    }

    void display() {
        cout << "\nVoter Registered Successfully!" << endl;
        cout << "ID: " << voterId << endl;
        cout << "Info: " << voterInfo << endl;
        cout << "Fingerprint: " << fingerprintTemplate << endl;
    }
};
int main() {
    string a, b, c;
    cout << "Enter ID, Info and Fingerprint:\n";
    cin >> a >> b >> c;

    RegisterVoter obj;
    obj.reg(a, b, c);
    obj.display();

    return 0;
}