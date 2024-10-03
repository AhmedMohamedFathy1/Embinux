#include "QtApp.hpp"
#include <QTimer>
#include <iostream>


// Initialize static members of QtFlags outside of the struct definition
bool QtFlags::Qt_Obstacle_Flag_GDB = false;
bool QtFlags::Qt_Temperature_Flag_GDB = false;
bool QtFlags::Qt_Fuel_Flag_GDB = false;
bool QtFlags::Qt_Battery_Flag_GDB = false;
bool QtFlags::Qt_speed_Flag_GDB = false;


QtFlags &Qt_Flags = VehicleApp::Get_Qt_FlagInstance();

VehicleApp::VehicleApp(QWidget *parent) : QMainWindow(parent), speed(0) {
    ui.setupUi(this);

    // Timer to simulate speed change and check condition
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VehicleApp::checkSpeed);
    timer->start(1000);  // Check every 1 second
}

void VehicleApp::checkSpeed(void) 
{
        if (isToggled) {
            ui.label->setText("Speed Exceeded!");
        } else {
            ui.label->setText("Vehicle Speed");
        }
        isToggled = !isToggled;  // Toggle the flag
    
}

void VehicleApp::updateLabel(Ui::MainWindow &ui, int speed) 
{
    QString labelText = QString("Vehicle Speed: %1 Km/h").arg(speed);
    ui.label->setText(labelText);
}

VehicleApp &VehicleApp::get_VehicleApp_Instance(void)
{
    static VehicleApp instance;  // Singleton instance
    return instance;
}

void VehicleApp::Label_Manager(Ui::MainWindow &ui)
{
    if (Qt_Flags.Qt_Obstacle_Flag_GDB == true) 
    {
        if (Obstacle_isToggled) 
        {
            ui.obstacle->setText("Obstacle Found");
        }
        else
        {
            ui.obstacle->setText("");
        }
        Obstacle_isToggled = !Obstacle_isToggled;  // Toggle the flag 
    }
    else 
    {
        ui.obstacle->setText("");
  
    }

    if (Qt_Flags.Qt_Temperature_Flag_GDB == true) 
    {
        if (Temp_isToggled) 
        {
            ui.OverHeat->setText("Motor Over Heat");
        }
        else
        {
            ui.OverHeat->setText("");
        }
        Temp_isToggled = !Temp_isToggled;  // Toggle the flag 
    }
    else 
    {
        ui.OverHeat->setText("");
  
    }

    if (Qt_Flags.Qt_Fuel_Flag_GDB == true) 
    {
        if (Fuel_isToggled) 
        {
            ui.Fuel->setText("Low Fuel");
        }
        else
        {
            ui.Fuel->setText("");
        }
        Fuel_isToggled = !Fuel_isToggled;  // Toggle the flag 
    }
    else 
    {
        ui.Fuel->setText("");
  
    }
    

    if (Qt_Flags.Qt_Battery_Flag_GDB == true) 
    {
        if (Battery_isToggled) 
        {
            ui.LowBattery->setText("Battery is Dead");
        }
        else
        {
            ui.LowBattery->setText("");
        }
        Battery_isToggled = !Battery_isToggled;  // Toggle the flag 
    }
    else 
    {
        ui.LowBattery->setText("");
  
    }

    if (Qt_Flags.Qt_speed_Flag_GDB == true) 
    {
        if (Speed_isToggled) 
        {
            ui.Speed->setText("Excessive Speed");
        }
        else
        {
            ui.Speed->setText("");
        }
        Speed_isToggled = !Speed_isToggled;  // Toggle the flag 
    }
    else 
    {
        ui.Speed->setText("");
  
    }

}

QtFlags &VehicleApp::Get_Qt_FlagInstance(void)
{
    static QtFlags QtFlags_PDB;
    return QtFlags_PDB;
}
