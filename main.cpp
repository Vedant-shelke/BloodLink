#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <cctype>
#include <limits>
using namespace std;

// Convert text to uppercase
string toUpperCase(string text) {
    for (char& c : text)
        c = toupper(c);
    return text;
}

// Validate YYYY-MM-DD
bool isValidDate(string date) {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7)
            continue;
        if (!isdigit(date[i]))
            return false;
    }
    try {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        if (year < 1900 || year > 2026)
            return false;
        if (month < 1 || month > 12)
            return false;
        if (day < 1 || day > 31)
            return false;
    }
    catch (...) {
        return false;
    }
    return true;
}

// Validate blood group
bool isValidBloodGroup(string group) {
    group = toUpperCase(group);
    return group == "A+" || group == "A-" ||
           group == "B+" || group == "B-" ||
           group == "AB+" || group == "AB-" ||
           group == "O+" || group == "O-";
}

// Base class
class Person {
protected:
    string name;
    string phone;
    string dateOfBirth;
    string bloodGroup;
public:
    Person(string name, string phone, string dateOfBirth, string bloodGroup)
        : name(name), phone(phone), dateOfBirth(dateOfBirth), bloodGroup(bloodGroup) {}
    string getName() const {
        return name;
    }
    string getPhone() const {
        return phone;
    }
    string getDateOfBirth() const {
        return dateOfBirth;
    }
    string getBloodGroup() const {
        return bloodGroup;
    }
};

// Donor class
class Donor : public Person {
private:
    string area;
    double weight;
    string lastDonationDate;
public:
    Donor(string name, string phone, string dateOfBirth, string bloodGroup,
          string area, double weight, string lastDonationDate)
        : Person(name, phone, dateOfBirth, bloodGroup),
          area(area), weight(weight), lastDonationDate(lastDonationDate) {}
    string getArea() const {
        return area;
    }
    double getWeight() const {
        return weight;
    }
    string getLastDonationDate() const {
        return lastDonationDate;
    }
    void display() const {
        cout << "Name          : " << name << "\n";
        cout << "Phone         : " << phone << "\n";
        cout << "Date of Birth : " << dateOfBirth << "\n";
        cout << "Blood Group   : " << bloodGroup << "\n";
        cout << "Area          : " << area << "\n";
        cout << "Weight        : " << weight << " kg\n";
        cout << "Last Donation : " << lastDonationDate << "\n";
    }
};

// Blood request class
class BloodRequest {
private:
    int requestId;
    string requesterName;
    string requiredBloodGroup;
    int units;
    string urgency;
    string area;
public:
    BloodRequest(int requestId, string requesterName, string requiredBloodGroup,
                 int units, string urgency, string area)
        : requestId(requestId), requesterName(requesterName),
          requiredBloodGroup(requiredBloodGroup), units(units),
          urgency(urgency), area(area) {}
    int getRequestId() const {
        return requestId;
    }
    string getRequesterName() const {
        return requesterName;
    }
    string getRequiredBloodGroup() const {
        return requiredBloodGroup;
    }
    int getUnits() const {
        return units;
    }
    string getUrgency() const {
        return urgency;
    }
    string getArea() const {
        return area;
    }
    void display() const {
        cout << "Request ID      : " << requestId << "\n";
        cout << "Requester       : " << requesterName << "\n";
        cout << "Required Group  : " << requiredBloodGroup << "\n";
        cout << "Units           : " << units << "\n";
        cout << "Urgency         : " << urgency << "\n";
        cout << "Area            : " << area << "\n";
    }
};

// Blood bank class
class BloodBank {
private:
    vector<Donor> donors;
    vector<BloodRequest> requests;
    unordered_map<string, vector<string>> compatibility;
    int nextRequestId;

    int calculateAge(string dateOfBirth) const {
        int birthYear = stoi(dateOfBirth.substr(0, 4));
        time_t currentTime = time(nullptr);
        tm* currentDate = localtime(&currentTime);
        int currentYear = currentDate->tm_year + 1900;
        return currentYear - birthYear;
    }

