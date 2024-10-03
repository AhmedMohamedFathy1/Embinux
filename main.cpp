#include <iostream>
#include <chrono>  // For std::chrono
#include <thread>  // For std::this_thread::sleep_for

#include <QApplication>
#include <QMainWindow>
#include <QTimer>
#include "ui_Car.h"

#include "diagnostics.hpp"
#include "AdpativeCruiseControl.hpp"
#include "SensorSimulators.hpp"

using namespace std;

// Function to update the QLabel with vehicle speed
void updateLabel(Ui::MainWindow &ui,int speed) {
    // Replace with actual sensor data or logic to get the vehicle speed
  // int speed = rand() % 100; // Example: random speed value between 0 and 99
    QString labelText = QString("Vehicle Speed: %1 Km/h").arg(speed);
    
    // Update QLabel with new speed value
    ui.label->setText(labelText);
}

int main(int argc, char *argv[]) 
{
    Sensors_data_t &Sensors_data = Update_Sensors::GetSensorData();
    Diagnostics diagnostics;
    AdaptiveCruiseControl ACC;
    Simulate_Sensor simulate_Sensor; 

    QApplication app(argc, argv);

    QMainWindow window;
    Ui::MainWindow ui;  
    ui.setupUi(&window);  // Set up the UI for the window

    // Create a timer to update the QLabel
    QTimer *timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        simulate_Sensor.Scenario_Handler();
        diagnostics.Run_Diagnostics();
        ACC.AdpativeCruiseControl_Manager();
        updateLabel(ui,static_cast<int>(Sensors_data.SpeedSensor_data)); // Call the function to update the label
    });
    timer->start(1000); // Update every 1000 ms (1 second)

    window.show();
    return app.exec();
}
