#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct Subject {
	string code;
	string name;
	double creditHour;

	Subject() {
		code = "NA";
		name = "NA";
		creditHour = -1;
	}
	Subject(string Code, string Name, double CreditHour) {
		code = Code;
		name = Name;
		creditHour = CreditHour;
	}
};

struct Grade {
	Subject subject;
	string grade;
	double point;

	Grade() {
		grade = "NA";
		point = -1;
	}
	Grade(string Grade, double gpa) {
		grade = Grade;
		point = gpa;
	}
};

struct Student {
	string id;
	string name;
	Grade grades[6];

	Student() {
		id = "NA";
		name = "NA";
	}
	Student(string ID, string Name) {
		id = ID;
		name = Name;
	}
};

struct Teacher {
	string id;
	string name;
	Subject subjectAssigned;

	Teacher() {
		id = "NA";
		name = "NA";
	}
	Teacher(string ID, string Name) {
		id = ID;
		name = Name;
	}
};

void createMainMenu(Subject[], Student[], Teacher[], const int, const int, const int);
void createAdminMenu(Subject[], Student[], Teacher[], const int, const int, const int);
void createTeacherMenu(Subject[], Student[], Teacher[], const int, const int, const int);

void manageSubjects(Subject[], Student[], const int, const int);
void manageTeachers(Subject[], Teacher[], const int, const int);
void manageStudents(Subject[], Student[], const int, const int);

void viewCurrentSubjects(Subject[], const int);
void viewCurrentStudents(Student[], const int);
void viewCurrentTeachers(Teacher currentTeachers[], const int MAX_TEACHER);
void viewCurrentStudentIdAndName(Student[], const int);
void viewAStudent(Student);
void viewSubjectReport(Student[], string, const int);

void addSubject(Subject[], const int);
void addStudent(Subject[], Student[], const int, const int);
void addTeacher(Subject[], Teacher[], const int, const int);

void removeStudent(Student[], const int);
void removeSubject(Subject[], Student[], const int, const int);
void removeTeacher(Teacher[], const int);

void addSubjectToAStudent(Student[], Subject[], const int, const int);
void getSubjectsToBeAdded(Subject[], Student&, const int);
void removeSubjectFromAStudent(Student[], Subject[], const int, const int);
void getSubjectsToBeRemoved(Student& student);
void assignSubjectToTeacher(Subject[], Teacher[], const int, const int, const int);

void gradeStudents(Student[], string, const int);
void getStudentGrade(Student&, int);
void editStudentGrade(Student[], string, const int);

double getStudentGPA(Student);
void generateStudentReport(Student[], const int);
void generateReport(Subject[], Student[], const int, const int);
void generateSubjectReport(Subject[], Student[], const int, const int);

void exportStudentReport(Subject[], Student[], const int, const int);
void exportSubjectReport(Student[], string, const int);

int findTargetInStudentArray(Student[], string, const int);
int findTargetInSubjectArray(Subject[], string, const int);
int findTargetInTeacherArray(Teacher[], string, const int);
int findTargetInGradeArray(Grade[], string);

bool checkEmptySubjectArray(Subject[], const int);
bool checkEmptyStudentArray(Student[], const int);
bool checkEmptyTeacherArray(Teacher[], const int);
bool checkEmptyGradesArray(Grade[]);
bool checkSubjectIsAssigned(Teacher[], string, const int);
int verifyTeacherExistence(Teacher[], const int);

void promptInputFromUser(string, double&);
void promptInputFromUser(string, int&);
bool promptYesOrNoFromUser(string);

void centerString(string);
void displayBanner(string);
void pause();

int main() {
	//Data is provided to the system to demonstrate features of the system.
	const int MAX_SUBJECT = 10, MAX_STUDENT = 50, MAX_TEACHER = MAX_SUBJECT;

	Subject subjectsAvailable[MAX_SUBJECT] = {
		//Creating some default subjects
		Subject("UCCD 1004","PROGRAMMING CONCEPTS AND PRACTICES",4.0),
		Subject("UCCD 1013","ANALYSIS AND DESIGN OF INFORMATION SYSTEMS",3.0),
		Subject("UCCM 1153","INTRODUCTION TO CALCULUS AND APPLICATION",3.0),
		Subject("UCCN 1004","DATA COMMUNICATION AND NETWORKING",4.0),
		Subject("UCCD 1143","PROBABILITY AND STATISTICS FOR COMPUTING",3.0),
		Subject("UCCN 3053","INFORMATION TECHNOLOGY PROFESSIONAL ETHICS",3.0),
		Subject("UCCM 1353","BASIC ALGEBRA",3.0)
	};

	Student currentStudents[MAX_STUDENT] = {
		//Creating some default students
		Student("2200001", "CAROL LEE"),
		Student("2200002", "TEOH YUAN KAI"),
		Student("2200003", "ONG YEE SONG"),
		Student("2200004", "TANG YI MIN"),
		Student("2200005", "CHEW KWOK YUAN")
	};

	Teacher currentTeachers[MAX_TEACHER] = {
		//Creating some default teachers
		Teacher("100001", "ALBERT LIU"),
		Teacher("100002", "RIZAN"),
		Teacher("100003", "YEW GIM LAY")
	};

	currentTeachers[0].subjectAssigned = subjectsAvailable[0];
	currentTeachers[1].subjectAssigned = subjectsAvailable[1];
	currentTeachers[2].subjectAssigned = subjectsAvailable[2];

	currentStudents[0].grades[0].subject = subjectsAvailable[0];
	currentStudents[0].grades[1].subject = subjectsAvailable[1];
	currentStudents[0].grades[2].subject = subjectsAvailable[2];
	currentStudents[0].grades[0].grade = "A+";
	currentStudents[0].grades[1].grade = "A-";
	currentStudents[0].grades[2].grade = "B ";
	currentStudents[0].grades[0].point = 4.00;
	currentStudents[0].grades[1].point = 3.67;
	currentStudents[0].grades[2].point = 3.00;

	currentStudents[1].grades[0].subject = subjectsAvailable[3];
	currentStudents[1].grades[1].subject = subjectsAvailable[2];
	currentStudents[1].grades[2].subject = subjectsAvailable[4];
	currentStudents[1].grades[0].grade = "B ";
	currentStudents[1].grades[1].grade = "B ";
	currentStudents[1].grades[2].grade = "B ";
	currentStudents[1].grades[0].point = 3.00;
	currentStudents[1].grades[1].point = 3.00;
	currentStudents[1].grades[2].point = 3.00;

	createMainMenu(subjectsAvailable, currentStudents, currentTeachers, MAX_SUBJECT, MAX_STUDENT, MAX_TEACHER);
	cout << "Thank you for using the system" << endl;
	pause();

	return 0;
}