    int daysSinceDonation(string donationDate) const {
        int year = stoi(donationDate.substr(0, 4));
        int month = stoi(donationDate.substr(5, 2));
        int day = stoi(donationDate.substr(8, 2));
        tm donation = {};
        donation.tm_year = year - 1900;
        donation.tm_mon = month - 1;
        donation.tm_mday = day;
        time_t donationTime = mktime(&donation);
        time_t currentTime = time(nullptr);
        double difference = difftime(currentTime, donationTime);
        return static_cast<int>(difference / (60 * 60 * 24));
    }

    bool isEligible(const Donor& donor) const {
        int age = calculateAge(donor.getDateOfBirth());
        if (age < 18 || age > 65)
            return false;
        if (donor.getWeight() < 50)
            return false;
        if (daysSinceDonation(donor.getLastDonationDate()) < 56)
            return false;
        return true;
    }

    bool isCompatible(string requiredGroup, string donorGroup) const {
        auto it = compatibility.find(requiredGroup);
        if (it == compatibility.end())
            return false;
        for (const string& group : it->second) {
            if (group == donorGroup)
                return true;
        }
        return false;
    }

public:
    BloodBank() {
        nextRequestId = 1001;
        compatibility["O-"] = {"O-"};
        compatibility["O+"] = {"O-", "O+"};
        compatibility["A-"] = {"O-", "A-"};
        compatibility["A+"] = {"O-", "O+", "A-", "A+"};
        compatibility["B-"] = {"O-", "B-"};
        compatibility["B+"] = {"O-", "O+", "B-", "B+"};
        compatibility["AB-"] = {"O-", "A-", "B-", "AB-"};
        compatibility["AB+"] = {"O-", "O+", "A-", "A+", "B-", "B+", "AB-", "AB+"};
    }

    void addDonor(const Donor& donor) {
        donors.push_back(donor);
        cout << "\nDonor added successfully.\n";
    }

    void displayAllDonors() const {
        if (donors.empty()) {
            cout << "\nNo donors available.\n";
            return;
        }
        cout << "\n========== DONOR LIST ==========\n";
        for (size_t i = 0; i < donors.size(); i++) {
            cout << "\nDonor #" << i + 1 << "\n";
            donors[i].display();
            cout << "--------------------------------\n";
        }
    }

    BloodRequest createRequest(string requesterName, string bloodGroup,
                               int units, string urgency, string area) {
        bloodGroup = toUpperCase(bloodGroup);
        if (!isValidBloodGroup(bloodGroup))
            throw invalid_argument("Invalid blood group.");
        if (units <= 0)
            throw invalid_argument("Number of units must be greater than 0.");
        urgency = toUpperCase(urgency);
        if (urgency != "HIGH" && urgency != "MEDIUM" && urgency != "LOW")
            throw invalid_argument("Invalid urgency level.");
        BloodRequest request(nextRequestId, requesterName, bloodGroup,
                             units, urgency, area);
        nextRequestId++;
        requests.push_back(request);
        return request;
    }

    vector<Donor> findMatchingDonors(const BloodRequest& request) const {
        vector<Donor> matches;
        for (const Donor& donor : donors) {
            if (!isCompatible(request.getRequiredBloodGroup(),
                              donor.getBloodGroup()))
                continue;
            if (!isEligible(donor))
                continue;
            matches.push_back(donor);
        }
        sort(matches.begin(), matches.end(),
             [](const Donor& a, const Donor& b) {
                 return a.getArea() < b.getArea();
             });
        return matches;
    }

    void displayMatchingDonors(const BloodRequest& request) const {
        vector<Donor> matches = findMatchingDonors(request);
        cout << "\n=====================================\n";
        cout << "          MATCHING DONORS\n";
        cout << "=====================================\n";
        cout << "\nRequest ID     : " << request.getRequestId() << "\n";
        cout << "Required Group : " << request.getRequiredBloodGroup() << "\n";
        cout << "Urgency        : " << request.getUrgency() << "\n";
        cout << "Units          : " << request.getUnits() << "\n";
        cout << "Area           : " << request.getArea() << "\n";
        if (matches.empty()) {
            cout << "\nNo eligible matching donors found.\n";
            return;
        }
        cout << "\nFound " << matches.size() << " suitable donor(s).\n";
        for (size_t i = 0; i < matches.size(); i++) {
            cout << "\nMatch #" << i + 1 << "\n";
            matches[i].display();
            cout << "-------------------------------------\n";
        }
    }

