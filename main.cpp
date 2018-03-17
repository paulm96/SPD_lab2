#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Task {
    int startTime;
    int taskTime;

    Task(int _startTime, int _taskTime)
            : startTime(_startTime), taskTime(_taskTime) { }
};

std::vector<Task> loadFromFile(const std::string &file) {
    std::ifstream in;
    in.open(file, std::ios::in);
    if (in.good())
        std::cout << "Opened succesfully\n";

    std::string s;
    std::getline(in, s);
    std::istringstream ss(s);

    int size;
    ss >> size;
    std::vector<Task> taskVector;
    int startTime, taskTime;

    for (int i = 0; i < size; ++i) {   //to fill taskVector
        std::getline(in, s);
        std::istringstream converter(s);
        converter >> startTime;
        converter >> taskTime;
        Task task(startTime, taskTime);
        taskVector.push_back(task);
    }
    return taskVector;
}

int Cmax(const std::vector<Task> &taskVector) {
    int Cmax = 0;
    for(const auto &i : taskVector) {
        if(i.startTime > Cmax) {     //if there is a gap on the machine
            Cmax += ((i.startTime - Cmax) + i.taskTime);  //add gap time and taskTime
        } else {                     //if there is not a gap on the machine
            Cmax += i.taskTime;       //add only taskTime
        }
    }
    return Cmax;
}

int main() {
    auto taskVector = loadFromFile("./JACK8.DAT");   //vector with tasks loaded from a file

    std::sort(taskVector.begin(), taskVector.end(), [](const Task& a, const Task& b)->bool {  //sort vector by  startTimes
       return  a.startTime < b.startTime;
    });

    std::cout << "Cmax = " << Cmax(taskVector) << std::endl;
    return 0;
}