/*Error Handling Functions************************************************************/
void promptInputFromUser(string promptString, int& var) {
	/*Func Des	: This function will display a prompt string, and then require user to provide an int type input. The function will handle the error by using cin.fail() and cin.clear() to keep the program running without error. cin.ignore() is used to clear the buffer. As a result, the program can use the getline() function anywhere without getting possible error. Notice that reference paramter is used here, a direct modification will be made to the given parameter var*/
	cout << promptString;
	cin >> var;
	if (cin.fail()) {
		cin.clear();

	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void promptInputFromUser(string promptString, double& var) {
	/*Func Des	: This is an overloaded function that takes double type input.The detail description of this function can be found at promptInputFromUser that takes int type parameter.*/
	cout << promptString;
	cin >> var;
	if (cin.fail()) {
		cin.clear();
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause() {
	/*Func Des	: This function is a replacement for system("PAUSE"), it will wait for user to press ENTER, before proceeding to the next section of program. Note that this function works when there's nothing else in the buffer; hence we need to ensure that the buffer is empty before calling this function. Incidentally, if the user tries to press anything apart from ENTER, this function will also ignore it as the buffer will be cleaned.*/
	cout << "Press ENTER to continue";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
/*Helper functions********************************************************************/
int findTargetInSubjectArray(Subject subjectArray[], string target, const int MAX_ITERATION) {
	/*Func Des	: This function check whether the target string, for example subject code, given by user is available in the given Subject array.It will return the position of target string resides, and if the target string does not exist in the given Subject array, it will return -1*/
	for (int i = 0; i < MAX_ITERATION; i++) {
		if (subjectArray[i].code == target) {
			return i;
		}
	}
	return -1;
}

int findTargetInStudentArray(Student studentArray[], string target, const int MAX_ITERATION) {
	/*Func Des	: This function check whether the target string, for example student id, given by user is available in the given Student array.It will return the position of target string resides, and if the target string does not exist in the given Student array, it will return -1*/
	for (int i = 0; i < MAX_ITERATION; i++) {
		if (studentArray[i].id == target) {
			return i;
		}
	}
	return -1;
}

int findTargetInGradeArray(Grade studentGrades[], string target) {
	/*Func Des	: This function check whether the target string, for example subject code, given by user is available in the given Grade array.It will return the position of target string resides and if the target string does not exist in the given Grade array, it will return -1*/
	for (int i = 0; i < 6; i++) {
		if (studentGrades[i].subject.code == target) {
			return i;
		}
	}
	return -1;
}

int findTargetInTeacherArray(Teacher teacherArray[], string target, const int MAX_ITERATION) {
	/*Func Des	: This function check whether the target string, for example teacher id, given by use is available in the given Teacher array.It will return the position of target string resides, and if the target string does not exist in the given Teacher array, it will return -1*/
	for (int i = 0; i < MAX_ITERATION; i++) {
		if (teacherArray[i].id == target) {
			return i;
		}
	}
	return -1;
}

bool checkEmptySubjectArray(Subject subjectArray[], const int MAX_ITERATION) {
	/*Func Des	: This function check whether the given subjectArray is all empty. If the given subject array, is not all empty, it will return false. If the subject array is full of empty values, it will return true.*/
	bool empty = true;
	for (int i = 0; i < MAX_ITERATION; i++) {
		if (subjectArray[i].code != "NA") {
			empty = false;
			break;
		}
	}
	return empty;
}

bool checkEmptyStudentArray(Student studentArray[], const int MAX_ITERATION) {
	/*Func Des	: This function check whether the given studentArray is all empty. If the given student array, is not all empty, it will return false. If the student array is full of empty values, it will return true.*/
	bool empty = true;
	for (int i = 0; i < MAX_ITERATION; i++) {
		if (studentArray[i].id != "NA") {
			empty = false;
			break;
		}
	}
	return empty;
}

bool checkEmptyTeacherArray(Teacher teacherArray[], const int MAX_ITERATION) {
	/*Func Des	: This function check whether the given teacherArray is all empty. If the given teacher array, is not all empty, it will return false. If the teacher array is full of empty values, it will return true.*/
	bool empty = true;
	for (int i = 0; i < MAX_ITERATION; i++) {
		if (teacherArray[i].id != "NA") {
			empty = false;
		}
	}
	return empty;
}

bool checkEmptyGradesArray(Grade studentGrades[]) {
	/*Func Des	: This function check whether the given Grade array is all empty. If the given Grade array, is not all empty, it will return false. If the teacher array is full of empty values, it will return true.*/
	bool empty = true;
	for (int i = 0; i < 6; i++) {
		if (studentGrades[i].subject.code != "NA") {
			empty = false;
			break;
		}
	}
	return empty;
}

bool checkSubjectIsAssigned(Teacher currentTeachers[], string subjectCode, const int MAX_TEACHER) {
	/*Func Des	: This function check whether the given subject is already assigned to other teacher. If the subject is already assigned, it will return true*/
	bool isAssigned = false;
	for (int i = 0; i < MAX_TEACHER; i++) {
		if (currentTeachers[i].subjectAssigned.code == subjectCode) {
			isAssigned = true;
			break;
		}
	}
	return isAssigned;
}
/*Functions for validation purposes********************************************************/
int verifyTeacherExistence(Teacher currentTeachers[], const int MAX_TEACHER) {
	/*Func Des	: This function ensure that only authorized teachers can manage student grades.The teacher is required to provide his id first before performing any actions in the teacher panel. The entered id will be verified via findTargetInTeacherArray(), if the entered id exists, then the user will be direct to teacher panel. Incidentally, the teacher can only perform actions related to his subject*/
	bool stop = false;
	int teacherIndex;
	while (!stop) {
		string teacherID;
		cout << "\nEnter Teacher ID (Press STOP to terminate): ";
		getline(cin, teacherID);
		if (teacherID == "STOP") {
			teacherIndex = -1;
			stop = true;
		}
		else {
			teacherIndex = findTargetInTeacherArray(currentTeachers, teacherID, MAX_TEACHER);
			if (teacherIndex == -1) {
				cout << "Teacher ID " << teacherID << " does not exist!\a" << endl;
			}
			else {
				stop = true;
			}
		}
	}
	return teacherIndex;
}
/*Functions for decoration purpose******************************************************/
void centerString(string stringCentered) {
	/*Func Des	: This function will print the given string on the center of terminal. It works by assuming the width of terminal is 115, and use this value to subtract the length of given string. The obatained value will then devided by 2, and be considered as the padding, which in simple word, the white space needed before printing the string.*/
	const int TERMINAL_WIDTH = 115;
	int padding = (TERMINAL_WIDTH - stringCentered.length()) / 2;
	cout << setw(padding + stringCentered.length()) << stringCentered << endl;
}

void displayBanner(string currentPanel) {
	/*Func Des	: This function displays the header of each panel*/
	system("cls");
	cout << endl;
	centerString("UTAR Grading System");
	centerString("Faculty of Information and Communication Technology");
	centerString("Academic Year 2023");
	centerString(currentPanel);
	return;
}
/*Functions that create panels************************************************************/
void createMainMenu(Subject currentSubjects[], Student currentStudents[], Teacher currentTeachers[], const int MAX_SUBJECT, const int MAX_STUDENT, const int MAX_TEACHER) {
	//Func Des	: This function allows the user to decide whether to use the grading system as an admin or a teacher.
	bool stop = false;
	do {
		int operation;
		displayBanner("Main Menu");
		centerString("Please select an option: ");
		centerString("1. Admin             ");
		centerString("2. Teacher           ");
		centerString("3. Terminate Program ");
		promptInputFromUser("Enter an operation: ", operation);
		switch (operation) {
		case 1:
			createAdminMenu(currentSubjects, currentStudents, currentTeachers, MAX_SUBJECT, MAX_STUDENT, MAX_TEACHER);
			pause();
			break;
		case 2:
			createTeacherMenu(currentSubjects, currentStudents, currentTeachers, MAX_SUBJECT, MAX_STUDENT, MAX_TEACHER);//added on 15.4.2023
			pause();
			break;
		case 3:
			stop = true;
			break;
		default:
			cout << "Invalid Input!\a" << endl;
			pause();
		}
	} while (!stop);
	return;
}

void createAdminMenu(Subject currentSubjects[], Student currentStudents[], Teacher currentTeachers[], const int MAX_SUBJECT, const int MAX_STUDENT, const int MAX_TEACHER) {
	//Func Des	: This function provide operations available as an admin.
	bool stop = false;
	do {
		int operation;
		displayBanner("Admin Panel");
		centerString("Please select an option:");
		centerString("1. Manage Subjects         ");
		centerString("2. Manage Teachers         ");
		centerString("3. Manage Students         ");
		centerString("4. Generate Report         ");
		centerString("5. Export Report of Student");
		centerString("6. Back to Main Menu       ");
		promptInputFromUser("Enter an operation: ", operation);
		switch (operation) {
		case 1:
			manageSubjects(currentSubjects, currentStudents, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 2:
			manageTeachers(currentSubjects, currentTeachers, MAX_SUBJECT, MAX_TEACHER);
			break;
		case 3:
			manageStudents(currentSubjects, currentStudents, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 4:
			generateReport(currentSubjects, currentStudents, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 5:
			exportStudentReport(currentSubjects, currentStudents, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 6:
			stop = true;
			break;
		default:
			cout << "Invalid Input!\a" << endl;
			pause();
		}
	} while (!stop);
	return;
}

void createTeacherMenu(Subject subjectsAvailable[], Student currentStudents[], Teacher currentTeachers[], const int MAX_SUBJECT, const int MAX_STUDENT, const int MAX_TEACHER) {
	//Func Des	: This function provides operations available as a teacher.
	int teacherIndex = verifyTeacherExistence(currentTeachers, MAX_TEACHER);
	if (teacherIndex != -1) {
		bool stop = false;
		while (!stop) {
			int choice;
			displayBanner("Teacher Panel - " + currentTeachers[teacherIndex].name);
			centerString("Please select an option:");
			centerString("1. View Subject Report  ");
			centerString("2. Grade Students       ");
			centerString("3. Edit Student Grade   ");
			centerString("4. Export Subject Report");
			centerString("5. Back to Main Menu    ");
			promptInputFromUser("Enter an operation: ", choice);
			switch (choice) {
			case 1:
				viewSubjectReport(currentStudents, currentTeachers[teacherIndex].subjectAssigned.code, MAX_STUDENT);
				pause();
				break;
			case 2:
				gradeStudents(currentStudents, currentTeachers[teacherIndex].subjectAssigned.code, MAX_STUDENT);
				pause();
				break;
			case 3:
				editStudentGrade(currentStudents, currentTeachers[teacherIndex].subjectAssigned.code, MAX_STUDENT);
				pause();
				break;
			case 4:
				exportSubjectReport(currentStudents, currentTeachers[teacherIndex].subjectAssigned.code, MAX_STUDENT);
				pause();
				break;
			case 5:
				stop = true;
				break;
			default:
				cout << "Invalid Input!\a" << endl;
				pause();
			}
		}
	}
	return;
}

/****Functions in admin panel********************************************************/
void manageSubjects(Subject currentSubjects[], Student currentStudents[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	//Func Des	: This function displays operations that the Manage Subjects feature of admin.
	bool stop = false;
	do {
		int operation;
		displayBanner("Admin Panel - Manage Subjects");
		centerString("Operations available: ");
		centerString("1. View current subjects");
		centerString("2. Add subject          ");
		centerString("3. Remove subject       ");
		centerString("4. Back to admin panel  ");
		promptInputFromUser("Enter an operation: ", operation);
		switch (operation) {
		case 1:
			viewCurrentSubjects(currentSubjects, MAX_SUBJECT);
			pause();
			break;
		case 2:
			addSubject(currentSubjects, MAX_SUBJECT);
			pause();
			break;
		case 3:
			removeSubject(currentSubjects, currentStudents, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 4:
			stop = true;
			break;
		default:
			cout << "Invalid Input!\a" << endl;
			pause();
		}
	} while (!stop);
	return;
}

void manageTeachers(Subject currentSubjects[], Teacher currentTeachers[], const int MAX_SUBJECT, const int MAX_TEACHER) {
	//Func Des	: This function displays operations that the Manage Teachers feature of admin.
	bool stop = false;
	while (!stop) {
		int op;
		displayBanner("Admin Panel - Manage Teachers");
		centerString("Operations available : ");
		centerString("1. View current teachers");
		centerString("2. Add teacher          ");
		centerString("3. Remove teacher       ");
		centerString("4. Back to admin panel  ");
		promptInputFromUser("Enter an operation: ", op);
		switch (op) {
		case 1:
			viewCurrentTeachers(currentTeachers, MAX_TEACHER);
			pause();
			break;
		case 2:
			addTeacher(currentSubjects, currentTeachers, MAX_SUBJECT, MAX_TEACHER);
			pause();
			break;
		case 3:
			removeTeacher(currentTeachers, MAX_TEACHER);
			pause();
			break;
		case 4:
			stop = true;
			break;
		default:
			cout << "Invalid Input!\a" << endl;
			pause();

		}
	}
	return;
}

void manageStudents(Subject subjectsAvailable[], Student currentStudents[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	//Func Des	: This function display operations that the Manage Students feature of admin.
	bool stop = false;
	do {
		int operation;
		displayBanner("Admin Panel - Manage Students");
		centerString("Operations available : ");
		centerString("1. View current students        ");
		centerString("2. Add student                  ");
		centerString("3. Remove student               ");
		centerString("4. Add subject to a student     ");
		centerString("5. Remove subject from a student");
		centerString("6. Back to admin panel          ");
		promptInputFromUser("Enter an operation: ", operation);
		switch (operation) {
		case 1:
			viewCurrentStudents(currentStudents, MAX_STUDENT);
			pause();
			break;
		case 2:
			addStudent(subjectsAvailable, currentStudents, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 3:
			removeStudent(currentStudents, MAX_STUDENT);
			pause();
			break;
		case 4:
			addSubjectToAStudent(currentStudents, subjectsAvailable, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 5:
			removeSubjectFromAStudent(currentStudents, subjectsAvailable, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 6:
			stop = true;
			break;
		default:
			cout << "Invalid Input!\a" << endl;
			pause();
		}
	} while (!stop);
	return;
}

void generateReport(Subject currentSubjects[], Student currentStudents[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	//Func Des	: This function display what kind of report the system can generate
	bool stop = false;
	do {
		int operation;
		displayBanner("Admin Panel-Generate Report");
		centerString("Operations available : ");
		centerString("1. Generate Report of a Student");
		centerString("2. Generate Report of a Subject");
		centerString("3. Back to admin panel         ");
		promptInputFromUser("Enter an operation: ", operation);
		switch (operation) {
		case 1:
			generateStudentReport(currentStudents, MAX_STUDENT);
			pause();
			break;
		case 2:
			generateSubjectReport(currentSubjects, currentStudents, MAX_SUBJECT, MAX_STUDENT);
			pause();
			break;
		case 3:
			stop = true;
			break;
		default:
			cout << "Invalid Input!\a" << endl;
			pause();
		}
	} while (!stop);
	return;
}

void exportStudentReport(Subject subjectsArray[], Student currentStudents[], const int MAX_ITERATION, const int MAX_STUDENT) {
	/*Func Des	: The function will first check whether there are available students; if no, the function will terminate. Then, it will require the user to enter student id; the entered id will be validated via findTargetInStudentArray(). If the entered student id is valid, the information of the student will be exported to a txt file entered by user. Incidentally, user needs to authorize this program to export report.*/
	viewCurrentStudentIdAndName(currentStudents, MAX_STUDENT);
	if (checkEmptyStudentArray(currentStudents, MAX_STUDENT)) {
		cout << "No students available!\a" << endl;
	}
	else {
		bool stop = false;
		do {
			string id;
			int studentIndex;
			cout << "Please input the ID of student you would like to generate report of: ";
			getline(cin, id);
			studentIndex = findTargetInStudentArray(currentStudents, id, MAX_STUDENT);
			if (studentIndex == -1) {
				cout << "Student not Found!\a\n" << endl;
			}
			else {
				ofstream outFile;
				char fileLocation[101];
				cout << "Note that you must provide authorization for this program to export file.\n" << endl;
				cout << "Enter a file location (e.g., D:\\\\UTAR\\\\Y1S2\\\\subjectReport.txt):";
				cin.getline(fileLocation, 100);
				outFile.open(fileLocation, ios::trunc);
				if (!outFile.is_open()) {
					cout << "Invalid file location!\a" << endl;
				}
				else {
					double GPA = getStudentGPA(currentStudents[studentIndex]);
					outFile << "                           STUDENT REPORT              \n" << endl;
					outFile << "Student ID	:  " << currentStudents[studentIndex].id << endl;
					outFile << endl;
					outFile << "Student Name: " << currentStudents[studentIndex].name << endl;
					outFile << endl;
					for (int i = 0; i < 6; i++) {
						if (currentStudents[studentIndex].grades[i].grade != "NA") {
							outFile << "\tCode		:  " << currentStudents[studentIndex].grades[i].subject.code << endl;
							outFile << "\tSubject	:  " << currentStudents[studentIndex].grades[i].subject.name << endl;
							outFile << "\tGrade		:  " << currentStudents[studentIndex].grades[i].grade << endl;
							outFile << "\tPoint		:  " << fixed << setprecision(2) << currentStudents[studentIndex].grades[i].point << endl;
							outFile << endl;
						}
					}
					outFile << "GPA		: " << to_string(GPA) << endl;
					outFile.close();
					cout << "Student Report has been generated in txt file....." << endl;
					stop = true;
				}
			}
		} while (!stop);
	}
	return;
}
/*Functions in manage subjects*********************************************************/
void viewCurrentSubjects(Subject subjectsArray[], const int MAX_ITERATION) {
	//Func Des	: This function allows user to view subjects in a given subject array
	cout << endl;
	centerString("Subjects Available for CS Students in Academic Year 2023");
	cout << left << "\t" << setw(6) << "No" << setw(20) << "CODE" << setw(70) << "NAME" << setw(10) << "CREDIT HOUR" << endl;
	for (int i = 0; i < MAX_ITERATION; i++) {
		cout << "\t" << setw(5) << left << i + 1 << ": ";
		cout << setw(20) << left << subjectsArray[i].code;
		cout << setw(70) << left << subjectsArray[i].name;
		cout << setw(10) << right << fixed << setprecision(2) << subjectsArray[i].creditHour << endl;
	}
	return;
}

void addSubject(Subject subjectArray[], const int MAX_SUBJECT) {
	/*Func Des	: This function fist check whether the given array still has empty slot by using findTargetInSubject();  if findTargetInSubject() return -1, which indicates there is no more empty slot in given array, this function will notify user there is no more empty slot and then terminate. Besides, this function has error handling features; it will prompt error to user if the user tries to give invalid input. Subject code & subject name given by user cannot equal to 0 character and cannot be greater than 20 and 70 characters respectively. If the user try to input non-double value for credit hour, this function will also handle the invalid input by using promptInputFromUser(). Furthermore, if the user inputs are all valid, this function will then ensure that the subject code is not used previously; if the subject code already exists, it will tell the user. This functon will continue looping until the user provides the valid input (if the given array is not full). */
	viewCurrentSubjects(subjectArray, MAX_SUBJECT);
	int emptySlot = findTargetInSubjectArray(subjectArray, "NA", MAX_SUBJECT);
	if (emptySlot == -1) {
		cout << "Cannot add subject anymore! (0 remaining empty slot)" << endl;
	}
	else {
		bool validInput = false;
		do {
			string subjectCode, subjectName;
			double subjectCreditHour = 0;
			cout << "\nSubject code (max 20 characters): ";
			getline(cin, subjectCode);
			cout << "Subject name (max 70 characters): ";
			getline(cin, subjectName);
			promptInputFromUser("Credit hour                     : ", subjectCreditHour);
			if (subjectCode.length() > 20 || subjectName.length() > 70 || subjectCode.length() == 0 || subjectName.length() == 0 || subjectCreditHour <= 0 || subjectCreditHour > 4) {
				cout << "Invalid Input!\a" << endl;
			}
			else if (findTargetInSubjectArray(subjectArray, subjectCode, MAX_SUBJECT) != -1) {
				cout << "Subject code is used by other subject!\a" << endl;
			}
			else {
				subjectArray[emptySlot].code = subjectCode;
				subjectArray[emptySlot].name = subjectName;
				subjectArray[emptySlot].creditHour = subjectCreditHour;
				cout << "\nSubject successfully added." << endl;
				validInput = true;
			}
		} while (!validInput);
	}
	return;
}

void removeSubject(Subject currentSubjects[], Student currentStudents[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	/*Func Des	: This function will first check the given Subject array is empty; if the Subject array is empty, it will prompt error to user as there is no more subject to be removed. If the Subject array is not empty, it will then prompt the user to input subject code. The function will check whether the entered subject code is valid via findTargetInSubjectArray(); if the subject code entered is not error, user will be prompted error; else subject will be removed from given Subject array, and also from the Subject array of all students.*/
	viewCurrentSubjects(currentSubjects, MAX_SUBJECT);
	if (checkEmptySubjectArray(currentSubjects, MAX_SUBJECT)) {
		cout << "Cannot remove subject anymore!" << endl;
	}
	else {
		bool stop = false;
		do {
			string subjectCode;
			cout << "\nWhat subject do you like to remove?" << endl;
			cout << "Subject code: ";
			getline(cin, subjectCode);
			int subjectIndex = findTargetInSubjectArray(currentSubjects, subjectCode, MAX_SUBJECT);
			if (subjectIndex == -1) {
				cout << "Invalid subject code!\a" << endl;
			}
			else {
				currentSubjects[subjectIndex].code = "NA";
				currentSubjects[subjectIndex].name = "NA";
				currentSubjects[subjectIndex].creditHour = -1;
				for (int i = 0; i < MAX_STUDENT; i++) {
					if (currentStudents[i].id != "NA") {
						for (int j = 0; j < 6; j++) {
							if (currentStudents[i].grades[j].subject.code == subjectCode) {
								currentStudents[i].grades[j].grade = "NA";
								currentStudents[i].grades[j].point = -1;
								currentStudents[i].grades[j].subject.code = "NA";
								currentStudents[i].grades[j].subject.name = "NA";
								currentStudents[i].grades[j].subject.creditHour = -1;
							}
						}
					}
				}
				cout << "Subject removed." << endl;
				stop = true;
			}
		} while (!stop);
	}
	return;
}
/*Functions in Manage Teachers*******************************************************/
void viewCurrentTeachers(Teacher currentTeachers[], const int MAX_TEACHER) {
	//Func Des	: This function allows admin to view the list of current teachers available.

	centerString("CS Teachers in Academic Year 2023");
	for (int i = 0, num = 1; i < MAX_TEACHER; i++, num++) {
		if (currentTeachers[i].id != "NA") {
			cout << "Teacher No		: " << num << endl;
			cout << "Teacher ID		: " << currentTeachers[i].id << endl;
			cout << "Teacher Name		: " << currentTeachers[i].name << endl;
			cout << "Subject Assigned	: " << currentTeachers[i].subjectAssigned.code << " " << currentTeachers[i].subjectAssigned.name << endl;
			cout << endl;
		}
	}
	return;
}

void addTeacher(Subject currentSubjects[], Teacher currentTeachers[], const int MAX_SUBJECT, const int MAX_TEACHER) {
	//Func Des	: This function allows admin to add new teachers. It will first check if teacher array if full, if yes, it will prompt error message to user. If not, it will proceed to ask for new teacher ID, name to be stored in teacher array given the conditions set are met.

	bool stop = false;
	int emptyTeacherSlot = findTargetInTeacherArray(currentTeachers, "NA", MAX_TEACHER);
	viewCurrentTeachers(currentTeachers, MAX_TEACHER);
	if (emptyTeacherSlot == -1) {
		cout << "No empty slot is available to add a new teacher!\a" << endl;
	}
	else {
		do {
			string teacherID, teacherName;
			cout << "Teacher ID (max 20 characters)  : ";
			getline(cin, teacherID);
			cout << "Teacher Name (max 70 characters): ";
			getline(cin, teacherName);
			if (teacherID.empty() || teacherID.length() > 20) {
				cout << "Invalid Input!\a" << endl;
			}
			else if (teacherName.empty() || teacherName.length() > 70) {
				cout << "Invalid Input!\a" << endl;
			}
			else if (findTargetInTeacherArray(currentTeachers, teacherID, MAX_TEACHER) != -1) {
				cout << "Teacher ID is used by other teacher!\a" << endl;
			}
			else {
				currentTeachers[emptyTeacherSlot].id = teacherID;
				currentTeachers[emptyTeacherSlot].name = teacherName;
				assignSubjectToTeacher(currentSubjects, currentTeachers, emptyTeacherSlot, MAX_SUBJECT, MAX_TEACHER);
				cout << "Teacher's information has been added........" << endl;
				stop = true;
			}
		} while (!stop);
	}
}

void assignSubjectToTeacher(Subject currentSubjects[], Teacher currentTeachers[], const int emptyTeacherSlot, const int MAX_SUBJECT, const int MAX_TEACHER) {
	//Func Des	: This function allows admin to assign a subject to teacher. It first checks prompts user to input subject code. It will then check if the subject exists or if another teacher has been assigned the subject. If so, an error message will prompt. If not, the subject would be assigned to the teacher.
	bool stop = false;
	viewCurrentSubjects(currentSubjects, MAX_SUBJECT);
	do {
		string subjectCode;
		cout << "\nSubject code (Enter STOP to terminate): ";
		getline(cin, subjectCode);
		if (subjectCode == "STOP") {
			stop = true;
		}
		else {
			int subjectIndex = findTargetInSubjectArray(currentSubjects, subjectCode, MAX_SUBJECT);
			if (subjectIndex == -1) {
				cout << "Invalid Input!\a" << endl;
			}
			else if (checkSubjectIsAssigned(currentTeachers, subjectCode, MAX_TEACHER)) {
				cout << "Error! Subject was assigned to other teacher!\a" << endl;
			}
			else {
				currentTeachers[emptyTeacherSlot].subjectAssigned = currentSubjects[subjectIndex];
				stop = true;
			}
		}
	} while (!stop);
}

void removeTeacher(Teacher currentTeachers[], const int MAX_TEACHER) {
	//Func Des	: This function allows admin to remove existing teachers. It will first check if teacher array is empty. If yes, an error message will prompt the user. If not, the function would prompt the user to input teacher ID. If teacher ID does not match with any ID in teacher array, error message will prompt to user. If ID matches, all information under the teacher stored in teacher array will be removed.

	viewCurrentTeachers(currentTeachers, MAX_TEACHER);
	if (checkEmptyTeacherArray(currentTeachers, MAX_TEACHER)) {
		cout << "Cannot remove teacher anymore!\a" << endl;
	}
	else {
		bool stop = false;
		do {
			string teacherIDByUser;
			cout << "Who do you like to remove?\nTeacher ID: ";
			getline(cin, teacherIDByUser);
			int teacherIndex = findTargetInTeacherArray(currentTeachers, teacherIDByUser, MAX_TEACHER);
			if (teacherIndex == -1) {
				cout << "Invalid teacher id!\a" << endl;
			}
			else {
				currentTeachers[teacherIndex].id = "NA";
				currentTeachers[teacherIndex].name = "NA";
				currentTeachers[teacherIndex].subjectAssigned.code = "NA";
				currentTeachers[teacherIndex].subjectAssigned.name = "NA";
				currentTeachers[teacherIndex].subjectAssigned.creditHour = -1;
				cout << "Teacher removed." << endl;
				stop = true;
			}
		} while (!stop);
	}
	return;
}
/*Functions in manage students**********************************************************/
void viewCurrentStudents(Student currentStudents[], const int MAX_STUDENT) {
	//Func Des	: This function allows user to view current students, including subjects taken by them.
	centerString("CS students in academic year 2023");
	for (int i = 0, num = 1; i < MAX_STUDENT; i++, num++) {
		if (currentStudents[i].id != "NA") {
			cout << "Student No   : " << num << endl;
			cout << "Student ID   : " << currentStudents[i].id << endl;
			cout << "Student Name : " << currentStudents[i].name << endl;
			cout << "Subject Taken: " << endl;
			for (int j = 0; j < 6; j++) {
				cout << "\t\t" << j + 1 << ". " << currentStudents[i].grades[j].subject.code << "\t" << currentStudents[i].grades[j].subject.name << endl;
			}
			cout << endl;
		}
	}
	return;
}

void viewAStudent(Student student) {
	/*Func Des	: This function is similar to viewCurrentStudents; however, it only display information about one student. */
	cout << endl;
	centerString("Information of " + student.name);
	cout << "Student ID   : " << student.id << endl;
	cout << "Student Name : " << student.name << endl;
	cout << "Subject Taken: " << endl;
	for (int i = 0; i < 6; i++) {
		cout << "\t\t" << i + 1 << ". " << student.grades[i].subject.code << "\t" << student.grades[i].subject.name << endl;
	}
	cout << endl;
}

void viewCurrentStudentIdAndName(Student currentStudents[], const int MAX_STUDENT) {
	//Func Des	: This function is similar to viewCurrentStudents(), the difference is it does not show subject taken by students.
	centerString("CS students in academic year 2023");
	for (int i = 0, num = 1; i < MAX_STUDENT; i++, num++) {
		if (currentStudents[i].id != "NA") {
			cout << "Student No   : " << num << endl;
			cout << "Student ID   : " << currentStudents[i].id << endl;
			cout << "Student Name : " << currentStudents[i].name << endl;
			cout << endl;
		}
	}
	return;
}

void addStudent(Subject subjectsAvailable[], Student currentStudents[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	/*Func Des	: This function allows user to add student to the array currentStudent; if the array is full of defined students, it will inform the user that the array is full and terminate. Apart from getting the name & student ID from user by using getStudentInfo(), this function also allows user to add subjects taken by that particular student by calling getStubjectRegisteredByStudent().*/
	viewCurrentStudentIdAndName(currentStudents, MAX_STUDENT);
	int emptySlot = findTargetInStudentArray(currentStudents, "NA", MAX_STUDENT);
	if (emptySlot == -1) {
		cout << "Cannot add student anymore! (0 remaining empty slot)" << endl;
	}
	else {
		bool stop = false;
		do {
			string studentID, studentName;
			cout << "Student ID (max 20 characters)  : ";
			getline(cin, studentID);
			cout << "Student Name (max 70 characters): ";
			getline(cin, studentName);
			if (studentID.length() > 20 || studentName.length() > 70 || studentID.length() == 0 || studentName.length() == 0) {
				cout << "Invalid Input!\a" << endl;
			}
			else if (findTargetInStudentArray(currentStudents, studentID, MAX_STUDENT) != -1) {
				cout << "Student ID is used by other student!\a" << endl;
			}
			else if (findTargetInStudentArray(currentStudents, studentID, MAX_STUDENT) == -1) {
				currentStudents[emptySlot].id = studentID;
				currentStudents[emptySlot].name = studentName;
				stop = true;
			}
		} while (!stop);
	}
	return;
}

void removeStudent(Student currentStudents[], const int MAX_STUDENT) {
	/*Func Des	: This function lets user to remove student from the Student array. It will first determine whether the given student still has elements to be removed by calling checkEmptyStudentArray(). If there is still element in the student array, it will prompt message, asking for student id. Then, it will validate whether the given student id is valid by calling findTargetInStudent(); if the student does exist, it will then be removed.*/
	viewCurrentStudentIdAndName(currentStudents, MAX_STUDENT);
	if (checkEmptyStudentArray(currentStudents, MAX_STUDENT)) {
		cout << "Cannot remove student anymore!\a" << endl;
	}
	else {
		bool stop = false;
		do {
			string studentID;
			cout << "Who do you like to remove?\nStudent ID: ";
			getline(cin, studentID);
			int studentIndex = findTargetInStudentArray(currentStudents, studentID, MAX_STUDENT);
			if (studentIndex == -1) {
				cout << "Invalid student id!\a" << endl;
			}
			else {
				currentStudents[studentIndex].id = "NA";
				currentStudents[studentIndex].name = "NA";
				for (int i = 0; i < 6; i++) {
					currentStudents[studentIndex].grades[i].grade = "NA";
					currentStudents[studentIndex].grades[i].point = -1;
					currentStudents[studentIndex].grades[i].subject.code = "NA";
					currentStudents[studentIndex].grades[i].subject.name = "NA";
					currentStudents[studentIndex].grades[i].subject.creditHour = -1;
				}
				cout << "Student removed." << endl;
				stop = true;
			}
		} while (!stop);
	}
	return;
}

void addSubjectToAStudent(Student currentStudents[], Subject subjectsAvailable[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	/*Func Des	: This function enables the user to assign subjects to students. It will first display student Id and name by calling displayStudentIdAndName() and check whether the Student array contains any student; if no, it will terminate. Then, it will also check whether the subjectsAvailable is empty; if it is empty, it will also terminate. If there is valid student in Student array, and valid subject in Subject array, it will prompt user to input student id, and call findTargetInStudent() to validate the entered the student id. If the student id is valid, it will call getSubjectRegisteredByStudent() to handle the process of assigning subject; if the student id is not valid at the beginning, user will be prompt an error message.*/
	viewCurrentStudentIdAndName(currentStudents, MAX_STUDENT);
	if (checkEmptyStudentArray(currentStudents, MAX_STUDENT)) {
		cout << "Error! There is no student available!\a" << endl;
	}
	else if (checkEmptySubjectArray(subjectsAvailable, MAX_SUBJECT)) {
		cout << "Error! There is no subject available!\a" << endl;
	}
	else {
		string studentIDByUser;
		int studentIndex;
		cout << "Enter a student ID : ";
		getline(cin, studentIDByUser);
		studentIndex = findTargetInStudentArray(currentStudents, studentIDByUser, MAX_STUDENT);
		if (studentIndex != -1) {
			getSubjectsToBeAdded(subjectsAvailable, currentStudents[studentIndex], MAX_SUBJECT);
		}
		else {
			cout << "Invalid Input!\a" << endl;
		}
	}
}

void getSubjectsToBeAdded(Subject subjectsAvailable[], Student& student, const int MAX_SUBJECT) {
	/*Func Des	: This function allows user to add subject to the array subjectRegistered of Student. It will shows current available subjects using viewCurrentSubjects(), and shows the detail of a student by calling viewAStudent(). The function will first check whether there is any empty slot in the array subjectsRegistered of student; if no, user will be prompt error; if yes, it will proceed to get subject ID from user. Subject id entered by user will then be validated by calling findTargetInSubject. Note that user is allowed to enter "STOP" to terminate when entering subject id. If the subject id is valid, the function will then check whether the user has previously registered the same subject before; if yes, user will be prompt error; if no, the subject will be registered to student. Incidentally, this function is based on do while loop, hence, any modification of the array subjectsRegistered of Student will be updated instantly. */

	bool stop = false;
	do {
		displayBanner("Admin Panel - Manage Students");
		viewCurrentSubjects(subjectsAvailable, MAX_SUBJECT);
		viewAStudent(student);
		int emptySlot = findTargetInGradeArray(student.grades, "NA");
		if (emptySlot != -1) {
			string subjectCode;
			cout << "\nWhat subject do you like to add?\nSubject's ID (Enter STOP to terminate): ";
			getline(cin, subjectCode);
			if (subjectCode == "STOP") {
				stop = true;
			}
			else {
				int subjectIndex = findTargetInSubjectArray(subjectsAvailable, subjectCode, MAX_SUBJECT);
				if (subjectIndex != -1) {
					if (findTargetInGradeArray(student.grades, subjectCode) != -1) {
						cout << "This subject has been registered previously!\a" << endl;
						pause();
					}
					else {
						student.grades[emptySlot].subject = subjectsAvailable[subjectIndex];
						cout << student.grades[emptySlot].subject.name << " has been successfully registered by student" << endl;
						pause();
					}
				}
				else {
					cout << "Invalid Input!\a" << endl;
					pause();
				}
			}
		}
		else {
			cout << "This student has registered maximum amount of subject!\a" << endl;
			stop = true;
		}
	} while (!stop);
	return;
}

void removeSubjectFromAStudent(Student currentStudents[], Subject subjectsAvailable[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	/*Func Des	: This function allows user to remove subject. First, it calls displayStudentIdAndName() to display the id and name of all current students. It then checks whether the student array is empty; if it is empty, user will be prompt error and the function will terminate; if it is not empty, the function will then ask the user to provide a student id. The entered student id will be validated by calling findTargetInStudent(); if it is valid, the function will call removeSubjectRegisteredByStudent() to handle the subject removing process; it is not valid, user will be prompt error, and the function will terminate.*/
	viewCurrentStudentIdAndName(currentStudents, MAX_STUDENT);
	if (checkEmptyStudentArray(currentStudents, MAX_STUDENT)) {
		cout << "Error! There is no student available!\a" << endl;
	}
	else {
		string studentID;
		int studentIndex;
		cout << "Enter a student ID : ";
		getline(cin, studentID);
		studentIndex = findTargetInStudentArray(currentStudents, studentID, MAX_STUDENT);
		if (studentIndex != -1) {
			getSubjectsToBeRemoved(currentStudents[studentIndex]);
		}
		else {
			cout << "Invalid Input!\a" << endl;
		}
	}
}

void getSubjectsToBeRemoved(Student& student) {
	/*Func Des	: This function get subject to be removed from a student. The function will first check whether the student is assigned a subject; if no, the function will terminate. After that, user will be prompt to enter a subject code; if the subject is assigned to student, then the data related to that subject will be removed from the student. */
	bool stop = false;
	do {
		displayBanner("Admin Panel - Manage Students");
		viewAStudent(student);
		if (checkEmptyGradesArray(student.grades)) {
			cout << "This student has no subject to be removed!\a" << endl;
			stop = true;
		}
		else {
			string subjectID;
			cout << "What subject do you like to remove?\nSubject's ID (Enter STOP to terminate): ";
			getline(cin, subjectID);
			if (subjectID == "STOP") {
				stop = true;
			}
			else {
				int subjectIndex = findTargetInGradeArray(student.grades, subjectID);
				if (subjectIndex != -1) {
					student.grades[subjectIndex].grade = "NA";
					student.grades[subjectIndex].point = -1;
					student.grades[subjectIndex].subject.code = "NA";
					student.grades[subjectIndex].subject.name = "NA";
					student.grades[subjectIndex].subject.creditHour = -1;
					cout << "Subject has been removed from student." << endl;
					pause();
				}
				else {
					cout << "Invalid Input!\a" << endl;
					pause();
				}
			}
		}
	} while (!stop);
}
/*Functions in Generate Report*****************************************************************************/
double getStudentGPA(Student student) {
	/*Func Des	: This function calculate the GPA of a student.*/
	double qualityPointSum = 0, creditHourSum = 0, GPA = 0;
	for (int i = 0; i < 6; i++) {
		if (student.grades[i].grade != "NA") {
			qualityPointSum += student.grades[i].point * student.grades[i].subject.creditHour;
			creditHourSum += student.grades[i].subject.creditHour;
		}
	}
	if (qualityPointSum == 0) {
		GPA = 0;
	}
	else {
		GPA = qualityPointSum / creditHourSum;
	}
	return GPA;
}

void generateStudentReport(Student currentStudents[], const int MAX_STUDENT) {
	/*Func Des	: This function generates the report of a student. As usual, the user will be prompt to enter a student id, and the student id will be generated. After that, the GPA of student will be calculated via getStudentGPA(), and data related to subject taken by student will be generated.*/
	bool stop = false;
	viewCurrentStudentIdAndName(currentStudents, MAX_STUDENT);
	do {
		string studentID;
		cout << "Enter student ID (Enter STOP to terminate): ";
		getline(cin, studentID);
		if (studentID == "STOP") {
			stop = true;
		}
		else {
			int studentIndex = findTargetInStudentArray(currentStudents, studentID, MAX_STUDENT);
			if (studentIndex == -1) {
				cout << "Student not found!\a" << endl;
			}
			else {
				double GPA = getStudentGPA(currentStudents[studentIndex]);
				displayBanner("Student Report of " + currentStudents[studentIndex].name);
				for (int i = 0; i < 6; i++) {
					if (currentStudents[studentIndex].grades[i].subject.code != "NA") {
						cout << endl;
						cout << setw(20) << right << currentStudents[studentIndex].grades[i].subject.code;
						cout << " ";
						cout << setw(70) << left << currentStudents[studentIndex].grades[i].subject.name;
						cout << " ";
						cout << setw(5) << left << currentStudents[studentIndex].grades[i].grade;
						cout << " ";
						cout << setw(5) << right << fixed << setprecision(2) << currentStudents[studentIndex].grades[i].point;
						cout << endl;
					}
				}
				cout << endl;
				centerString("GPA: " + to_string(GPA));
				stop = true;
			}
		}
	} while (!stop);
	return;
}

void generateSubjectReport(Subject currentSubjects[], Student currentStudents[], const int MAX_SUBJECT, const int MAX_STUDENT) {
	/*Func Des	: This function generates the report of a subject. */
	bool stop = false;
	viewCurrentSubjects(currentSubjects, MAX_SUBJECT);
	do {
		string subjectCode;
		cout << "Enter a subject code (Enter STOP to terminate): ";
		getline(cin, subjectCode);
		if (subjectCode == "STOP") {
			stop = true;
		}
		else {
			if (findTargetInSubjectArray(currentSubjects, subjectCode, MAX_SUBJECT) == -1) {
				cout << "Invalid Input!\a" << endl;
			}
			else {
				displayBanner("Subject Report");
				viewSubjectReport(currentStudents, subjectCode, MAX_STUDENT);
				stop = true;
			}
		}
	} while (!stop);
}
/*Funtions in Teacher panel********************************************************/
void viewSubjectReport(Student currentStudents[], string subjectCode, const int MAX_STUDENT) {
	/*Func Des	: This function loops and checks whether the ith student in currentStudents is valid. After that, it loops and checks whether the jth subject of ith student equals to the given subject code. If yes, performance of ith student in jth subject will be displayed*/
	centerString("Report for " + subjectCode);
	for (int i = 0; i < MAX_STUDENT; i++) {
		string stringToBeDisplayed;
		if (currentStudents[i].id != "NA") {
			stringToBeDisplayed += currentStudents[i].id + "    ";
			stringToBeDisplayed += currentStudents[i].name + "    ";
			for (int j = 0; j < 6; j++) {
				if (currentStudents[i].grades[j].subject.code == subjectCode) {
					stringToBeDisplayed += currentStudents[i].grades[j].grade;
					stringToBeDisplayed += "    ";
					stringToBeDisplayed += to_string(currentStudents[i].grades[j].point);
					centerString(stringToBeDisplayed);
				}
			}
		}
	}
}

void gradeStudents(Student currentStudents[], string subjectCode, const int MAX_STUDENT) {
	/*Func Des	: This function first checks whether there is an available student in currentStudents via checkEmptyStudentArray(). Then, it loops and checks whether the ith student is valid. After that, it checks whether the jth subject of ith student equals to subject taught by the teacher. Note that the subject must not be graded before. Finally, the function calls getStudentGrade() to get the grade of that particular student in this subject.*/
	if (checkEmptyStudentArray(currentStudents, MAX_STUDENT)) {
		cout << "No students available!\a" << endl;
	}
	else {
		viewSubjectReport(currentStudents, subjectCode, MAX_STUDENT);
		for (int i = 0; i < MAX_STUDENT; i++) {
			if (currentStudents[i].id != "NA") {
				for (int j = 0; j < 6; j++) {
					if (currentStudents[i].grades[j].subject.code == subjectCode && currentStudents[i].grades[j].grade == "NA") {
						getStudentGrade(currentStudents[i], j);
					}
				}
			}
		}
		cout << "\nAll students were graded for this subject." << endl;
	}
}

void getStudentGrade(Student& student, int gradeIndex) {
	/*Func Des	: The function prompt user to enter course work mark and final assessment mark of a student. It then calculates the total mark based on coursework and final assessment mark. Note that, if the coursework is lower than 40, the user will not be required to enter the final mark as the student already fails the subject; hence, the function will terminate. The function also assigns the grade and point of student in this subject based on given conditions. */
	bool stop = false;
	do {
		double courseworkMark, finalassessmentMark;
		cout << endl;
		cout << "Provide performace of " << student.name << " for this subject." << endl;
		promptInputFromUser("Enter coursework mark (100%)		: ", courseworkMark);
		if (courseworkMark < 40 && courseworkMark >= 0) {
			student.grades[gradeIndex].point = 0.00;
			student.grades[gradeIndex].grade = "F ";
			cout << "Student has failed this subject." << endl;
			stop = true;
		}
		else {
			promptInputFromUser("Enter final assessment mark (100%)	: ", finalassessmentMark);
			if (courseworkMark < 0 || courseworkMark > 100 || finalassessmentMark < 0 || finalassessmentMark > 100) {
				cout << "Invalid Input!\a" << endl;
			}
			else {
				double totalMark = courseworkMark * 0.4 + finalassessmentMark * 0.6;
				if (totalMark >= 90) {
					student.grades[gradeIndex].point = 4.00;
					student.grades[gradeIndex].grade = "A+";
				}
				else if (totalMark >= 80) {
					student.grades[gradeIndex].point = 4.00;
					student.grades[gradeIndex].grade = "A ";
				}
				else if (totalMark >= 75) {
					student.grades[gradeIndex].point = 3.67;
					student.grades[gradeIndex].grade = "A-";
				}
				else if (totalMark >= 70) {
					student.grades[gradeIndex].point = 3.33;
					student.grades[gradeIndex].grade = "B+";
				}
				else if (totalMark >= 65) {
					student.grades[gradeIndex].point = 3.00;
					student.grades[gradeIndex].grade = "B ";
				}
				else if (totalMark >= 60) {
					student.grades[gradeIndex].point = 2.67;
					student.grades[gradeIndex].grade = "B-";
				}
				else if (totalMark >= 55) {
					student.grades[gradeIndex].point = 2.33;
					student.grades[gradeIndex].grade = "C+";
				}
				else if (totalMark >= 50) {
					student.grades[gradeIndex].point = 2.00;
					student.grades[gradeIndex].grade = "C ";
				}
				else {
					student.grades[gradeIndex].point = 0.00;
					student.grades[gradeIndex].grade = "F ";
				}
				stop = true;
			}
		}
	} while (!stop);
}

void editStudentGrade(Student currentStudents[], string subjectCode, const int MAX_STUDENT) {
	/*Func Des	: The function enables the user to change the grade of a student*/
	bool stop = false;
	viewSubjectReport(currentStudents, subjectCode, MAX_STUDENT);
	do {
		string studentID;
		int studentIndex;
		cout << "Enter student ID: ";
		getline(cin, studentID);
		studentIndex = findTargetInStudentArray(currentStudents, studentID, MAX_STUDENT);
		if (studentIndex == -1) {
			cout << "Invalid input!\a" << endl;
		}
		else {
			getStudentGrade(currentStudents[studentIndex], findTargetInGradeArray(currentStudents[studentIndex].grades, subjectCode));
			stop = true;
		}
	} while (!stop);
}

void exportSubjectReport(Student currentStudents[], string subjectCode, const int MAX_STUDENT) {
	/*Func Des	: The function enables user to export subject report. User will be prompt to provide the file location. After that, it exports the performance of students in this subject.*/
	bool stop = false;
	ofstream outFile;
	char fileLocation[101];
	do {
		cout << "Note that you must provide authorization for this program to export file.\n" << endl;
		cout << "Enter a file location (e.g., D:\\\\UTAR\\\\Y1S2\\\\subjectReport.txt):";
		cin.getline(fileLocation, 100);
		outFile.open(fileLocation, ios::trunc);
		if (!outFile.is_open()) {
			cout << "Invalid file location!\a" << endl;
		}
		else {
			string title = "Subject Report for " + subjectCode + " In Academic Year 2023";
			outFile << title << endl;
			outFile << endl;
			for (int i = 0; i < MAX_STUDENT; i++) {
				if (currentStudents[i].id != "NA") {
					for (int j = 0; j < 6; j++) {
						if (currentStudents[i].grades[j].subject.code == subjectCode) {
							outFile << "Student ID		:" << " " << currentStudents[i].id << endl;
							outFile << "Student Name	:" << " " << currentStudents[i].name << endl;
							outFile << "Subject Grade	:" << " " << currentStudents[i].grades[j].grade << endl;
							outFile << "Subject Point	:" << fixed << setprecision(2) << " " << currentStudents[i].grades[j].point << endl;
							outFile << endl;
						}
					}
				}
			}
			cout << "Report was successfully generated." << endl;
			stop = true;
		}
	} while (!stop);
	outFile.close();
	return;
}