    void displayRequests() const {
        if (requests.empty()) {
            cout << "\nNo blood requests found.\n";
            return;
        }
        cout << "\n========== REQUEST HISTORY ==========\n";
        for (const BloodRequest& request : requests) {
            request.display();
            cout << "-------------------------------------\n";
        }
    }

    void saveDonorsToFile() const {
        ofstream file("data/donors.txt");
        if (!file)
            throw runtime_error("Unable to open donors.txt");
        for (const Donor& donor : donors) {
            file << donor.getName() << "|";
            file << donor.getPhone() << "|";
            file << donor.getDateOfBirth() << "|";
            file << donor.getBloodGroup() << "|";
            file << donor.getArea() << "|";
            file << donor.getWeight() << "|";
            file << donor.getLastDonationDate() << "\n";
        }
        file.close();
    }

    void loadDonorsFromFile() {
        ifstream file("data/donors.txt");
        if (!file)
            return;
        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;
            try {
                stringstream ss(line);
                string name, phone, dob, bloodGroup;
                string area, weightString, lastDonation;
                getline(ss, name, '|');
                getline(ss, phone, '|');
                getline(ss, dob, '|');
                getline(ss, bloodGroup, '|');
                getline(ss, area, '|');
                getline(ss, weightString, '|');
                getline(ss, lastDonation, '|');
                double weight = stod(weightString);
                bloodGroup = toUpperCase(bloodGroup);
                if (!isValidDate(dob) ||
                    !isValidBloodGroup(bloodGroup) ||
                    !isValidDate(lastDonation))
                    throw invalid_argument("Invalid donor data.");
                donors.push_back(Donor(name, phone, dob, bloodGroup,
                                       area, weight, lastDonation));
            }
            catch (const exception& e) {
                cout << "\nSkipping invalid donor record: "
                     << e.what() << "\n";
            }
        }
        file.close();
    }

    void saveRequestsToFile() const {
        ofstream file("data/requests.txt");
        if (!file)
            throw runtime_error("Unable to open requests.txt");
        for (const BloodRequest& request : requests) {
            file << request.getRequestId() << "|";
            file << request.getRequesterName() << "|";
            file << request.getRequiredBloodGroup() << "|";
            file << request.getUnits() << "|";
            file << request.getUrgency() << "|";
            file << request.getArea() << "\n";
        }
        file.close();
    }

    void loadRequestsFromFile() {
        ifstream file("data/requests.txt");
        if (!file)
            return;
        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;
            try {
                stringstream ss(line);
                string idString, requesterName, bloodGroup;
                string unitsString, urgency, area;
                getline(ss, idString, '|');
                getline(ss, requesterName, '|');
                getline(ss, bloodGroup, '|');
                getline(ss, unitsString, '|');
                getline(ss, urgency, '|');
                getline(ss, area, '|');
                int id = stoi(idString);
                int units = stoi(unitsString);
                bloodGroup = toUpperCase(bloodGroup);
                if (!isValidBloodGroup(bloodGroup))
                    throw invalid_argument("Invalid blood group.");
                requests.push_back(BloodRequest(id, requesterName,
                                                bloodGroup, units,
                                                urgency, area));
                if (id >= nextRequestId)
                    nextRequestId = id + 1;
            }
            catch (const exception& e) {
                cout << "\nSkipping invalid request record: "
                     << e.what() << "\n";
            }
        }
        file.close();
    }
};

