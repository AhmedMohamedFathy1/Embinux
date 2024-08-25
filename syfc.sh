#!/bin/bash
source ./SystemLogs.sh
##################################   System    ##################################
# Function to show device information and topology
show_device_info() 
{
    local command="Show Device Information"
    local shell_command="lscpu; ls /sys/class/block; lsusb; ls /sys/class/net"
    
    # Bold blue color
    bold_blue="\e[1;34m"
    # Reset color
    reset_color="\e[0m"

    echo "Devices in the system:"

    # Show CPU topology
    echo "CPU Topology:"
    lscpu_output=$(lscpu)  # Capture the output of lscpu
    echo -e "${bold_blue}${lscpu_output}${reset_color}"
    
    # Show storage devices
    echo "Storage Devices:"
    storage_output=$(ls /sys/class/block)  # Capture the output of ls /sys/class/block
    echo -e "${bold_blue}${storage_output}${reset_color}"
    
    # Show USB devices
    echo "USB Devices:"
    usb_output=$(lsusb)  # Capture the output of lsusb
    echo -e "${bold_blue}${usb_output}${reset_color}"
    
    # Show network devices
    echo "Network Devices:"
    network_output=$(ls /sys/class/net)  # Capture the output of ls /sys/class/net
    echo -e "${bold_blue}${network_output}${reset_color}"
    
    # Log the command and its output
    local output="${lscpu_output}\n${storage_output}\n${usb_output}\n${network_output}"
    log_command_output "$command" "$shell_command" "$output"
}

# Optional: Function to set battery threshold
set_battery_threshold() {
    local command="Set Battery Threshold"
    local shell_command="echo 60 > /sys/class/power_supply/BAT0/charge_control_end_threshold"
    
    echo -e "${bold_blue}Setting battery threshold to 60%...${reset_color}"
    # Log the command and its output
    sudo bash -c "echo 60 > /sys/class/power_supply/BAT0/charge_control_end_threshold" 2>&1 | tee -a "$log_file"
    echo -e "${bold_blue}Battery threshold set to 60%.${reset_color}"
    
    # Log the action
    log_command_output "$command" "$shell_command" "Battery threshold set to 60%."
}

# Optional: Function to control PC LEDs (e.g., Caps Lock LED)
control_leds() {
    local command="Control PC LEDs"
    
    echo "Controlling Caps Lock"
    echo "1) Turn on Caps Lock LED"
    echo "2) Turn off Caps Lock LED"
    read -p "Enter your choice: " choice

    local shell_command=""
    local output=""
    
    case $choice in
        1) 
            shell_command="echo 1 > /sys/class/leds/input2::capslock/brightness"
            sudo bash -c "$shell_command" 2>&1
            output="Caps Lock LED is Turned on."
            ;;
        2) 
            shell_command="echo 0 > /sys/class/leds/input2::capslock/brightness"
            sudo bash -c "$shell_command" 2>&1
            output="Caps Lock LED is Turned off."
            ;;
        *) 
            output="Invalid choice."
            ;;
    esac
    
    # Print and log the result
    echo -e "${bold_blue}${output}${reset_color}"
    log_command_output "$command" "$shell_command" "$output"
}


DeviceInfo_MainLoop()
{
    # Device Main loop
    while true; 
    do
            echo "Menu:"
            echo "1) Show Device Information"
            echo "2) Set Battery Threshold (Admin Access Required)"
            echo "3) Control PC LEDs (Admin Access Required)"
            echo "4) Exit"
            # Read user choice
            read -p "Enter your choice: " choice

            case $choice in
            1) show_device_info 
            ;;
            2) set_battery_threshold 
            ;;
            3) control_leds
            ;;
            4) echo "Exiting...";
            break ;;

            *) echo "Invalid choice, try again." 
            ;;
            esac
    done
}