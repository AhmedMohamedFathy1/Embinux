#!/bin/bash

#include from another modules
source ./system.sh
source ./syfc.sh
source ./Network.sh
source ./SystemControl.sh
source ./SystemLogs.sh


CreateFile
# Device Main loop
while true; 
do
        echo "Menu:"
        echo "1) Show System Information"
        echo "2) Show Device Information"
        echo "3) Show Network Infomation"
        echo "4) System Control"
        
        echo "5) Exit"
        # Read user choice
        read -p "Enter your choice: " choice

        case $choice in
        1) 
        SystemInfo_MainLoop
        ;;
        2) 
        DeviceInfo_MainLoop 
        ;;
        3) 
        Network_MainLoop 
        ;;
        4)
        SystemControl_MainLoop
        ;;
        5) echo "Exiting...";
        break ;;

        *) echo "Invalid choice, try again." 
        ;;
        esac
done