// Main function
int main() {
    try {
        BloodBank bloodBank;
        bloodBank.loadDonorsFromFile();
        bloodBank.loadRequestsFromFile();
        int choice;
        do {
            cout << "\n=====================================\n";
            cout << "          BLOODLINK SYSTEM\n";
            cout << "=====================================\n";
            cout << "1. Register Donor\n";
            cout << "2. View Donors\n";
            cout << "3. Create Blood Request & Find Donors\n";
            cout << "4. View Request History\n";
            cout << "5. Exit\n";
            cout << "\nEnter your choice: ";
            cin >> choice;
            try {
                if (choice == 1) {
                    string name, phone, dob, bloodGroup;
                    string area, lastDonation;
                    double weight;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nEnter name: ";
                    getline(cin, name);
                    cout << "Enter phone: ";
                    getline(cin, phone);
                    while (true) {
                        cout << "Enter date of birth (YYYY-MM-DD): ";
                        getline(cin, dob);
                        if (isValidDate(dob))
                            break;
                        cout << "Invalid date. Please enter YYYY-MM-DD.\n";
                    }
                    while (true) {
                        cout << "Enter blood group: ";
                        getline(cin, bloodGroup);
                        bloodGroup = toUpperCase(bloodGroup);
                        if (isValidBloodGroup(bloodGroup))
                            break;
                        cout << "Invalid blood group. Use A+, A-, B+, B-, "
                             << "AB+, AB-, O+ or O-.\n";
                    }
                    cout << "Enter area: ";
                    getline(cin, area);
                    while (true) {
                        cout << "Enter weight: ";
                        if (cin >> weight && weight >= 50)
                            break;
                        cout << "Invalid weight. Minimum weight is 50 kg.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (true) {
                        cout << "Enter last donation date (YYYY-MM-DD): ";
                        getline(cin, lastDonation);
                        if (isValidDate(lastDonation))
                            break;
                        cout << "Invalid date. Please enter YYYY-MM-DD.\n";
                    }
                    Donor donor(name, phone, dob, bloodGroup, area,
                                weight, lastDonation);
                    bloodBank.addDonor(donor);
                    bloodBank.saveDonorsToFile();
                }
                else if (choice == 2) {
                    bloodBank.displayAllDonors();
                }
                else if (choice == 3) {
                    string requesterName, bloodGroup, urgency, area;
                    int units;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nEnter requester name: ";
                    getline(cin, requesterName);
                    while (true) {
                        cout << "Enter required blood group: ";
                        getline(cin, bloodGroup);
                        bloodGroup = toUpperCase(bloodGroup);
                        if (isValidBloodGroup(bloodGroup))
                            break;
                        cout << "Invalid blood group. Use A+, A-, B+, B-, "
                             << "AB+, AB-, O+ or O-.\n";
                    }
                    while (true) {
                        cout << "Enter required units: ";
                        if (cin >> units && units > 0)
                            break;
                        cout << "Invalid units. Enter a number greater than 0.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (true) {
                        cout << "Enter urgency (HIGH/MEDIUM/LOW): ";
                        getline(cin, urgency);
                        urgency = toUpperCase(urgency);
                        if (urgency == "HIGH" ||
                            urgency == "MEDIUM" ||
                            urgency == "LOW")
                            break;
                        cout << "Invalid urgency. Enter HIGH, MEDIUM or LOW.\n";
                    }
                    cout << "Enter area: ";
                    getline(cin, area);
                    BloodRequest request = bloodBank.createRequest(
                        requesterName, bloodGroup, units, urgency, area);
                    bloodBank.saveRequestsToFile();
                    cout << "\n=====================================\n";
                    cout << "      REQUEST CREATED SUCCESSFULLY\n";
                    cout << "=====================================\n";
                    cout << "Request ID : " << request.getRequestId() << "\n";
                    cout << "Requester  : " << request.getRequesterName() << "\n";
                    cout << "Blood Group: " << request.getRequiredBloodGroup() << "\n";
                    cout << "Units      : " << request.getUnits() << "\n";
                    cout << "Urgency    : " << request.getUrgency() << "\n";
                    cout << "Area       : " << request.getArea() << "\n";
                    bloodBank.displayMatchingDonors(request);
                }
                else if (choice == 4) {
                    bloodBank.displayRequests();
                }
                else if (choice == 5) {
                    cout << "\nThank you for using BloodLink.\n";
                }
                else {
                    cout << "\nInvalid choice.\n";
                }
            }
            catch (const exception& e) {
                cout << "\nInput/processing error: "
                     << e.what() << "\n";
            }
        } while (choice != 5);
    }
    catch (const exception& e) {
        cout << "\nSystem Error: " << e.what() << "\n";
    }
    return 0;
}