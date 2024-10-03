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


#include "QtApp.hpp"

using namespace std;


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

    VehicleApp &mian_vehicleApp = VehicleApp::get_VehicleApp_Instance();

    // Create a timer to update the QLabel
    QTimer *timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        simulate_Sensor.Scenario_Handler();
        diagnostics.Run_Diagnostics();
        ACC.AdpativeCruiseControl_Manager();

        mian_vehicleApp.updateLabel(ui,static_cast<int>(Sensors_data.SpeedSensor_data)); // Call the function to update the label
        mian_vehicleApp.Label_Manager(ui);
      //  mian_vehicleApp.checkSpeed(ui);
    });
    timer->start(1000); // Update every 1000 ms (1 second)

    window.show();
    return app.exec();
}
