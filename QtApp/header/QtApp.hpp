#ifndef __QTAPP__H__
#define __QTAPP__H__

#include <QMainWindow>
#include "ui_Car.h"

// Declare the struct and its static members
struct QtFlags
{
    // Flags to toggle labels 
    static bool Qt_Obstacle_Flag_GDB;
    static bool Qt_Temperature_Flag_GDB;
    static bool Qt_Fuel_Flag_GDB;
    static bool Qt_Battery_Flag_GDB;
    static bool Qt_speed_Flag_GDB;

};

class VehicleApp : public QMainWindow 
{
    Q_OBJECT

public:

    Ui::MainWindow ui;

    VehicleApp(QWidget *parent = nullptr);  // Constructor

    void updateLabel(Ui::MainWindow &ui, int speed);
    void Label_Manager(Ui::MainWindow &ui);
    void checkSpeed(void);  // Method to check and toggle speed label

    static QtFlags &Get_Qt_FlagInstance(void); 
    static VehicleApp &get_VehicleApp_Instance(void);

private slots:

private:
    int speed;              // Variable to store the speed
    bool isToggled;
    bool Obstacle_isToggled;        
    bool Temp_isToggled;         
    bool Fuel_isToggled;        
    bool Battery_isToggled;      
    bool Speed_isToggled;

};

#endif  //!__QTAPP__H__
